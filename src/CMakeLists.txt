add_library(
	NGLib
		NGApplication.cpp
		NGAppMain.cpp
		NGPropertySavingRestoring.cpp
		NGRestorer.cpp
		NGSavable.cpp
		NGSelfSavable.cpp
)

ecm_generate_export_header(NGLib
	VERSION 1.0.0
)

install(
	TARGETS
		NGLib
	DESTINATION
		${KDE_INSTALL_LIBDIR}
)

install(
	FILES
		NGLib.h

		NGApplication.h
		NGAppMain.h
		NGPropertySavingRestoring.h
		NGRestorer.h
		NGSavable.h
		NGSelfSavable.h

		${CMAKE_CURRENT_BINARY_DIR}/nglib_export.h
	DESTINATION
		${KDE_INSTALL_INCLUDEDIR}/NGLib
)

target_include_directories(NGLib
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
    INTERFACE "$<INSTALL_INTERFACE:${NGLIB_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(NGLib
	PUBLIC
		Qt5::Core Qt5::Gui Qt5::Widgets
		KF5::CoreAddons KF5::I18n KF5::ConfigCore KF5::ConfigGui
)

ecm_generate_pkgconfig_file(
	BASE_NAME
		NGLib
	DEPS
		Qt5Core Qt5Gui Qt5Widgets
	FILENAME_VAR
		nglib
	INSTALL
)
