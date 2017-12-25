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

//http������
class CNetCommunication : public QObject
{
	Q_OBJECT
public:
	//����post�Ĺ��캯��
	CNetCommunication(QString * url, QByteArray * warninginfo);

	//����get�Ĺ��캯��
	CNetCommunication(QString * url);

	//����http����,����Ԥ����Ϣ
	bool PostWarningInfo();

	//��õ���Χ������Ϣ
	bool GetInfo();

	//post��״̬
	bool status;

	//����http����Ԥ����Ϣ�󷵻ص�json����
	bool AnalysePostReturn(QString json);

	//����Get���ĵ���Χ����json��Ϣ
	void ParseJson(QByteArray bytearray);

	//�յ�post�ķ�����Ϣ
	QString postresult;

	//�յ��ĵ���Χ���������Ϣ
	QByteArray getresult;

	//������Ƭ��Ϣ
	void GetPhoto(std::vector<cv::Mat> * photo);

	//������Ƭ��json����
	void ParsePhotoJson(QByteArray bytearray);

	//������Ƭ
	//cv::Mat 
	void DownloadPhoto(QString url);

	//�����Ƭ
	std::vector<cv::Mat> * Photo;
private:
	//���������
	QNetworkAccessManager* manager;

	//��װ���󷵻���Ϣ
	QNetworkReply* reply; 
	
	//�����url
	QString * url;

	//��Ҫ�����json����
	QByteArray * postData;
};
