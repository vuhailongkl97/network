bin_PROGRAMS = target
noinst_LIBRARIES= liblong.a

liblong_a_SOURCES=list_iface.c
target_LDADD = -L. -llong
target_SOURCES = main.c
if  MY_FLAGS_SET
list_inf_CFLAGS = -DLONGKK
else
list_inf_CFLAGS = -DNO_FLAG
endif
