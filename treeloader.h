#ifndef TREELOADER_H
#define TREELOADER_H

#include <QObject>
#include <QVariantList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class TreeLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList treeModel READ treeModel NOTIFY modelChanged)

public:
    explicit TreeLoader(QObject *parent = nullptr);

    QVariantList treeModel() const;
    Q_INVOKABLE bool loadFromFile(const QString &filePath);

signals:
    void modelChanged();

private:
    QVariantList parseJsonArray(const QJsonArray &array);
    QVariantList m_model;
};

#endif // TREELOADER_H
