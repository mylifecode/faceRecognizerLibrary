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
	//播放状态
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
	//打开文件
	bool openFileSlots();
	//播放
	void playSlots();
	//退出
	bool exitSlots();
	//播放下个文件
	void nextSlots();
	//设置播放信息
	void initVideoPlayInfo();
private:
	//当前文件路径
	QString filePath;
	//当前播放状态
	PlayState playState;
	//创建播放器
	QMediaPlayer* player;
	//创建播放列表
	QMediaPlaylist* playerlist;
	//视频播放窗口
	QVideoWidget* videoWidget;
	//记录视频名称和路径
	QMap<QString,QString> videoNameAndPath;
	//记录视频路径
	QVector<QString> videoPathVector;
	//当前视频名称
	QLabel* videoName;
	//Ui::videoPlayAppClass ui;

};
