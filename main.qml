import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.0

Window {
    visible: true
    width: 800
    height: 600
    title: "Tree Viewer"

    // FileDialog для выбора файла
    FileDialog {
        id: fileDialog
        title: "Select Tree JSON File"
        nameFilters: ["JSON files (*.json)"]
        onAccepted: {
            var url = fileUrl.toString()
            var path = url.replace("file:///", "")
            treeModel.loadFromFile(path)
        }
    }

    // Окно для отображения текста
    Window {
        id: treeWindow
        //modal: true
        width: 600
        height: 400
        visible: false
        title: "Tree Visualization"

        // Загрузка TreeView из файла
        Loader {
            id: treeLoader
            source: "TreeView.qml"

            onStatusChanged: {
                if (status === Loader.Error) {
                    console.error("Loader error:", errorString)
                }
            }

            onLoaded: {
                item.width = parent.width
                item.height = parent.height
                item.rootNode = treeModel.root
                console.log("treeModel.root =", treeModel.root)
                if (item.rootNode) {

                    console.log("TreeView loaded with root node:", treeModel.root)
                } else {
                    console.error("Error: treeModel.root is undefined!")
                }
                console.log("TreeView loaded")

                treeModel.treeUpdated.connect(function() {
                                item.rootNode = treeModel.root
                            })
            }
        }

        Button {
            text: "Close"
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: treeWindow.close()
        }
    }


    // Кнопка загрузки файла
    Button {
        id: loadButton
        text: "Load Tree"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        onClicked: fileDialog.open()
    }

    // Кнопка отображения дерева
    Button {
        id: treeView
        text: "Show Text"
        anchors.top: loadButton.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        onClicked: {
            treeWindow.visible = true

        }
    }
}
