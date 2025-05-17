import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import TreeModel 1.0

Window {
    width: 800
    height: 600
    visible: true
    title: "Главное окно"

    TreeModel {
        id: treeModel
    }

    FileDialog {
        id: fileDialog
        title: "Выберите JSON-файл"
        nameFilters: ["JSON files (*.json)"]
        onAccepted: {
            treeModel.loadFromFile(fileDialog.fileUrl)
        }
    }

    // Второе окно
    Window {
        id: secondWindow
        width: 600
        height: 400
        visible: false
        title: "Дерево во втором окне"

        ListView {
            anchors.fill: parent
            model: treeModel
            delegate: Rectangle {
                width: parent.width
                height: 30
                color: "#BBDEFB"

                Text {
                    text: model.text
                    font.pixelSize: 12
                    anchors {
                        left: parent.left
                        leftMargin: 20 + (model.level * 20)
                        verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 10

        // Кнопка выбора файла
        Rectangle {
            width: 150
            height: 40
            color: "#4CAF50"
            radius: 5

            Text {
                text: "Выбрать файл"
                anchors.centerIn: parent
                color: "white"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: fileDialog.open()
            }
        }

        // Кнопка открытия второго окна
        Rectangle {
            width: 150
            height: 40
            color: "#2196F3"
            radius: 5

            Text {
                text: "Открыть дерево во втором окне"
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 10
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (!secondWindow.visible) {
                        secondWindow.visible = true
                    } else {
                        secondWindow.raise() // Если уже открыт — поднять поверх
                    }
                }
            }
        }

        // Отображение дерева в главном окне
        ListView {
            width: parent.width
            height: parent.height - 100
            model: treeModel
            delegate: TreeDelegate {
                width: parent.width
                height: 40
                color: "#E3F2FD"

                Text {
                    text: model.text
                    font.pixelSize: 14
                    anchors {
                        left: parent.left
                        leftMargin: 20 + (model.level * 30)
                        verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }
}
