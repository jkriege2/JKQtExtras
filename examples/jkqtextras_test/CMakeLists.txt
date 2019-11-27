cmake_minimum_required(VERSION 3.0)

set(EXAMPLE_NAME jkqtextras_test)
set(EXENAME ${EXAMPLE_NAME})

message( STATUS "..   Building Example ${EXAMPLE_NAME}" )


# Set up source files
set(SOURCES
    jkqtextras_test.cpp
    testmainwindow.cpp
    )
set(HEADERS
    testmainwindow.h
    )
set(RESOURCES  )
set(UIS
    testmainwindow.ui
    )

add_executable(${EXENAME} WIN32 ${SOURCES} ${HEADERS} ${RESOURCES} ${UIS})
target_include_directories(${EXENAME} PRIVATE ../../lib)
if(JKQtExtras_BUILD_STATIC_LIBS)
    target_link_libraries(${EXENAME} JKQtExtrasLib)
elseif(JKQtExtras_BUILD_SHARED_LIBS)
    target_link_libraries(${EXENAME} JKQtExtrasSharedLib)
endif()



# Installation
install(TARGETS ${EXENAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

#Installation of Qt DLLs on Windows
jkqtextras_deployqt(${EXENAME})
