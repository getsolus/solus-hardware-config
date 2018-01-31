data_conf = configuration_data()
data_conf.set('SBINDIR', path_sbindir)

configure_file(
    input: 'on-demand-cpupower.service.in',
    output: 'on-demand-cpupower.service',
    configuration: data_conf,
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