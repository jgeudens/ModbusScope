#ifndef DATAFILEHANDLER_H
#define DATAFILEHANDLER_H

#include <QObject>

#include "guimodel.h"
#include "graphdatamodel.h"
#include "notemodel.h"
#include "settingsmodel.h"
#include "loadfiledialog.h"

#include "datafileexporter.h"
#include "dataparsermodel.h"

class DataFileHandler : public QObject
{
    Q_OBJECT
public:
    explicit DataFileHandler(GuiModel* pGuiModel, GraphDataModel* pGraphDataModel, NoteModel* pNoteModel, SettingsModel *pSettingsModel, DataParserModel * pDataParserModel);
    ~DataFileHandler();

    void loadDataFile(QString dataFilePath);

    void enableExporterDuringLog();
    void disableExporterDuringLog();

    void exportDataFile(QString dataFile);
    bool updateNoteLines();

signals:
    void startDataParsing();

public slots:
    void selectDataImportFile();
    void selectDataExportFile();

    void exportDataLine(double timeData, QList <double> dataValues);
    void rewriteDataFile(void);

    void parseDataFile();

private:

    GuiModel* _pGuiModel;
    GraphDataModel* _pGraphDataModel;
    NoteModel* _pNoteModel;
    SettingsModel* _pSettingsModel;

    DataFileExporter * _pDataFileExporter;
    DataParserModel * _pDataParserModel;

    QTextStream* _pDataFileStream;
    LoadFileDialog* _pLoadFileDialog;

    static const qint32 _cSampleLineLength = 50;
};

#endif // DATAFILEHANDLER_H
