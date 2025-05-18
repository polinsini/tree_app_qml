// TreeModel.h
#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>
#include <QJsonDocument>
#include "treenode.h"

class TreeModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(TreeNode* root READ getRoot NOTIFY treeUpdated)
public:

    explicit TreeModel(QObject *parent = nullptr);
    Q_INVOKABLE void loadFromFile(const QString& filePath);

     TreeNode* getRoot() const { return root; }
     QString getRawText();
signals:
    void treeUpdated();

private:
    TreeNode* root = nullptr;
    QString rawText; // Поле для хранения текста
};
#endif // TREEMODEL_H
