#include "treeloader.h"

TreeLoader::TreeLoader(QObject *parent) : QObject(parent) {}

QVariantList TreeLoader::treeModel() const {
    return m_model;
}

bool TreeLoader::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        //qWarning() << "Failed to open file:" << filePath;
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull()) {
        //qWarning() << "Invalid JSON in file:" << filePath;
        return false;
    }

    m_model = parseJsonArray(doc.array());
    emit modelChanged();
    return true;
}

QVariantList TreeLoader::parseJsonArray(const QJsonArray &array) {
    QVariantList result;
    for (const QJsonValue &value : array) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            QVariantMap node;
            node["text"] = obj["text"].toString();
            node["elements"] = parseJsonArray(obj["elements"].toArray());
            result.append(node);
        }
    }
    return result;
}
