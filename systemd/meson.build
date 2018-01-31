install_data(
    'on-demand-cpupower.service',
    install_dir: path_systemd_unit_dir,
)

# Configure systemd coredump itself
install_data(
    '00-coredump-solus.conf',
    install_dir: path_coredump_conf,
)

# Configure systemd coredump behaviour (global, manager)
install_data(
    '00-solus-coredump.conf',
    install_dir: path_systemd_conf,
)

# CPU on-demand script (needs rewriting to not suck.)
install_data(
    'on-demand-cpupower-switch',
    install_dir: path_sbindir,
)