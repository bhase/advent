# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.c" "calendar.c"  "max72xx.c"  "spi.c")
set(COMPONENT_ADD_INCLUDEDIRS "")

register_component()
