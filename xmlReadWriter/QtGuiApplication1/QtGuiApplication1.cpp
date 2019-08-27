#include "QtGuiApplication1.h"
#include<QFile>
#include<qxmlstream.h>
#include<direct.h>
#include<qdebug.h>
#include<iostream>
QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	connect(ui.writeBtn, &QPushButton::clicked, this, [=]()
	{
		char* fileNameStr = getcwd(NULL, 0);
		if (fileNameStr != NULL)
		{
			QString fileName = QString(fileNameStr)+'\\'+ QString("config1.xml");
			writerXml(fileName);
		}
	});

	connect(ui.readBtn, &QPushButton::clicked, this, [=]()
	{
		char* fileNameStr = getcwd(NULL, 0);
		if (fileNameStr != NULL)
		{
			QString fileName = QString(fileNameStr) + '\\' + QString("personInfo.xml");
			bool ret=readXml(fileName);

			if (ret)
			{
				if (!pesInfoV.isEmpty())
				{
					std::cout<< "file read results:" << std::endl;
					for (auto &v : pesInfoV)
					{
						std::cout<<v->name.toStdString() << " " << v->number.toStdString() << " " << v->content.toStdString() << " " << v->time.toStdString() << std::endl;
					}
				}
			}
		}
	});
}

bool QtGuiApplication1::readXml(const QString& fileName)
{
	QFile inFile(fileName);
	if (inFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QXmlStreamReader reader(&inFile);
		reader.readNext();
		personInfo* perInfo;
		while (!reader.atEnd())
		{
			if (reader.isStartElement())
			{
				if (reader.name() == "Sms")
				{
					perInfo = new personInfo;
				}
				else if (reader.name() == "Name")
				{
					perInfo->setName(reader.readElementText());
				}
				else if (reader.name() == "Number")
				{
					perInfo->setNumber(reader.readElementText());
				}
				else if (reader.name() == "Content")
				{
					perInfo->setContent(reader.readElementText());


				}
				else if (reader.name() == "Time")
				{
					perInfo->setTime(reader.readElementText());

				}
			}
			else if (reader.isEndElement())
			{
				if (reader.name() == "Sms")
				{
					pesInfoV.push_back(perInfo);
				}
			}
			reader.readNext();
		}

		return true;
	}
	else
		return false;
}

bool QtGuiApplication1::writerXml(const QString& fileName)
{
	QFile infile(fileName);
	if (infile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QXmlStreamWriter writer(&infile);
		writer.setAutoFormatting(true);
		writer.writeStartDocument();
		writer.writeStartElement("DATA");
		writer.writeStartElement("Sm");
		writer.writeTextElement("Name", ui.NameEdit->text());
		writer.writeTextElement("Number", ui.NumberEdit->text());
		writer.writeTextElement("Country", ui.CountryEdit->text());
		writer.writeTextElement("School", ui.SchoolEdit->text());
		writer.writeEndElement();
		writer.writeEndElement();
		writer.writeEndDocument();

		return true;
	}
	else
		return false;

}

void Sum(int* data)
{

}

struct DelPointer
{
public:
	template<typename T>
	void operator()(T* t)
	{
		delete t;
		t = NULL;
	}
};
void print()
{
	std::vector<int*> Vec;
	std::for_each(Vec.begin(), Vec.end(), &Sum);
	std:for_each(Vec.begin(), Vec.end(), DelPointer());
}