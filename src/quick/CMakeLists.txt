add_library(
	NGLibQuick
		NGBeacon.cpp
		NGBeaconController.cpp
		NGBeaconControllerDelegate.cpp
		NGToolBarItem.cpp
		NGToolBarController.cpp
		NGToolBarDelegate.cpp
)

ecm_generate_export_header(
	NGLibQuick
	VERSION
		${CMAKE_PROJECT_VERSION}
)

install(
	TARGETS
		NGLibQuick
	DESTINATION
		${KDE_INSTALL_LIBDIR}
)

install(
	FILES
		NGLibQuick.h

		NGBeacon.h
		NGBeaconController.h
		NGBeaconControllerDelegate.h
		NGToolBarController.h
		NGToolBarDelegate.h
		NGToolBarItem.h

		${CMAKE_CURRENT_BINARY_DIR}/nglibquick_export.h
	DESTINATION
		${KDE_INSTALL_INCLUDEDIR}/NGLibQuick
)

target_include_directories(NGLibQuick
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}
    INTERFACE "$<INSTALL_INTERFACE:${NGLIB_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(NGLibQuick
	PUBLIC
		Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick
		KF5::CoreAddons KF5::I18n KF5::ConfigCore KF5::ConfigGui
		NGLib
)

ecm_generate_pkgconfig_file(
	BASE_NAME
		NGLibQuick
	DEPS
		Qt5Core Qt5Gui Qt5Widgets Qt5Quick
	FILENAME_VAR
		nglibquick
	INSTALL
)
