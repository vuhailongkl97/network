bin_PROGRAMS = target
lib_LTLIBRARIES = liblong.la

liblong_la_SOURCES=list_iface.c
target_LDADD = liblong.la

target_SOURCES = main.c
if  MY_FLAGS_SET
target_CFLAGS = -DLONGKK
else
target_CFLAGS = -DNO_FLAG
endif
