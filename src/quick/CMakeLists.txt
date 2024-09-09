# SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
#
# SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

add_library(
	NGLibQuick
		NGBeacon.cpp
		NGBeaconController.cpp
		NGBeaconControllerDelegate.cpp
		NGToolBarItem.cpp
		NGToolBarController.cpp
		NGToolBarDelegate.cpp
)

target_compile_options(
	NGLibQuick
	PRIVATE
		-Werror=deprecated-declarations
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
	EXPORT
		NongurigaeruTargets
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
    INTERFACE "$<INSTALL_INTERFACE:${NGLIBQUICK_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(NGLibQuick
	PUBLIC
		Qt::Core Qt::Gui Qt::Widgets Qt::Quick
		KF6::CoreAddons KF6::I18n KF6::ConfigCore KF6::ConfigGui
		NGLib
)

ecm_generate_pkgconfig_file(
	BASE_NAME
		NGLibQuick
	DEPS
		Qt6Core Qt6Gui Qt6Widgets Qt6Quick
	FILENAME_VAR
		nglibquick
	INSTALL
)
