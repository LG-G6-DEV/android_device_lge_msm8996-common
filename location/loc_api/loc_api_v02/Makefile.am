AM_CFLAGS = \

            ${QMIF_CFLAGS} \
            -I../../utils \
            -I../../platform_lib_abstractions \
            -I../libloc_api_50001

requiredlibs = \
            ${QMIF_LIBS} \
            ../libloc_api_50001/libloc_adapter_so.la \
            ../../utils/libgps_utils_so.la

h_sources = LocApiV02Adapter.h \
            loc_util_log.h \
            location_service_v02.h \
            loc_api_sync_req.h \
            loc_api_v02_client.h \
            loc_api_v02_log.h

c_sources = LocApiV02Adapter.cpp \
            loc_api_v02_log.c \
            loc_api_v02_client.c \
            loc_api_sync_req.c \
            location_service_v02.c

library_includedir = $(pkgincludedir)
library_include_HEADERS = $(h_sources)

libloc_api_la_SOURCES = $(c_sources) $(h_sources)

if USE_GLIB
libloc_api_la_CFLAGS = -DUSE_GLIB $(AM_CFLAGS) @GLIB_CFLAGS@
libloc_api_la_LDFLAGS = -lstdc++ -Wl,-z,defs -lpthread @GLIB_LIBS@ -shared -version-info 1:0:0
libloc_api_la_CPPFLAGS = -DUSE_GLIB $(AM_CFLAGS) $(AM_CPPFLAGS) @GLIB_CFLAGS@
else
libloc_api_la_CFLAGS = $(AM_CFLAGS)
libloc_api_la_LDFLAGS = -shared -Wl,-z,defs -version-info 1:0:0
libloc_api_la_CPPFLAGS = $(AM_CFLAGS) $(AM_CPPFLAGS)
endif

libloc_api_la_LIBADD = $(requiredlibs) -lstdc++

lib_LTLIBRARIES = libloc_api.la

    -I. \
    $(LOCPLA_CFLAGS) \
    $(GPSUTILS_CFLAGS) \
    $(LOC_CORE_CFLAGS) \
    $(LOCDS_CFLAGS) \
    $(QMIFW_CFLAGS) \
    -fno-short-enums \
    -D__func__=__PRETTY_FUNCTION__ \
    -DTARGET_USES_QCOM_BSP

libloc_api_v02_la_SOURCES = \
    LocApiV02.cpp \
    loc_api_v02_log.c \
    loc_api_v02_client.c \
    loc_api_sync_req.c \
    location_service_v02.c

if USE_GLIB
libloc_api_v02_la_CFLAGS = -DUSE_GLIB $(AM_CFLAGS) @GLIB_CFLAGS@
libloc_api_v02_la_LDFLAGS = -lstdc++ -Wl,-z,defs @GLIB_LIBS@ -shared -version-info 1:0:0
libloc_api_v02_la_CPPFLAGS = -DUSE_GLIB $(AM_CFLAGS) $(AM_CPPFLAGS) @GLIB_CFLAGS@
else
libloc_api_v02_la_CFLAGS = $(AM_CFLAGS)
libloc_api_v02_la_LDFLAGS = -lstdc++ -Wl,-z,defs -shared -version-info 1:0:0
libloc_api_v02_la_CPPFLAGS = $(AM_CFLAGS) $(AM_CPPFLAGS)
endif

libloc_api_v02_la_CXXFLAGS = -std=c++0x
libloc_api_v02_la_LIBADD = -lstdc++ -ldl -lutils $(QMIFW_LIBS) $(GPSUTILS_LIBS) $(LOC_CORE_LIBS)

library_include_HEADERS = \
    location_service_v02.h \
    loc_api_v02_log.h \
    loc_api_v02_client.h \
    loc_api_sync_req.h \
    LocApiV02.h \
    loc_util_log.h

library_includedir = $(pkgincludedir)/loc_api_v02

#Create and Install libraries
lib_LTLIBRARIES = libloc_api_v02.la

library_includedir = $(pkgincludedir)
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = loc-api-v02.pc
EXTRA_DIST = $(pkgconfig_DATA)

