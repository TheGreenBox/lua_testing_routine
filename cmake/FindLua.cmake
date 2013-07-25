
MESSAGE(STATUS "FILD LUA LIBRARY")

SET ( LUA_SEARCH_PATHS
        ${HELIUM_THIRD_PARTY_OUTPUT_PATH}/lualib/include
        ${HELIUM_THIRD_PARTY_OUTPUT_PATH}/lualib/lib
    )


FIND_PATH ( LUA_INCLUDE_DIR
	        NAMES lua.h 
	        HINTS
	        $ENV{LUADIR}
            $ENV{LUA_PATH}
            PATHS ${LUA_SEARCH_PATHS}
          )

FIND_LIBRARY ( LUA_LIBRARY 
                NAMES lua52 liblua52
                HINTS
                NO_DEFAULT_PATH
                NO_CMAKE_ENVIRONMENT_PATH
                NO_CMAKE_SYSTEM_PATH
                NO_SYSTEM_ENVIRONMENT_PATH
                NO_CMAKE_PATH
                CMAKE_FIND_FRAMEWORK NEVER
                $ENV{LUADIR}
                $ENV{LUA_PATH}
                PATH_SUFFIXES lib lib64
                PATHS ${LUA_SEARCH_PATHS}
             )

# First search for d-suffixed libs
FIND_LIBRARY ( LUA_LIBRARY_DEBUG 
                NAMES lua52_d liblua52_d
                HINTS
                NO_DEFAULT_PATH
                NO_CMAKE_ENVIRONMENT_PATH
                NO_CMAKE_SYSTEM_PATH
                NO_SYSTEM_ENVIRONMENT_PATH
                NO_CMAKE_PATH
                CMAKE_FIND_FRAMEWORK NEVER
                $ENV{LUADIR}
                $ENV{LUA_PATH}
                PATH_SUFFIXES lib lib64
                PATHS ${LUA_SEARCH_PATHS}
             )

MESSAGE ( STATUS "Lua was found:" )
MESSAGE ( STATUS ${LUA_LIBRARY}  )
MESSAGE ( STATUS ${LUA_LIBRARY_DEBUG} )

