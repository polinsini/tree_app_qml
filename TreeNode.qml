import QtQuick 2.0

Rectangle {
    width: 50
    height: 50
    radius: 25
    color: "lightblue"
    border.width: 2
    border.color: "darkblue"

    property string value: ""

    Text {
        anchors.centerIn: parent
        text: parent.value
        font.pixelSize: 14
    }
}
