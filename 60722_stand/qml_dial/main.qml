import QtQuick 1.0
import "content"

Rectangle {
	color: "#ff5454";
    width: 363; height: 278
    property alias value: dial.value

	Dial {
		id: dial
		anchors.centerIn: parent
	}
}
