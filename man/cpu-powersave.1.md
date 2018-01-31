cpu-powersave(1) -- Transition CPU governor
===========================================


## SYNOPSIS

`cpu-powersave [subcommand]`


## DESCRIPTION

`cpu-powersave` is a system binary used during the boot process to transition
the CPU governor from the default `performance` into the appropriate powersaving governor
supported by the kernel driver.

For `intel_pstate` systems all cores will transition to the `powersave` governor, whereas
traditional `cpufreq` systems will transition to the `ondemand` governor.

   
## SUBCOMMANDS


`start`

    Switch the governor to the appropriate powersaving option
    on all cores.

`stop`

    Switch the governor to the appropriate `performance` option
    on all cores.

`help`

    Print the supported command set for the program.

`version`

    Print the version and license information, before quitting.
   

## EXIT STATUS

On success, 0 is returned. A non-zero return code signals a failure.


## COPYRIGHT

 * Copyright © 2018 Solus Project, License: CC-BY-SA-3.0


## SEE ALSO

 * https://github.com/solus-project/solus-hardware-config

## NOTES

Creative Commons Attribution-ShareAlike 3.0 Unported

 * http://creativecommons.org/licenses/by-sa/3.0/
