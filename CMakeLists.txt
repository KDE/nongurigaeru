# SPDX-FileCopyrightText: 2022 Janet Blackquill <uhhadd@gmail.com>
#
# SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

cmake_minimum_required(VERSION 3.16)

set(NONGURIGAERU_VERSION "1.0.0")
set(QT_MIN_VERSION "6.5.2")
set(KF_MIN_VERSION "6.3.0")

project(NGLib LANGUAGES CXX VERSION ${NONGURIGAERU_VERSION})

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_NGLIB_QUICK "Builds Nongurigaeru's components for QtQuick" ON)

find_package(ECM 5.240.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
include(ECMSetupVersion)
include(ECMGeneratePkgConfigFile)
include(ECMGenerateExportHeader)

set(NGLIB_INSTALL_INCLUDEDIR "${KDE_INSTALL_INCLUDEDIR}/NGLib")
set(NGLIBQUICK_INSTALL_INCLUDEDIR "${KDE_INSTALL_INCLUDEDIR}/NGLibQuick")

ecm_setup_version(
	${NONGURIGAERU_VERSION}
	VARIABLE_PREFIX NONGURIGAERU
	VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/nongurigaeru_version.h"
	PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/NongurigaeruConfigVersion.cmake"
)

find_package(
	Qt6 ${QT_MIN_VERSION}
	COMPONENTS
		Core Gui Widgets
	REQUIRED
)

if (BUILD_NGLIB_QUICK)
	find_package(
		Qt6 ${QT_MIN_VERSION}
		COMPONENTS
			Quick
		REQUIRED
	)
endif()

find_package(
	KF6 ${KF_MIN_VERSION}
	COMPONENTS
		CoreAddons I18n Config
	REQUIRED
)

add_subdirectory(src)

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/Nongurigaeru")
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/NongurigaeruConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/NongurigaeruConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
  PATH_VARS  KDE_INSTALL_INCLUDEDIR CMAKE_INSTALL_PREFIX
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/NongurigaeruConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/NongurigaeruConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT NongurigaeruTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE NongurigaeruTargets.cmake NAMESPACE KF6:: )

if (BUILD_NGLIB_QUICK)
	add_subdirectory(src/quick)
	add_subdirectory(src/quick/plugin)
endif()

if (BUILD_TESTING)
	add_subdirectory(test)
endif()
