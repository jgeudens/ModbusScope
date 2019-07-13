#ifndef DATAFILEPARSER_H
#define DATAFILEPARSER_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>

#include "note.h"
#include "dataparsermodel.h"

class DataFileParser : public QObject
{
    Q_OBJECT

public:

    typedef struct
    {
        QString axisLabel;
        QList<double> timeRow;

        QStringList dataLabel;
        QList<QList<double> > dataRows;
        QList<QColor> colors;
        QList<Note> notes;

    } FileData;

    DataFileParser(DataParserModel * pDataParserModel);
    ~DataFileParser();

    bool processDataFile(QTextStream * pDataStream, FileData * pData);

private:
    bool parseDataLines(QList<QList<double> > &dataRows);
    bool readLineFromFile(QString *pLine);
    qint64 parseDateTime(QString rawData, bool *bOk);
    bool parseNoteField(QStringList noteFieldList, Note * pNote);
    double parseDouble(QString strNumber, bool* bOk);


    QTextStream * _pDataStream;
    DataParserModel * _pDataParserModel;

    quint32 _expectedFields;

    QRegularExpression _dateParseRegex;

    static const QString _cPattern;

};

#endif // DATAFILEPARSER_H
