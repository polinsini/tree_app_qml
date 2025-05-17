import QtQuick 2.0

Rectangle {
    id: node
    width: 80
    height: 40
    color: "#9acfea"
    border.color: "#2b5876"
    radius: 5

    property string text
    property variant elements: []

    Text {
        anchors.centerIn: parent
        text: parent.text
        font.pixelSize: 14
    }

    Repeater {
        model: elements
        delegate: TreeNode {
            x: calculateX(model.index, modelData.level || 0)
            y: 60
            text: modelData.text
            elements: modelData.elements
        }
    }

    function calculateX(index, level) {
        return (index - Math.pow(2, level)/2) * (60 / (level + 1));
    }
}
