cmake_minimum_required(VERSION 3.16)
project(Importer C)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Engine")
add_definitions(-DEZXML_NOMMAP)

add_executable(Importer
    ezxml/ezxml.c
    ezxml/ezxml.h
    md5/md5.c
    md5/md5.h
    image.c
    importer.h
    main.c
    output.c
    stb_image.h
    tilecache.c
    tilemap.c
    tileset.c
    util.c
    )
