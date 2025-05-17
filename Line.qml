import QtQuick 2.0
import QtQuick.Shapes 1.0

Shape {
    id: shape
    property point p1: Qt.point(0, 0)
    property point p2: Qt.point(0, 0)
    property color color: "black"

    ShapePath {
        strokeWidth: 2
        strokeColor: shape.color
        startX: shape.p1.x
        startY: shape.p1.y
        PathLine { x: shape.p2.x; y: shape.p2.y }
    }
}
