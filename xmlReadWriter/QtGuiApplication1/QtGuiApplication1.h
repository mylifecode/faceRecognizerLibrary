#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiApplication1.h"
#include<QString>
#include<qpushbutton.h>
#include<QVector>
typedef struct personInfo
{
	QString name;
	QString number;
	QString content;
	QString time;
	personInfo()
	{

	}
	/*personInfo(QString _name, int _number, QString _content, QString _time) :
		name(_name), number(_number), content(_content), time(_time) {};*/
	void setName(const QString &_name)
	{
		name = _name;
	}
	void setNumber(const QString &_number)
	{
		number = _number;
	}
	void setTime(const QString &_time)
	{
		time = _time;
	}
	void setContent(const QString &_content)
	{
		content = _content;

	}
}personInfo;

class QtGuiApplication1 : public QWidget
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);
	bool readXml(const QString& fileName);
	bool writerXml(const QString &fileName);
private:
	Ui::QtGuiApplication1Class ui;
	QVector<personInfo*> pesInfoV;
};
