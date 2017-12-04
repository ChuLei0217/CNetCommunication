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

//http请求类
class CNetCommunication : public QObject
{
	Q_OBJECT
public:
	CNetCommunication(QString * url,QByteArray * arr);

	//发起http请求,传输预警信息
	bool PostWarningInfo();

	//接收数据
	void GetInfo();

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
