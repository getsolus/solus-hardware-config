# solus-hardware-config

[![License](https://img.shields.io/badge/License-GPL%202.0-blue.svg)](https://opensource.org/licenses/GPL-2.0)

This package contains configuration data and utilities required by all Solus installations, with various tweaks, to ensure proper performance and hardware functionality.

`solus-hardware-config` is a [Solus project](https://solus-project.com/)

![logo](https://build.solus-project.com/logo.png)

## Components

### coredump

Data snippets to nuke systemd coredump behaviour from orbit. Solus contains full `-dbginfo` packages that users can install to use `gdb` to debug problematic software with guidance from the team. Persistent automatic coredumps lead to security risks, not to mention massive performance issues when large processes dump. Additionally, they take up a massive amount of disk space.

### cpu-on-demand

Trivial boot service to move the system into powersave/on-demand CPU governor. The Solus kernel is configured to prefer `performance` by default, and lazily changing this later in the boot helps to maintain decent boot times as well as being conservative with battery life.

### modprobe

Various `modprobe.d` snippets to fix and blacklist certain hardware.

### tweaks

`sysctl` and `udev` tweaks, i.e. HDD scheduler and such.

### xorg

Legacy X11 snippets for problematic hardware. Should be unnecessary when using `libinput`.


## Authors

Copyright © 2016-2018 Solus Project

`solus-hardware-config` is available under the terms of the `GPL-2.0` license.

Data files can be distributed under the terms of the `GPL-2.0` or `MIT` license, at your discretion.
