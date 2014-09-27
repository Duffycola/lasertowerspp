cmake_minimum_required (VERSION 2.8)

project( LaserTowersPP )
set( PROJECT_VERSION "1.0" )
set( SRC_DIR "lasertowerspp" )
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)




# OpenCV Package required
find_package( OpenCV REQUIRED )
if (${OpenCV_VERSION} VERSION_LESS 2.3.0)
	message( fatal_error "OpenCV version is not compatible: ${OpenCV_VERSION}")
endif()

find_package( OpenGL REQUIRED )
find_package( GLUT REQUIRED )


set ( OTHER_INCLUDE_DIRS
		${OpenCV_INCLUDE_DIR}
		${OPENGL_INCLUDE_DIRS}
		${GLUT_INCLUDE_DIRS}
)
set ( OTHER_LIBS
		${OpenCV_LIBS}
		${OPENGL_LIBRARIES}
		${GLUT_LIBRARIES}
)


# Setting predefined Flags
if( UNIX )
    set( CMAKE_CXX_FLAGS "-std=c++11" )
endif ()

if( APPLE ) 
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
    SET( CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++" )
endif()


#############################
# Source Folder and files
#############################
SET (SRC_DIR src)

file(GLOB HEADER_FILES
    ${SRC_DIR}/*.h
    ${SRC_DIR}/lasertowerspp/*.h
    ${SRC_DIR}/opengl/*.h
)

file(GLOB SRC_FILES
	${SRC_DIR}/*.cpp
    ${SRC_DIR}/lasertowerspp/*.cpp
    ${SRC_DIR}/opengl/*.cpp
)


include_directories( ${SRC_DIR} )
include_directories( ${SRC_DIR}/lasertowerspp )
include_directories( ${SRC_DIR}/opengl )
include_directories( ${OTHER_INCLUDE_DIRS} )


# debug
#message(STATUS ${SRC_DIR})
#message(STATUS ${HEADER_FILES})
#message(STATUS ${SRC_FILES})


#######################################
# MAIN APP
#######################################
set (EXECUTABLE lasertowerspp)
add_executable(${EXECUTABLE} ${SRC_FILES} )
target_link_libraries( ${EXECUTABLE} ${OTHER_LIBS} )

