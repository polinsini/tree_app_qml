#include "treemodel.h"
#include "treeitem.h"


enum TreeRoles {
    TextRole = Qt::UserRole + 1,
    LevelRole
};

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_rootItem = new TreeItem(nullptr);
    m_roleNames[TextRole] = "text";
    m_roleNames[LevelRole] = "level";
}

TreeModel::~TreeModel()
{
    delete m_rootItem;
}

bool TreeModel::loadFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        //qWarning() << "Failed to open file:" << filePath;
        return false;
    }

    beginResetModel();
    delete m_rootItem;
    m_rootItem = new TreeItem(nullptr);

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isArray()) {
        setupModelData(doc.array(), m_rootItem);
    }

    endResetModel();
    return true;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);
    TreeItem *childItem = parentItem->child(row);

    return childItem ? createIndex(row, column, childItem) : QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(child);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);
    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = getItem(index);

    switch (role) {
    case TextRole:
        return item->text();
    case LevelRole:
        return item->level();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    return m_roleNames;
}

void TreeModel::setupModelData(const QJsonArray &array, TreeItem *parent)
{
    for (const QJsonValue &value : array) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            TreeItem *item = new TreeItem(parent);
            item->setText(obj["text"].toString());
            item->setLevel(parent->level() + 1);

            if (obj.contains("elements") && obj["elements"].isArray()) {
                setupModelData(obj["elements"].toArray(), item);
            }
        }
    }
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return m_rootItem;
}
