# ----------------------------------------------------------------------------
#  Root CMake file for Neron proj
# ----------------------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 2.7)

project(first_step_in_lua)

SET( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )
SET( HELIUM_THIRD_PARTY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/thirdparty/builds/product/ )

FIND_PACKAGE( Lua REQUIRED )

IF( CMAKE_BUILD_TYPE STREQUAL Release )
    SET ( HELIUM_THIRDPARTY_LIB
            ${LUA_LIBRARY_DEBUG}
        )

ELSEIF( CMAKE_BUILD_TYPE STREQUAL Debug )
    SET ( HELIUM_THIRDPARTY_LIB
            ${LUA_LIBRARY_DEBUG}
        )

ELSE()
    MESSAGE (ERROR "CMAKE_BUILD_TYPE must be defined")
ENDIF()

INCLUDE_DIRECTORIES( ${LUA_INCLUDE_DIR} )

SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )

SET( SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp )
SET( HEADERS )

ADD_EXECUTABLE ( first_step_in_lua 
                    ${SOURCES}
                    ${HEADERS}      
               )

target_link_libraries( first_step_in_lua ${HELIUM_THIRDPARTY_LIB} )

