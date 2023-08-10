# solus-hardware-config

[![License](https://img.shields.io/badge/License-GPL%202.0-blue.svg)](https://opensource.org/licenses/GPL-2.0)

This package contains configuration data and utilities required by all Solus installations, with various tweaks, to ensure proper performance and hardware functionality.

`solus-hardware-config` is a [Solus project](https://getsol.us/)

![logo](https://build.getsol.us/logo.png)

## Components

### cpu-powersave

Trivial boot service to move the system into powersave/on-demand CPU governor. The Solus kernel is configured to prefer `performance` by default, and lazily changing this later in the boot helps to maintain decent boot times as well as being conservative with battery life.

### modprobe

Various `modprobe.d` snippets to fix and blacklist certain hardware.

### tweaks

`sysctl` tweaks. Previously contained HDD tweaks but has since been removed.

### xorg

Legacy X11 snippets for problematic hardware. Should be unnecessary when using `libinput`.


## Authors

Copyright © 2016-2018 Solus Project

`solus-hardware-config` is available under the terms of the `GPL-2.0` license.

Data files can be distributed under the terms of the `GPL-2.0` or `MIT` license, at your discretion.
