#pragma once

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QSettings>
//#include <string>

class TextFileWorker
{
public:
	TextFileWorker(void);
	~TextFileWorker(void);

	bool OpenFile(QString fileName, bool overwrite = false);
	bool OpenINIFile(QString fileName);
	void CloseFile();
	bool WriteLine(QString text);
	bool WriteCSVLine(QStringList text);
	bool WriteINILine(QString key, QString value);
	bool Write(QString text);
	QString ReadLine();
	bool ReadCSVLine(QStringList* line);
	bool ReadINIValue(QString key, QString* readValue);
	void BeginINIGroup(QString groupName);
	void EndINIGroup();


private:
	QFile* _file;
	QTextStream* _ts;
	QSettings* _settings;
	bool _isOpened;
	bool _isINIOpened;

};

