#pragma once

#include <QtWidgets/QWidget>
//#include "ui_videoPlayApp.h"
#include<qmediaplayer.h>
#include<qmediaplaylist.h>
#include<qpushbutton.h>
#include<qvideowidget.h>
#include<qlabel.h>

class videoPlayApp : public QWidget
{
	Q_OBJECT
public:
	enum PlayState
	{
		PLAY,
		PAUSE,
		STOP
	};
public:
	videoPlayApp(QWidget *parent = Q_NULLPTR);
	void initialize();
private slots:
	bool openFileSlots();
	void playSlots();
	bool exitSlots();
	void nextSlots();
private:
	QString filePath;
	PlayState playState;
	QMediaPlayer* player;
	QMediaPlaylist* playerlist;
	QWidget* videoPlayWidget;
	QVideoWidget* videoWidget;
	QMap<QString,QString> videoNameAndPath;
	QVector<QString> videoPathVector;
	QLabel* videoName;
	//Ui::videoPlayAppClass ui;

};
