#include "treenode.h"
#include <QDebug>

TreeNode::TreeNode(QObject *parent) : QObject(parent) {}

QString TreeNode::value() const {
    return m_value;
}

TreeNode* TreeNode::left() const {
    return m_left;
}

TreeNode* TreeNode::right() const {
    return m_right;
}

void TreeNode::setValue(const QString &value) {
    if (m_value != value) {
        m_value = value;
        emit valueChanged();
    }
}

void TreeNode::setLeft(TreeNode *left) {
    if (m_left != left) {
        if (m_left) m_left->deleteLater();
        m_left = left;
        if (m_left) m_left->setParent(this);
        emit leftChanged();
    }
}

void TreeNode::setRight(TreeNode *right) {
    if (m_right != right) {
        if (m_right) m_right->deleteLater();
        m_right = right;
        if (m_right) m_right->setParent(this);
        emit rightChanged();
    }
}

TreeNode* TreeNode::fromJson(const QJsonObject &obj, QObject *parent) {
    if (!obj.contains("value")) {
        qWarning() << "JSON object doesn't contain 'value' key";
        return nullptr;
    }

    TreeNode *node = new TreeNode(parent);
    node->setValue(obj["value"].toString());

    if (obj.contains("left") && obj["left"].isObject()) {
        node->setLeft(fromJson(obj["left"].toObject(), node));
    }

    if (obj.contains("right") && obj["right"].isObject()) {
        node->setRight(fromJson(obj["right"].toObject(), node));
    }

    return node;
}

void TreeNode::deleteTree(TreeNode *root) {
    if (!root) return;

    deleteTree(root->left());
    deleteTree(root->right());
    root->deleteLater();
}
