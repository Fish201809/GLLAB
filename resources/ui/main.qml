
import QtQuick 2.0
import OpenGLUnderQML 1.0

Item {

    width: 320
    height: 480

	Triangle{
	//   SequentialAnimation on num {
    //         NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
    //         NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
    //         loops: Animation.Infinite
    //         running: true
    //     }
	}
    Rectangle {
        color: Qt.rgba(1, 1, 1, 0.7)
        radius: 10
        border.width: 1
        border.color: "white"
        anchors.margins: -10
    }
}