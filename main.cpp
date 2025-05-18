#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "TreeModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<TreeNode>("TreeNodes", 1, 0, "TreeNode");

    TreeModel model;
    engine.rootContext()->setContextProperty("treeModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
