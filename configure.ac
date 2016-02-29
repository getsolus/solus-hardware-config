AC_INIT([Solus HW Config], 1, [ikey@solus-project.com], [solus-hardware-config], [https://solus-project.com/])
AM_INIT_AUTOMAKE([-Wno-portability no-dist-gzip dist-xz foreign subdir-objects])

AC_PREFIX_DEFAULT(/usr/local)
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_FILES([Makefile
                blacklist/Makefile
                xorg/Makefile])


AC_OUTPUT

AC_MSG_RESULT([
        solus-hardware-config $VERSION
        ========

        prefix:                 ${prefix}
        libdir:                 ${libdir}
        sysconfdir:             ${sysconfdir}
        exec_prefix:            ${exec_prefix}
        bindir:                 ${bindir}
        datarootdir:            ${datarootdir}
])
