# Configure systemd coredump itself
install_data(
    '00-coredumpd-solus.conf',
    install_dir: path_coredump_conf,
)

# Configure systemd coredump behaviour (global, manager)
install_data(
    '00-manager-coredump-solus.conf',
    install_dir: path_systemd_conf,
)

install_data(
    '60-solus-coredump.conf',
    install_dir: path_sysctl_dir,
)