# ----------------------------------------------------------------------------
#  Root CMake file for Helium proj
# ----------------------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 2.7)

project(first_step_in_lua)

SET( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )
SET( HELIUM_THIRD_PARTY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/thirdparty/builds/product/ )
SET( OUTCOME_PATH ${CMAKE_BINARY_DIR}/product )

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

IF(UNIX)
    SET ( HELIUM_THIRDPARTY_LIB
            ${HELIUM_THIRDPARTY_LIB}
            -ldl  # for lua lib
            -lm   # for lua lib
        )
ENDIF(UNIX)

INCLUDE_DIRECTORIES( ${LUA_INCLUDE_DIR} )

SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )

SET ( SOURCES 
        ${CMAKE_SOURCE_DIR}/src/main.cpp 
        ${CMAKE_SOURCE_DIR}/src/cardsDeck.cpp
    )

SET ( HEADERS
        ${CMAKE_SOURCE_DIR}/src/cardsDeck.h
    )

ADD_EXECUTABLE ( first_step_in_lua 
                    ${SOURCES}
                    ${HEADERS}      
               )

TARGET_LINK_LIBRARIES( first_step_in_lua ${HELIUM_THIRDPARTY_LIB} )

INSTALL ( TARGETS first_step_in_lua
            DESTINATION ${OUTCOME_PATH}
        )

INSTALL ( DIRECTORY ${CMAKE_SOURCE_DIR}/scripts
            DESTINATION ${OUTCOME_PATH}
        )

MESSAGE(STATUS "END HELIUM GENERATING")

