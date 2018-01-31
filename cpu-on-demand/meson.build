install_data(
    'on-demand-cpupower.service',
    install_dir: path_systemd_unit_dir,
)

executable(
    'on-demand-cpupower-switch',
    sources: [
        'main.c',
    ],
    install: true,
    install_dir: path_sbindir,
)