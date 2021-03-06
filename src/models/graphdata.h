#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#include <QtGlobal>
#include <QColor>
#include "qcustomplot.h"

class GraphData
{

public:
    explicit GraphData();
    ~GraphData();

    bool isVisible() const;
    void setVisible(bool bVisible);

    QString label() const;
    void setLabel(const QString &label);

    QColor color() const;
    void setColor(const QColor &color);

    bool isActive() const;
    void setActive(bool bActive);

    bool isUnsigned() const;
    void setUnsigned(bool bUnsigned);

    bool isBit32() const;
    void setBit32(bool isBit32);

    QString expression() const;
    void setExpression(QString expression);

    quint16 registerAddress() const;
    void setRegisterAddress(const quint16 &registerAddress);

    quint8 connectionId() const;
    void setConnectionId(const quint8 &connectionId);

    QSharedPointer<QCPGraphDataContainer> dataMap();

private:

    bool _bVisible;
    QString _label;
    QColor _color;

    bool _bActive;
    bool _bUnsigned;
    bool _bit32;
    quint16 _registerAddress;
    quint8 _connectionId;

    QString _expression;

    QSharedPointer<QCPGraphDataContainer> _pDataMap;

};

#endif // GRAPHDATA_H
