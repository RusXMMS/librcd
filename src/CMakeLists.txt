if (NOT WIN32)
    SET(BUILD_SHARED_LIBS ON)
endif (NOT WIN32)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(HEADERS 
    librcd.h
)

SET(rcd_SRCS
    librcd.c
    russian_table.h
    ${HEADERS}
)

ADD_LIBRARY(rcd ${rcd_SRCS})
