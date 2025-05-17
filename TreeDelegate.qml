import QtQuick 2.0

Rectangle {
    property int itemLevel: level
    property string itemText: text

    color: index % 2 ? "#E3F2FD" : "#BBDEFB"
    border.color: "#2196F3"
    radius: 3

    Text {
        text: itemText
        font.pixelSize: 14
        anchors {
            left: parent.left
            leftMargin: 20 + (itemLevel * 30)
            verticalCenter: parent.verticalCenter
        }
    }
}
