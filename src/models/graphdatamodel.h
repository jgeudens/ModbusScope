#ifndef GRAPHDATAMODEL_H
#define GRAPHDATAMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>

#include "settingsmodel.h"
#include "graphdata.h"


class GraphDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum column {
        COLOR = 0,
        ACTIVE,
        UNSIGNED,
        REGISTER,
        BIT32,
        TEXT,
        EXPRESSION,
        CONNECTION_ID,

        COUNT
    };

    explicit GraphDataModel(SettingsModel * pSettingsModel, QObject *parent = nullptr);

    /* Functions for QTableView (model) */
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role);
    Qt::ItemFlags flags(const QModelIndex & index) const;

    bool removeRows (int row, int count, const QModelIndex &parent);
    bool insertRows (int row, int count, const QModelIndex &parent);

    /* Functions for other classes */
    qint32 size() const;
    qint32 activeCount() const;

    bool isVisible(quint32 index) const;
    QString label(quint32 index) const;
    QColor color(quint32 index) const;
    bool isActive(quint32 index) const;
    bool isUnsigned(quint32 index) const;
    bool isBit32(quint32 index) const;
    QString expression(quint32 index) const;
    quint16 registerAddress(quint32 index) const;
    quint8 connectionId(quint8 index) const;
    QSharedPointer<QCPGraphDataContainer> dataMap(quint32 index);

    void setVisible(quint32 index, bool bVisible);
    void setLabel(quint32 index, const QString &label);
    void setColor(quint32 index, const QColor &color);
    void setActive(quint32 index, bool bActive);
    void setUnsigned(quint32 index, bool bUnsigned);
    void setBit32(quint32 index, bool b32Bit);
    void setExpression(quint32 index, QString expression);
    void setRegisterAddress(quint32 index, const quint16 &registerAddress);
    void setConnectionId(quint32 index, const quint8 &connectionId);

    void add(GraphData rowData);
    void add(QList<GraphData> graphDataList);
    void add();
    void add(QList<QString> labelList, QList<double> timeData, QList<QList<double> > data);

    void removeRegister(qint32 idx);
    void clear();

    void activeGraphIndexList(QList<quint16> * pList);

    bool getDuplicate(quint16 * pRegister, QString* pExpression, quint8 * pConnectionId);
    virtual bool isPresent(quint16 addr, QString* pExpression);

    qint32 convertToActiveGraphIndex(quint32 graphIdx);
    qint32 convertToGraphIndex(quint32 activeIdx);

signals:

    void visibilityChanged(const quint32 graphIdx);
    void labelChanged(const quint32 graphIdx);
    void colorChanged(const quint32 graphIdx);
    void activeChanged(const quint32 graphIdx); // when graph is actived / deactivated
    void unsignedChanged(const quint32 graphIdx);
    void bit32Changed(const quint32 graphIdx);
    void expressionChanged(const quint32 graphIdx);
    void registerAddressChanged(const quint32 graphIdx);
    void connectionIdChanged(const quint32 graphIdx);
    void graphsAddData(QList<double>, QList<QList<double> > data);

    void added(const quint32 idx); // When graph definition is added
    void removed(const quint32 idx); // When graph definition is removed

public slots:

private slots:

    void modelDataChanged(quint32 idx);
    void modelCompleteDataChanged();

private:
    quint16 nextFreeAddress();
    void updateActiveGraphList(void);
    void addToModel(GraphData * pGraphData);
    void removeFromModel(qint32 row);

    QList<GraphData> _graphData;
    QList<quint32> _activeGraphList;

    SettingsModel * _pSettingsModel;
};

#endif // GRAPHDATAMODEL_H
