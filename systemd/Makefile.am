EXTRA_DIST = \
	on-demand-cpupower.service \
	on-demand-cpupower-switch \
	00-coredump-solus.conf

systemdsystemunitdir = $(prefix)/lib/systemd/system
systemdsystemunit_DATA = on-demand-cpupower.service

sbin_SCRIPTS = \
	on-demand-cpupower-switch

coredumpdir = $(prefix)/lib/systemd/coredump.conf.d
coredump_DATA = 00-coredump-solus.conf
