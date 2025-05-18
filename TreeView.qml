import QtQuick 2.0
import QtQuick.Window 2.0
import TreeNodes 1.0

Item {
    id: treeView
    width: 600
    height: 400

    property TreeNode rootNode

    function drawTree(node, x, y, level) {
        console.log("Creating node at:", x, y, "with value:", node.value);

        var obj = Qt.createQmlObject(`
            import QtQuick 2.0
            Rectangle {
                width: 80; height: 40
                x: ${x}; y: ${y}
                color: "red"
                border.width: 1
                Text {
                    text: "${node.value}"
                    anchors.centerIn: parent
                }
            }
        `, treeView);

        console.log("Object created:", obj, "at coordinates:", obj.x, obj.y);

        // Расстояние между уровнями
        var spacing = 150;

        if (node.left) {
            drawTree(node.left, x - spacing, y + 70, level + 1);
        }

        if (node.right) {
            drawTree(node.right, x + spacing, y + 70, level + 1);
        }
    }

    onRootNodeChanged: {
        // Очищаем старые элементы
        for (var i = children.length - 1; i >= 0; i--) {
            if (children[i] !== this) {
                children[i].destroy();
            }
        }

        // Рисуем новое дерево
        if (rootNode) {
            drawTree(rootNode, 300, 50, 1); // Стартовая позиция по центру
        }

        console.log("Root node structure:", JSON.stringify(rootNode));
        if (rootNode) {
            console.log("Root value:", rootNode.value);
            console.log("Left exists:", !!rootNode.left);
            console.log("Right exists:", !!rootNode.right);
        }
    }
}

