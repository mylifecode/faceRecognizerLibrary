#include "videoPlayApp.h"
#include<qlayout.h>
#include<QBoxLayout>
#include<QVBoxLayout>
#include<qmessagebox.h>
#include<qfiledialog.h>



#define CHS(text) QString::fromLocal8Bit(text)

videoPlayApp::videoPlayApp(QWidget *parent)
	: QWidget(parent),
	filePath(""),
	playState(STOP),
	player(NULL),
	playerlist(NULL),
	videoWidget(NULL),
	videoName(NULL)
{
	//ui.setupUi(this);
	initialize();
}

//页面布局初始化
void videoPlayApp::initialize()
{
	
	QVBoxLayout* vLayout = new QVBoxLayout();
	QHBoxLayout* h1Layout = new QHBoxLayout();
	videoName = new QLabel(CHS("正在播放-")+"XX.mp4");
	videoName->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
	QFont font;
	font.setPointSize(20);
	//font.
	videoName->setFont(font);
	h1Layout->addItem(new QSpacerItem(1, QSizePolicy::Expanding));
	h1Layout->addWidget(videoName);
	h1Layout->addItem(new QSpacerItem(1, QSizePolicy::Expanding));

	videoWidget = new QVideoWidget;
	videoWidget->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);

	QPushButton* openFile = new QPushButton("open");
	openFile->setFixedSize(QSize(150, 50));
	connect(openFile, &QPushButton::clicked, this, &videoPlayApp::openFileSlots);

	QPushButton* play = new QPushButton("play/stop");
	play->setFixedSize(QSize(150, 50));
	connect(play, &QPushButton::clicked, this, &videoPlayApp::playSlots);

	QPushButton* nextVideo = new QPushButton("next");
	nextVideo->setFixedSize(QSize(150, 50));
	connect(nextVideo, &QPushButton::clicked, this, &videoPlayApp::nextSlots);

	QPushButton* exit = new QPushButton("exit");
	exit->setFixedSize(QSize(150, 50));
	connect(exit, &QPushButton::clicked, this, &videoPlayApp::exitSlots);
	
	QHBoxLayout* hLayout = new QHBoxLayout();
	hLayout->addWidget(openFile);
	hLayout->addWidget(play);
	hLayout->addWidget(nextVideo);
	hLayout->addWidget(exit);
	//hLayout->setContentsMargins(30, 10, 10, 30);

	vLayout->addItem(new QSpacerItem(10,QSizePolicy::Fixed));
	vLayout->addLayout(h1Layout);
	vLayout->addWidget(videoWidget);
	vLayout->addItem(new QSpacerItem(10, QSizePolicy::Expanding));
	//vLayout->addSpacerItem(new QSpacerItem(1, QSizePolicy::Preferred));
	vLayout->addLayout(hLayout);
	//vLayout->setContentsMargins(0,0,0,0);
	//vLayout->setSpacing(0);
	this->setLayout(vLayout);

	player = new QMediaPlayer(this);
	playerlist = new QMediaPlaylist(this);
}


