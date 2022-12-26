cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(sbml_networkeditor_gui)

include(GNUInstallDirs)

## Determine the version
set(SBML_NETWORKEDITOR_GUI_VERSION_MAJOR)
set(SBML_NETWORKEDITOR_GUI_VERSION_MINOR)
set(SBML_NETWORKEDITOR_GUI_VERSION_PATCH)
set(SBML_NETWORKEDITOR_GUI_VERSION_RELEASE)
set(SBML_NETWORKEDITOR_GUI_DOTTED_VERSION)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt")
    file(STRINGS "${CMAKE_SOURCE_DIR}/VERSION.txt" VersionString NEWLINE_CONSUME)
    string(STRIP "${VersionString}" VersionString)
    set(SBML_NETWORKEDITOR_GUI_DOTTED_VERSION ${VersionString})
    string(REPLACE "." ";" VersionString "${VersionString}" )
    string(REPLACE "-" ";" VersionString "${VersionString}" )
    list(LENGTH VersionString versionLength)
    list(GET VersionString 0 SBML_NETWORKEDITOR_GUI_VERSION_MAJOR)
    list(GET VersionString 1 SBML_NETWORKEDITOR_GUI_VERSION_MINOR)
    list(GET VersionString 2 SBML_NETWORKEDITOR_GUI_VERSION_PATCH)
endif()

if(WIN32)
	## on windows Ws2_32.lib is needed to be included for the dll
    	list(APPEND EXTRA_LIBS "Ws2_32.lib")

	## get libsbml_networkeditor directories
	set(LIBSBML_NETWORKEDITOR_PREFIX "C:/Program Files/libsbml_networkeditor" CACHE PATH "libSBML_NeworkEditor root directory (contains lib, include, etc.)")
	file(GLOB LIBSBML_NETWORKEDITOR_LIBS "${LIBSBML_NETWORKEDITOR_PREFIX}/lib/*.lib")
	file(GLOB LIBSBML_NETWORKEDITOR_DEPENDENCIES_LIBS "${LIBSBML_NETWORKEDITOR_PREFIX}/lib/dependencies/*.lib")
	file(GLOB LIBSBML_NETWORKEDITOR_DLLS "${LIBSBML_NETWORKEDITOR_PREFIX}/bin/*.dll")
	file(GLOB LIBSBML_NETWORKEDITOR_DEPENDENCIES_DLLS "${LIBSBML_NETWORKEDITOR_PREFIX}/bin/dependencies/*.dll")
elseif(UNIX)
	## get libsbml_networkeditor directories
	set(LIBSBML_NETWORKEDITOR_PREFIX "/usr/local" CACHE PATH "libSBML_NeworkEditor root directory (contains lib, include, etc.)")
	
	## set use of RPATH for Mac
	if (APPLE)
		file(GLOB LIBSBML_NETWORKEDITOR_LIBS "${LIBSBML_NETWORKEDITOR_PREFIX}/lib/*.dylib")
		file(GLOB LIBSBML_NETWORKEDITOR_DEPENDENCIES_LIBS "${LIBSBML_NETWORKEDITOR_PREFIX}/lib/dependencies/*.dylib")
		set(CMAKE_MACOSX_RPATH true)
		set(CMAKE_BUILD_RPATH "${CMAKE_BINARY_DIR}/src;${CMAKE_BINARY_DIR}/src/dependencies")
		set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_RPATH} "@loader_path;@loader_path/../Frameworks;@loader_path/../Frameworks/dependencies")

		## set C/C++ compiler flags
    		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall -Wno-inline")
    		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fPIC -std=gnu++11")
	else ()
		file(GLOB LIBSBML_NETWORKEDITOR_LIBS ${LIBSBML_NETWORKEDITOR_PREFIX}/lib/*.so)
		set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_RPATH} "$ORIGIN;;$ORIGIN/../lib/dependencies")
		## set C/C++ compiler flags
    		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall -Wno-inline")
    		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fPIC -std=gnu++11 -Wl,--disable-new-dtags")
	endif()

	## set RPATH features
	set(CMAKE_SKIP_BUILD_RPATH FALSE)
	set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
	set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif ()

set(LIBSBML_NETWORKEDITOR_INCLUDEDIR ${LIBSBML_NETWORKEDITOR_PREFIX}/include)


## find Qt5 and required components
find_package(Qt5 COMPONENTS Core Gui Widgets DBus PrintSupport REQUIRED)

## Set build type default.
set(CMAKE_BUILD_TYPE "Release" CACHE STRING
  "Choose the type of build to perform. The options are: Debug, Release, RelWithDebInfo, MinSizeRel.")
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release" FORCE)
endif()

add_subdirectory(src)