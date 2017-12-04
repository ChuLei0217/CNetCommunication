#include <CNetCommunication.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QByteArray append("warnings.deviceserial=786297833");
	append.append("&warnings.warningType=1");
	append.append("&warnings.roomAreaTypeId=3");
	append.append("&warnings.warningState=0");
	append.append("&warnings.startTime=2020-11-11 10:10:10");
	append.append("&warnings.endTime=2020-12-12 12:12:12}");
	QByteArray * b = &append;
	QString u = "http://211.67.27.249:8080/MonitorWeb/warning/warning_add.action";
	QString *uu = &u;
	CNetCommunication * test = new CNetCommunication(uu,b);

	if (test->PostWarningInfo() != true)
	{
		qDebug() << test->postresult;
	}
	else
	{
		qDebug() << "true";
	}
	return a.exec();
}
