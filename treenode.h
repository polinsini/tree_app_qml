#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>
#include <QString>
#include <QJsonObject>

class TreeNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(TreeNode* left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(TreeNode* right READ right WRITE setRight NOTIFY rightChanged)

public:
    explicit TreeNode(QObject *parent = nullptr);

    // Геттеры
    QString value() const;
    TreeNode* left() const;
    TreeNode* right() const;

    // Сеттеры
    void setValue(const QString &value);
    void setLeft(TreeNode *left);
    void setRight(TreeNode *right);

    // Статические методы
    static TreeNode* fromJson(const QJsonObject &obj, QObject *parent = nullptr);
    static void deleteTree(TreeNode *root);

signals:
    void valueChanged();
    void leftChanged();
    void rightChanged();

private:
    QString m_value;
    TreeNode* m_left = nullptr;
    TreeNode* m_right = nullptr;
};

#endif // TREENODE_H
