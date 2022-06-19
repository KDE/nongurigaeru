// SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.15 as Kirigami
import Nongurigaeru 1.0 as NGLib
import Nongurigaeru.Private 1.0

QQC2.ToolBar {
	id: _control

	required property bool editing
	required property NGLib.ToolBarController controller
	property QtObject outlet: null
	readonly property NGLib.BeaconController beaconController: _beaconController

	NGLib.BeaconController {
		id: _beaconController
		parent: _control
		anchors.fill: parent
		delegate: PrivateToolBarViewDelegate {
			controller: _control.controller
		}
	}

	contentItem: GridLayout {
		Repeater {
			model: _control.controller.items

			delegate: Loader {
				id: _loader

				required property var modelData
				required property int index

				sourceComponent: modelData.component

				Layout.fillWidth: item ? item.Layout.fillWidth : false
				Layout.fillHeight: item ? item.Layout.fillHeight : false

				onItemChanged: {
					_blockMouseArea.parent = _loader.item
					_blockMouseArea.anchors.fill = _loader.item
				}
				BlockMouseArea {
					id: _blockMouseArea
					enabled: _control.editing
				}

				Binding {
					target: _loader.item
					property: "outlet"
					value: _control.outlet || _control.controller.outlet
				}

				DragHandler {
					target: null
					enabled: _control.editing
					onActiveChanged: {
						if (active) {
							_loader.item.grabToImage((result) => {
								_control.controller.removeItemAt(_loader.index)
								_loader.Drag.imageSource = result.url
								_loader.Drag.active = active
							})
						} else {
							_loader.Drag.active = active
						}
					}
				}
				Drag.dragType: Drag.Automatic
				Drag.mimeData: {
					"application/x-nongurigaeru-toolbar-item": _loader.modelData.identifier
				}

				NGLib.Beacon {
					id: beforeBeacon

					controller: beaconController
					beaconID: "before" + _loader.index
					dataCallback: () => ["before", _loader.index]

					anchors.top: parent.top
					anchors.bottom: parent.bottom
					anchors.left: parent.left
					width: 1
				}
				Rectangle {
					anchors.top: parent.top
					anchors.bottom: parent.bottom
					anchors.left: parent.left
					width: 2
					visible: _beaconController.activeBeaconID == beforeBeacon.beaconID
					color: Kirigami.Theme.highlightColor
					z: 500
				}
				NGLib.Beacon {
					id: afterBeacon

					controller: beaconController
					beaconID: "after" + _loader.index
					dataCallback: () => ["after", _loader.index]

					anchors.top: parent.top
					anchors.bottom: parent.bottom
					anchors.right: parent.right
					width: 1
				}
				Rectangle {
					anchors.top: parent.top
					anchors.bottom: parent.bottom
					anchors.right: parent.right
					width: 2
					visible: _beaconController.activeBeaconID == afterBeacon.beaconID
					color: Kirigami.Theme.highlightColor
					z: 500
				}
			}
		}
	}
}
