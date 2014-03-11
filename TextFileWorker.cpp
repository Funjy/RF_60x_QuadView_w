#include "TextFileWorker.h"

TextFileWorker::TextFileWorker(void)
{
	_isOpened = false;
	_isINIOpened = false; 
}


TextFileWorker::~TextFileWorker(void)
{
	CloseFile();
}

bool TextFileWorker::OpenFile(QString fileName, bool overwrite /*= false*/)
{
	bool toRet;
	if(_isINIOpened)
		return false;
	CloseFile();	
	_file = new QFile(fileName);
	if(!overwrite)
		toRet = _file->open(QIODevice::ReadWrite | QIODevice::Text);	
	else
		toRet = _file->open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
	if(toRet)
	{
		_ts = new QTextStream(_file);	
		_isOpened = toRet;
	}
	else
	{
		_isOpened = false;
	}
	return toRet;	
}

void TextFileWorker::CloseFile()
{
	if(_isOpened)
	{
		_file->close();	
		delete _file;
		_file = NULL;
		_isOpened = false;
	}
	if(_isINIOpened)
	{
		delete _settings;
		_settings = 0;
		_isINIOpened = false;
	}	
}

bool TextFileWorker::WriteLine(QString text)
{
	if(_ts == NULL)
		return false;
	(*_ts) << text << endl;
	return true;
}

bool TextFileWorker::Write(QString text)
{
	if(_ts == NULL)
		return false;
	(*_ts) << text;
	return true;
}

QString TextFileWorker::ReadLine()
{
	if(_ts == NULL)
		return NULL;
	//_ts = new QTextStream(_file);
	//if(_ts != NULL)
		return _ts->readLine();
	//return NULL;
}

bool TextFileWorker::ReadCSVLine(QStringList* line)
{
	QString str = ReadLine();
	if(str == NULL)
		return false;
	*line = str.split(';', QString::KeepEmptyParts);
	return true;
}

bool TextFileWorker::WriteCSVLine(QStringList text)
{
	if(_ts == NULL || !_isOpened)
		return false;
	QString sb;
	QString str;
	foreach(str, text)
	{
		sb.append(str);
		sb.append(';');
	}
	sb.remove(sb.length() - 1, 1);
	(*_ts) << sb << endl;
	return true;
}

bool TextFileWorker::WriteINILine(QString key, QString value)
{
	if(!_isINIOpened)
		return false;
	_settings->setValue(key, value);
	return true;
}

bool TextFileWorker::ReadINIValue(QString key, QString* readValue)
{
	if(!_isINIOpened)
		return false;
	const QString notFound = "noHere";
	//readValue = new QString();
	*readValue = _settings->value(key, notFound).toString();
	if((*readValue).compare(notFound) == 0)
	{
		//delete readValue;
		//readValue = 0;
		return false;
	}
	return true;
}

bool TextFileWorker::OpenINIFile(QString fileName)
{
	if(_isOpened || _isINIOpened)
		return false;
	_settings = new QSettings(fileName, QSettings::IniFormat);
	_isINIOpened = true;
	return true;
}

void TextFileWorker::BeginINIGroup(QString groupName)
{
	if(!_isINIOpened)
		return;
	_settings->beginGroup(groupName);
}

void TextFileWorker::EndINIGroup()
{
	_settings->endGroup();	
}
