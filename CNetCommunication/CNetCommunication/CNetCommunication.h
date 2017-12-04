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

//http������
class CNetCommunication : public QObject
{
	Q_OBJECT
public:
	CNetCommunication(QString * url,QByteArray * arr);

	//����http����,����Ԥ����Ϣ
	bool PostWarningInfo();

	//��������
	void GetInfo();

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
