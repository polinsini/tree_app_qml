#include "treemodel.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>

TreeModel::TreeModel(QObject *parent) : QObject(parent), root(nullptr) {}

void TreeModel::loadFromFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << filePath;
        return;
    }

    rawText = file.readAll(); // Сохраняем текст
    QJsonDocument doc = QJsonDocument::fromJson(rawText.toUtf8());
    if (!doc.isObject()) {
            qWarning() << "Invalid JSON format in file:" << filePath;
            return;
        }
    if (root) {
        TreeNode::deleteTree(root);
        root = nullptr;
    }
    TreeNode::deleteTree(root);
    root = TreeNode::fromJson(doc.object(), this);
    if (!root) {
        qDebug() << "Failed to parse JSON tree structure";
        return;
    }

    qDebug() << "Tree loaded successfully. Root node:" << root;
    emit treeUpdated();
}

QString TreeModel::getRawText() {
    return rawText;
}
