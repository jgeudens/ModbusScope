#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

#include <QObject>
#include <QList>
#include <QStringListModel>
#include <QTimer>

#include "modbusmaster.h"
#include "registervaluehandler.h"

//Forward declaration
class GuiModel;
class SettingsModel;
class GraphDataModel;

class ModbusMasterData : public QObject
{
    Q_OBJECT
public:

    explicit ModbusMasterData(ModbusMaster * pArgModbusMaster, QObject *parent = nullptr):
        QObject(parent)
    {
        pModbusMaster = pArgModbusMaster;
        bActive = false;
    }

    ModbusMaster * pModbusMaster;
    bool bActive;
};

class CommunicationManager : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationManager(SettingsModel * pSettingsModel, GuiModel * pGuiModel, GraphDataModel * pGraphDataModel, QObject *parent = nullptr);
    ~CommunicationManager();

    bool startCommunication();
    void stopCommunication();

    bool isActive();
    void resetCommunicationStats();

signals:
    void handleReceivedData(QList<bool> successList, QList<double> values);

private slots:
    void handlePollDone(QMap<quint16, ModbusResult> resultMap, quint8 connectionId);
    void handleModbusError(QString msg);
    void handleModbusInfo(QString msg);
    void readData();

private:

   double processValue(quint32 graphIndex, quint16 value);

    QList<ModbusMasterData *> _modbusMasters;
    quint32 _activeMastersCount;

    bool _bPollActive;
    QTimer * _pPollTimer;
    qint64 _lastPollStart;

    RegisterValueHandler _registerValueHandler;

    GuiModel * _pGuiModel;
    SettingsModel * _pSettingsModel;
};

#endif // COMMUNICATION_MANAGER_H
