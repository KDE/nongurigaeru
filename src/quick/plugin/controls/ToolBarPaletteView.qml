import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import org.kde.kirigami 2.15 as Kirigami
import QtQuick.Layouts 1.15
import Nongurigaeru 1.0 as NGLib

QQC2.Control {
	id: _control

	required property NGLib.ToolBarController controller
	property QtObject outlet: null

	padding: Kirigami.Units.gridUnit
	leftPadding: padding
	rightPadding: padding
	topPadding: padding
	bottomPadding: padding

	background: Kirigami.ShadowedRectangle {
		color: Kirigami.Theme.backgroundColor
		border.width: 1
		border.color: Kirigami.ColorUtils.tintWithAlpha(color, Kirigami.Theme.textColor, 0.2)
		radius: 3
		shadow {
			size: Kirigami.Units.gridUnit
			color: Qt.rgba(0, 0, 0, 0.2)
			yOffset: 2
		}
	}
	BlockMouseArea {
		parent: _control
		anchors.fill: _control
	}
	BlockDropArea {
		parent: _control
		anchors.fill: _control
	}
	contentItem: ColumnLayout {
		spacing: Kirigami.Units.largeSpacing
		QQC2.Label {
			text: "Drag your favourite objects into the toolbar..."
			font.bold: true
			Layout.fillWidth: true
		}
		Flow {
			spacing: Kirigami.Units.gridUnit
			Layout.margins: Kirigami.Units.largeSpacing
			Layout.fillWidth: true

			Repeater {
				model: _control.controller.possibleItems
				delegate: ColumnLayout {
					id: del
					required property var modelData

					DragHandler {
						target: null
						onActiveChanged: {
							if (active) {
								_loader.item.grabToImage((result) => {
									del.Drag.imageSource = result.url
									del.Drag.active = active
								})
							} else {
								_loader.Drag.active = active
							}
						}
					}
					Drag.dragType: Drag.Automatic
					Drag.mimeData: {
						"application/x-nongurigaeru-toolbar-item": del.modelData.identifier
					}

					Loader {
						id: _loader

						sourceComponent: del.modelData.component
						onItemChanged: {
							_blockMouseArea.parent = _loader.item
							_blockMouseArea.anchors.fill = _loader.item
						}
						BlockMouseArea {
							id: _blockMouseArea
						}

						Binding {
							target: _loader.item
							property: "outlet"
							value: _control.outlet || _control.controller.outlet
						}

						Layout.alignment: Qt.AlignHCenter
					}
					QQC2.Label {
						text: del.modelData.label
						horizontalAlignment: Qt.AlignHCenter

						Layout.fillWidth: true
					}
				}
			}
		}
		QQC2.Label {
			text: "... or drag the default set into the toolbar"
			font.bold: true
			Layout.fillWidth: true
		}
		QQC2.Control {
			id: _defaultSet

			DragHandler {
				target: null
				onActiveChanged: {
					if (active) {
						_defaultSet.grabToImage((result) => {
							_defaultSet.Drag.imageSource = result.url
							_defaultSet.Drag.active = active
						})
					} else {
						_defaultSet.Drag.active = active
					}
				}
			}
			Drag.dragType: Drag.Automatic
			Drag.mimeData: {
				"application/x-nongurigaeru-toolbar-default-set": "yes"
			}
			BlockMouseArea {
				id: _blockMouseArea
				anchors.fill: parent
			}

			background: Rectangle {
				color: Kirigami.Theme.backgroundColor
				border.color: Kirigami.ColorUtils.tintWithAlpha(color, Kirigami.Theme.textColor, 0.2)
				border.width: 1
			}
			contentItem: RowLayout {
				Repeater {
					model: _control.controller.defaultItems
					delegate: Loader {
						id: _loader

						required property var modelData
						required property int index
						sourceComponent: modelData.component

						Binding {
							target: _loader.item
							property: "outlet"
							value: _control.outlet || _control.controller.outlet
						}

						Layout.fillWidth: item ? item.Layout.fillWidth : false
						Layout.fillHeight: item ? item.Layout.fillHeight : false
					}
				}
			}
			Layout.fillWidth: true
			Layout.margins: Kirigami.Units.largeSpacing
		}
	}
}
