add_library(
	NGLibQuickPlugin SHARED

		NGQuickPlugin.cpp
		PrivateToolBarViewDelegate.cpp
		Resources.qrc
		controls/qmldir
)

target_link_libraries(
	NGLibQuickPlugin
	PRIVATE
		NGLibQuick
)

if (BUILD_SHARED_LIBS)
	install(DIRECTORY controls/ DESTINATION ${KDE_INSTALL_QMLDIR}/Nongurigaeru)
	install(TARGETS NGLibQuickPlugin DESTINATION ${KDE_INSTALL_QMLDIR}/Nongurigaeru)
endif()
