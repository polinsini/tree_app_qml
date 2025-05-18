import QtQuick 2.0

Item {
    property var rootNode

    function drawNode(node, x, y, level) {
        if (!node) return;

        // Создаем прямоугольник с текстом
        var rect = Qt.createQmlObject('''
            import QtQuick 2.0
            Rectangle {
                width: 80
                height: 40
                color: "lightblue"
                border.color: "black"
                border.width: 1

                Text {
                    anchors.centerIn: parent
                    text: "''' + node.value + '''"
                }
            }
        ''', parent);

        rect.x = x - rect.width / 2
        rect.y = y

        // Рекурсивно рисуем левый и правый узлы
        var offset = 100 / level
        if (node.left) {
            drawNode(node.left, x - offset, y + 100, level + 1)
        }
        if (node.right) {
            drawNode(node.right, x + offset, y + 100, level + 1)
        }
    }

    onRootNodeChanged: {
        // Очистить старые элементы
        for (var i = children.length - 1; i >= 0; i--) {
            if (children[i] !== this)
                children[i].destroy()
        }

        if (rootNode)
            drawNode(rootNode, parent.width / 2, 50, 1)
    }
}
