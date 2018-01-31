install_data(
    'on-demand-cpupower.service',
    install_dir: path_systemd_unit_dir,
)

executable(
    'on-demand-cpupower-switch',
    sources: [
        'main.c',
    ],
    include_directories: [
        config_h_dir,
    ],
    install: true,
    install_dir: path_sbindir,
)