bool videoPlayApp::openFileSlots()
{
	//正在播放时先关闭播放器
	if (playState == PlayState::PLAY)
	{
		player->pause();
		playState = PAUSE;
	}

	//获得播放文件完整路径
	QStringList filePaths = QFileDialog::getOpenFileNames(NULL,CHS("请选择导入视频文件"),"./","video/mp3 (*.*)");
	for (auto &path : filePaths)
	{
		QString videoName = "";
		int loc = path.lastIndexOf("/");
		videoName = path.mid(loc+1);
		//判别文件是否已经存在
		if (videoNameAndPath.find(videoName) == videoNameAndPath.end())
		{
			videoNameAndPath[videoName] = path;
			videoPathVector.push_back(path);
		}
	}
	//路径空返回
	if (filePaths.isEmpty())
	{
		return false;
	}
	QMessageBox::information(this, "", CHS("文件导入成功!"), QMessageBox::Yes);
	return true;
}
//播放视频
void videoPlayApp::playSlots()
{
	//第一次点击
	if (videoPathVector.isEmpty())
	{
		QMessageBox::information(this, "", CHS("请先导入播放文件!"), QMessageBox::Yes);
		return;
	}
	////正在播放时点击切换为暂停
	//if (playState == PlayState::PLAY)
	//{
	//	player->pause();
	//	playState = PAUSE;
	//	return;
	//}
	////切换为播放
	//else if (playState == PlayState::PAUSE)
	//{
	//	player->play();
	//	playState = PLAY;
	//	return;
	//}
	//else
	//{// stop状态
	//	//先清空播放列表，重新导入
	//	playerlist->clear();
	//	for (auto& filePath : videoPathVector)
	//	{
	//		//添加播放资源
	//		playerlist->addMedia(QUrl::fromLocalFile(filePath));
	//	}
	//	//设置当前播放顺序
	//	playerlist->setCurrentIndex(currentIndex);
	//	//显示当前播放信息
	//	//int currentIndex = playerlist->currentIndex();
	//	if (currentIndex < videoPathVector.size())
	//	{
	//		QString currentFilePath = videoPathVector[currentIndex];
	//		int loc = currentFilePath.lastIndexOf("/");
	//		QString tmpVideoName = currentFilePath.mid(loc + 1);
	//		videoName->setText(CHS("正在播放-") + tmpVideoName);
	//	}
	//	//设置播放模式
	//	playerlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
	//	//设置播放列表
	//	player->setPlaylist(playerlist);
	//	//设置视频显示窗口
	//	player->setVideoOutput(videoWidget);
	//	//显示视频
	//	videoWidget->show();
	//	//播放音频
	//	player->play();
	//	playState = PLAY;
	//}

	switch (playState)
	{
		case(PAUSE):
		{
			playState = PLAY;
			player->play();
			break;
		}
		case(PLAY):
		{
			playState = PAUSE;
			player->pause();
			break;
		}
		case(STOP):
		{
			initVideoPlayInfo();
			break;
		}
		default:
			break;
	}
}


void videoPlayApp::initVideoPlayInfo()
{
	//先清空播放列表，重新导入
	//playerlist->clear();
	for (auto& filePath : videoPathVector)
	{
		//添加播放资源
		playerlist->addMedia(QUrl::fromLocalFile(filePath));
	}
	//显示当前播放信息
	playerlist->setCurrentIndex(0);

	int currentIndex = playerlist->currentIndex();
	if (currentIndex < videoPathVector.size())
	{
		QString currentFilePath = videoPathVector[currentIndex];
		int loc = currentFilePath.lastIndexOf("/");
		QString tmpVideoName = currentFilePath.mid(loc + 1);
		videoName->setText(CHS("正在播放-") + tmpVideoName);
	}
	//设置播放模式
	playerlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
	//设置播放列表
	player->setPlaylist(playerlist);
	//设置视频显示窗口
	player->setVideoOutput(videoWidget);
	//显示视频
	videoWidget->show();
	//播放音频
	player->play();
	playState = PLAY;
}
//退出播放器
bool videoPlayApp::exitSlots()
{
	QMessageBox::StandardButton btn=QMessageBox::information(this, "", CHS("是否确认退出？"), QMessageBox::Yes | QMessageBox::No);
	if (btn == QMessageBox::Yes)
	{	
		//停止播放
		player->stop();
		playState = STOP;
		this->close();
		return true;
	}
	return false;
}

//播放下一个资源
void videoPlayApp::nextSlots()
{
	if (playerlist->isEmpty())
	{
		QMessageBox::information(this, "", CHS("请导入播放文件!"), QMessageBox::Yes);
		return;
	}
	player->stop();
	playState = STOP;
	//确保当前已经导入资源文件
	int totalMediaNumber = playerlist->mediaCount();
	int currentIndex = playerlist->currentIndex();
	int nextIndex;
	//判别是否最后一个资源
	if (currentIndex >= totalMediaNumber - 1)
	{
		nextIndex = 0;
		playerlist->setCurrentIndex(nextIndex);
	}
	else
	{
		nextIndex = currentIndex + 1;
		playerlist->setCurrentIndex(nextIndex);
	}
	//更新video名称
	if (nextIndex < videoPathVector.size())
	{
		QString currentFilePath = videoPathVector[nextIndex];
		int loc = currentFilePath.lastIndexOf("/");
		QString tmpVideoName = currentFilePath.mid(loc + 1);
		videoName->setText(CHS("正在播放-") + tmpVideoName);
	}
	player->play();
	playState = PLAY;
}