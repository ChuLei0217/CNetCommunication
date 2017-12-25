#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>
#include <QSslConfiguration>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qtextcodec.h>
#include <qeventloop.h>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueIterator>
#include <opencv2\opencv.hpp>
#include <qbuffer.h>
#include <qimagereader.h>

//http请求类
class CNetCommunication : public QObject
{
	Q_OBJECT
public:
	//用于post的构造函数
	CNetCommunication(QString * url, QByteArray * warninginfo);

	//用于get的构造函数
	CNetCommunication(QString * url);

	//发起http请求,传输预警信息
	bool PostWarningInfo();

	//获得电子围栏的信息
	bool GetInfo();

	//post的状态
	bool status;

	//解析http传输预警信息后返回的json数据
	bool AnalysePostReturn(QString json);

	//解析Get到的电子围栏的json信息
	void ParseJson(QByteArray bytearray);

	//收到post的返回信息
	QString postresult;

	//收到的电子围栏区域的信息
	QByteArray getresult;

	//接收照片信息
	void GetPhoto(std::vector<cv::Mat> * photo);

	//分析照片的json数据
	void ParsePhotoJson(QByteArray bytearray);

	//下载照片
	//cv::Mat 
	void DownloadPhoto(QString url);

	//存放照片
	std::vector<cv::Mat> * Photo;
private:
	//网络管理类
	QNetworkAccessManager* manager;

	//封装请求返回信息
	QNetworkReply* reply; 
	
	//请求的url
	QString * url;

	//需要传输的json数据
	QByteArray * postData;
};
