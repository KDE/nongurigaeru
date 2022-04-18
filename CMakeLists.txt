cmake_minimum_required(VERSION 3.16)

project(NGLib LANGUAGES CXX VERSION 1.0.0)

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
find_package(
	KF5
	COMPONENTS
		CoreAddons I18n Config
	REQUIRED
)

add_subdirectory(src)
