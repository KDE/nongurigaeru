# SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
#
# SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

cmake_minimum_required(VERSION 3.16)

project(NGLib LANGUAGES CXX VERSION 1.0.0)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_NGLIB_QUICK "Builds Nongurigaeru's components for QtQuick" ON)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
include(ECMGeneratePkgConfigFile)
include(ECMGenerateExportHeader)

find_package(
	Qt5
	COMPONENTS
		Core Gui Widgets
	REQUIRED
)

if (BUILD_NGLIB_QUICK)
	find_package(
		Qt5
		COMPONENTS
			Quick
		REQUIRED
	)
endif()

find_package(
	KF5
	COMPONENTS
		CoreAddons I18n Config
	REQUIRED
)

add_subdirectory(src)

if (BUILD_NGLIB_QUICK)
	add_subdirectory(src/quick)
	add_subdirectory(src/quick/plugin)
endif()

if (BUILD_TESTING)
	add_subdirectory(test)
endif()
