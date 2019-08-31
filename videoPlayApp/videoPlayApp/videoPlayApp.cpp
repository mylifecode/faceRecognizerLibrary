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
	videoPlayWidget(NULL),
	videoName(NULL)
{
	//ui.setupUi(this);
	initialize();
}

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
	//videoPlayWidget = new QWidget;
	//videoPlayWidget->setObjectName("videoPlayWidget");
	//videoPlayWidget->setStyleSheet(QString("QWidget#videoPlayWidget{min-height:500;max-height:500;}"));
	videoWidget->setFixedSize(QSize(800, 500));
	videoWidget->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Expanding);

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
	if (playState != PlayState::STOP)
	{
		player->stop();
		playState = STOP;
	}
	QStringList filePaths = QFileDialog::getOpenFileNames(NULL,CHS("导入视频文件"),"./","video/mp3 (*.*)");
	for (auto &path : filePaths)
	{
		QString videoName = "";
		int loc = path.lastIndexOf("/");
		videoName = path.mid(loc+1);
		if (videoNameAndPath.find(videoName) == videoNameAndPath.end())
		{
			videoNameAndPath[videoName] = path;
			videoPathVector.push_back(path);
		}
	}
	if (filePaths.isEmpty())
	{
		return false;
	}
	QMessageBox::information(this, "", CHS("文件导入成功!"), QMessageBox::Yes);
	return true;
}

void videoPlayApp::playSlots()
{
	if (videoPathVector.isEmpty())
	{
		QMessageBox::information(this, "", CHS("请先导入播放文件!"), QMessageBox::Yes);
		return;
	}
	if (playState == PlayState::PLAY)
	{
		player->pause();
		playState = PAUSE;
		return;
	}
	else if (playState == PlayState::PAUSE)
	{
		player->play();
		playState = PLAY;
		return;
	}
	else
	{
		playerlist->clear();
		for (auto& filePath : videoPathVector)
		{
			playerlist->addMedia(QUrl::fromLocalFile(filePath));
		}
		
		playerlist->setCurrentIndex(0);
		int currentIndex = playerlist->currentIndex();
		if (currentIndex < videoPathVector.size())
		{
			QString currentFilePath = videoPathVector[currentIndex];
			int loc = currentFilePath.lastIndexOf("/");
			QString tmpVideoName = currentFilePath.mid(loc + 1);
			videoName->setText(CHS("正在播放-") + tmpVideoName);
		}
		playerlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
		player->setPlaylist(playerlist);
		player->setVideoOutput(videoWidget);
		videoWidget->show();
		player->play();
		playState = PLAY;
	}
}

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

void videoPlayApp::nextSlots()
{
	player->stop();
	playState = STOP;
	int totalMediaNumber = playerlist->mediaCount();
	int nextIndex = playerlist->nextIndex();
	if (nextIndex >= totalMediaNumber - 1)
	{
		playerlist->setCurrentIndex(0);
	}
	else
	{
		playerlist->setCurrentIndex(nextIndex);
	}
	//更新video名称
	int currentIndex = playerlist->currentIndex();
	if (currentIndex < videoPathVector.size())
	{
		QString currentFilePath = videoPathVector[currentIndex];
		int loc = currentFilePath.lastIndexOf("/");
		QString tmpVideoName = currentFilePath.mid(loc + 1);
		videoName->setText(CHS("正在播放-") + tmpVideoName);
	}
	player->play();
	playState = PLAY;
}