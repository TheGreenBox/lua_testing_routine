# ----------------------------------------------------------------------------
#  Root CMake file for Neron proj
# ----------------------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(first_step_in_lua)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#FIND_PACKAGE(OpenCV REQUIRED)
##LIST( APPEND HEADERS ${OpenCV_INCLUDE_DIR} )
##LIST( APPEND REQUIRED_LIBRARIES ${OpenCV_LIBS} ) 
   
SET( SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp )
SET( HEADERS )

ADD_EXECUTABLE ( first_step_in_lua 
                    ${SOURCES}
                    ${HEADERS}      
               )

#target_link_libraries( Neron ${REQUIRED_LIBRARIES} )

