#include "treeitem.h"

TreeItem::TreeItem(TreeItem *parent)
    : m_parentItem(parent),
      m_level(0)
{
    if (m_parentItem)
        m_level = m_parentItem->level() + 1;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *child)
{
    m_childItems.append(child);
}

TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

TreeItem *TreeItem::parent()
{
    return m_parentItem;
}

QString TreeItem::text() const
{
    return m_text;
}

void TreeItem::setText(const QString &text)
{
    m_text = text;
}

int TreeItem::level() const
{
    return m_level;
}

void TreeItem::setLevel(int level)
{
    m_level = level;
}
