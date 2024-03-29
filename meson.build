project(
    'solus-hardware-config',
    ['c'],
    version: '16',
    license: [
        'MIT',
    ],
    default_options: [
        'c_std=c11',
        'prefix=/usr',
        'sysconfdir=/etc',
        'localstatedir=/var',
    ],
)

am_cflags = [
    '-fstack-protector',
    '-Wall',
    '-pedantic',
    '-Wstrict-prototypes',
    '-Wundef',
    '-fno-common',
    '-Werror-implicit-function-declaration',
    '-Wformat',
    '-Wformat-security',
    '-Werror=format-security',
    '-Wconversion',
    '-Wunused-variable',
    '-Wunreachable-code',
    '-W',
]

# Add our main flags
add_global_arguments(am_cflags, language: 'c')

# Get configuration bits together
path_prefix = get_option('prefix')
path_sysconfdir = join_paths(path_prefix, get_option('sysconfdir'))
path_libdir = join_paths(path_prefix, get_option('libdir'))
path_mandir = join_paths(path_prefix, get_option('mandir'))
path_datadir = join_paths(path_prefix, get_option('datadir'))
path_sbindir = join_paths(path_prefix, get_option('sbindir'))

# Grab systemd specifics
message('Asking pkg-config for systemd\'s directories')
dep_systemd = dependency('systemd')
systemd_util_dir = dep_systemd.get_pkgconfig_variable('systemdutildir')

path_systemd_conf = join_paths(systemd_util_dir, 'system.conf.d')
path_systemd_unit_dir = dep_systemd.get_pkgconfig_variable('systemdsystemunitdir')
path_sysctl_dir = dep_systemd.get_pkgconfig_variable('sysctldir')


# Modprobe is a bit of an odd ball
path_modprobe_dir = join_paths(path_libdir, 'modprobe.d')

# Sort out config.h now
cdata = configuration_data()

# X11 
path_x11_dir = join_paths(path_datadir, 'X11', 'xorg.conf.d')

# General options..
cdata.set_quoted('PACKAGE_NAME', meson.project_name())
cdata.set_quoted('PACKAGE_VERSION', meson.project_version())
cdata.set_quoted('PACKAGE_URL', 'https://solus-project.com')

# Write config.h now
config_h = configure_file(
     configuration: cdata,
     output: 'config.h',
)
config_h_dir = include_directories('.')

subdir('modprobe')
subdir('tweaks')
subdir('xorg')
subdir('cpu-powersave')
subdir('man')

report = [
    '    Build configuration:',
    '    ====================',
    '',
    '    prefix:                                 @0@'.format(path_prefix),
    '    mandir:                                 @0@'.format(path_mandir),
    '    datadir:                                @0@'.format(path_datadir),
    '    sysconfdir:                             @0@'.format(path_sysconfdir),
    '    libdir:                                 @0@'.format(path_libdir),
    '    sbindir:                                @0@'.format(path_sbindir),
    '',
    '    Directories:',
    '    ============',
    '',
    '    systemd unit directory:                @0@'.format(path_systemd_unit_dir),
    '    sysctl.d:                              @0@'.format(path_sysctl_dir),
    '    system.conf.d:                         @0@'.format(path_systemd_conf),
    '    modprobe.d:                            @0@'.format(path_modprobe_dir),
    '    X11 config:                            @0@'.format(path_x11_dir),
]

# Output some stuff to validate the build config
message('\n\n\n' + '\n'.join(report) + '\n\n')
