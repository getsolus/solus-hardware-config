/*
 * This file is part of solus-hardware-config.
 *
 * Copyright © 2018 Solus Project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Trivial helper to silence warnings */
#define __shc_unused__ __attribute__((unused))

/**
 * Just represent the main governor frequencys
 */
typedef enum {
        SHC_SCALE_POWERSAVE = 0,
        SHC_SCALE_PERFORMANCE,
} ShcScale;

/**
 * Drivers we know and care about
 */
typedef enum {
        SHC_DRIVER_UNKNOWN = 0,  /**<Unable to determine driver, so bail. */
        SHC_DRIVER_CPUFREQ,      /**< System uses cpufreq on this core */
        SHC_DRIVER_INTEL_PSTATE, /**<System uses intel_pstate on this core */
} ShcDriver;

/**
 * Read the node and stuff it into out_buf, if possible.
 */
static bool shc_read_node(const char *node, char **out_buf, size_t buflen)
{
        int fd = -1;
        bool ret = false;
        ssize_t r = 0;

        fd = open(node, O_RDONLY | O_CLOEXEC);
        if (fd < 0) {
                return false;
        }

        if ((r = read(fd, out_buf, buflen)) < 0) {
                fprintf(stderr, "Failed to read %s: %s\n", node, strerror(errno));
                goto clean;
        }

        ret = true;

clean:
        close(fd);
        return ret;
}

/**
 * Determine which kernel driver is used to govern this cpufreq_path
 */
static ShcDriver shc_get_driver(const char *cpufreq_path)
{
        char cpu_buf[PATH_MAX] = { 0 };
        char read_buf[PATH_MAX] = { 0 };

        /* Build path for scaling_driver */
        if (snprintf(cpu_buf, sizeof(cpu_buf), "%s/scaling_driver", cpufreq_path) < 0) {
                fputs("OOM\n", stderr);
                return SHC_DRIVER_UNKNOWN;
        }

        if (!shc_read_node(cpu_buf, (char **)&read_buf, sizeof(read_buf))) {
                return SHC_DRIVER_UNKNOWN;
        }

        if (strncmp(read_buf, "intel_pstate", 12) == 0) {
                return SHC_DRIVER_INTEL_PSTATE;
        }

        /* We could expand this in future, but for now we only support these 2 guys. */
        return SHC_DRIVER_CPUFREQ;
}

/**
 * Transform requested scale to intel_pstate specific governor
 */
static const char *shc_transform_intel(ShcScale scale)
{
        switch (scale) {
        case SHC_SCALE_PERFORMANCE:
                return "performance";
        case SHC_SCALE_POWERSAVE:
        default:
                return "powersave";
        }
}

/**
 * Transform requested scale to cpufreq specific governor
 */
static const char *shc_transform_cpufreq(ShcScale scale)
{
        switch (scale) {
        case SHC_SCALE_PERFORMANCE:
                return "powerformance";
        case SHC_SCALE_POWERSAVE:
        default:
                return "ondemand";
        }
}

/**
 * Standard entry to transform driver + scale to target mode
 */
static const char *shc_transform(ShcDriver driver, ShcScale scale)
{
        switch (driver) {
        case SHC_DRIVER_INTEL_PSTATE:
                return shc_transform_intel(scale);
        case SHC_DRIVER_CPUFREQ:
                return shc_transform_cpufreq(scale);
        default:
                /* Handle UNKNOWN */
                return NULL;
        }
}

/**
 * Set the current governor for the @cpufreq_path to @target_mode
 */
static bool shc_set_governor(const char *cpufreq_path, const char *target_mode)
{
        char cpu_buf[PATH_MAX] = { 0 };
        int fd = -1;
        bool ret = false;

        /* Build path for scaling_driver */
        if (snprintf(cpu_buf, sizeof(cpu_buf), "%s/scaling_governor", cpufreq_path) < 0) {
                fputs("OOM\n", stderr);
                return SHC_DRIVER_UNKNOWN;
        }

        fd = open(cpu_buf, O_WRONLY | O_CLOEXEC, 00644);
        if (fd < 0) {
                fprintf(stderr,
                        "Failed to open %s for writing: %s\n",
                        cpufreq_path,
                        strerror(errno));
                return false;
        }

        /* Write mode */
        if (write(fd, target_mode, strlen(target_mode)) < 0) {
                fprintf(stderr, "Failed to write %s: %s\n", cpufreq_path, strerror(errno));
                goto failed;
        }

        (void)fdatasync(fd);
        ret = true;

failed:
        close(fd);
        return ret;
}

/**
 * Set scale on all CPUs to @mode
 */
static int shc_set_scale(ShcScale scale)
{
        static const char *glob_pattern = "/sys/devices/system/cpu/cpu*/cpufreq";
        glob_t glo = { 0 };

        if (glob(glob_pattern, 0, NULL, &glo) != 0) {
                return EXIT_FAILURE;
        }

        for (size_t i = 0; i < glo.gl_pathc; i++) {
                const char *cpu = glo.gl_pathv[i];
                ShcDriver driver = SHC_DRIVER_UNKNOWN;
                const char *target_mode = NULL;

                /* Skip unknown drivers */
                driver = shc_get_driver(cpu);
                target_mode = shc_transform(driver, scale);
                if (!target_mode) {
                        goto failed;
                }

                if (!shc_set_governor(cpu, target_mode)) {
                        goto failed;
                }
        }

failed:
        globfree(&glo);

        return EXIT_SUCCESS;
}

/**
 * Main entry into cpu-on-demand service
 *
 * For now we'll just push the powersave mode.
 */
int main(__shc_unused__ int argc, __shc_unused__ char **argv)
{
        return shc_set_scale(SHC_SCALE_POWERSAVE);
}