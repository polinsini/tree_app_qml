#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

class TreeItem
{
public:
    explicit TreeItem(TreeItem *parent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int row() const;
    TreeItem *parent();

    QString text() const;
    void setText(const QString &text);

    int level() const;
    void setLevel(int level);

private:
    QList<TreeItem*> m_childItems;
    TreeItem *m_parentItem;
    QString m_text;
    int m_level;
};

#endif // TREEITEM_H
