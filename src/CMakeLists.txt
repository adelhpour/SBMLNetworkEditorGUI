set(CMAKE_AUTOMOC ON)

### build the main
## set the required sources
set(gui_sources
	libsbml_ne_main.cpp
	libsbml_ne_main_window.cpp
	libsbml_ne_interactor.cpp
	libsbml_ne_graphics_view.cpp
	libsbml_ne_graphics_scene.cpp
	libsbml_ne_network_element.cpp
	libsbml_ne_compartment.cpp
	libsbml_ne_species.cpp
	libsbml_ne_reaction.cpp
	libsbml_ne_species_reference.cpp
	libsbml_ne_text.cpp
	libsbml_ne_network_element_builder.cpp
	libsbml_ne_element_graphics_item.cpp
	libsbml_ne_1d_shape_graphics_item.cpp
	libsbml_ne_curve_graphics_item.cpp
	libsbml_ne_2d_shape_graphics_item.cpp
	libsbml_ne_rect_graphics_item.cpp
	libsbml_ne_ellipse_graphics_item.cpp
	libsbml_ne_polygon_graphics_item.cpp
	libsbml_ne_text_graphics_item.cpp
	libsbml_ne_feature_menu.cpp)

## set the required headers
set(gui_headers
	libsbml_ne_main_window.h
	libsbml_ne_interactor.h
	libsbml_ne_graphics_view.h
	libsbml_ne_graphics_scene.h
	libsbml_ne_network_element.h
	libsbml_ne_compartment.h
	libsbml_ne_species.h
	libsbml_ne_reaction.h
	libsbml_ne_species_reference.h
	libsbml_ne_text.h
	libsbml_ne_network_element_builder.h
	libsbml_ne_element_graphics_item.h
	libsbml_ne_1d_shape_graphics_item.h
	libsbml_ne_curve_graphics_item.h
	libsbml_ne_2d_shape_graphics_item.h
	libsbml_ne_rect_graphics_item.h
	libsbml_ne_ellipse_graphics_item.h
	libsbml_ne_polygon_graphics_item.h
	libsbml_ne_text_graphics_item.h
	libsbml_ne_feature_menu.h)

## build the bundle/executable
add_executable(LIBSBML_NETWORKEDITOR_GUI WIN32 MACOSX_BUNDLE 
	${gui_sources})

## include directories
target_include_directories(LIBSBML_NETWORKEDITOR_GUI PUBLIC
	${LIBSBML_NETWORKEDITOR_INCLUDEDIR}
	${CMAKE_SOURCE_DIR}/src)

## link libraries
target_link_libraries(LIBSBML_NETWORKEDITOR_GUI
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets
	Qt5::PrintSupport
	${LIBSBML_NETWORKEDITOR_LIBS}
	${LIBSBML_NETWORKEDITOR_DEPENDENCIES_LIBS})

set(DEPENDENCIES_BUILD_DIR ${CMAKE_BINARY_DIR}/src/dependencies)
add_custom_command(TARGET LIBSBML_NETWORKEDITOR_GUI POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${DEPENDENCIES_BUILD_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIBSBML_NETWORKEDITOR_LIBS} ${DEPENDENCIES_BUILD_DIR})

if (APPLE)
	## set the info plist
	set_target_properties(LIBSBML_NETWORKEDITOR_GUI PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/src/Info.Plist)
	
	add_custom_command(TARGET LIBSBML_NETWORKEDITOR_GUI POST_BUILD
		COMMAND ${CMAKE_INSTALL_NAME_TOOL} -change
		"libsbml.5.dylib" "@rpath/libsbml.5.dylib" $<TARGET_FILE:LIBSBML_NETWORKEDITOR_GUI>)
endif ()