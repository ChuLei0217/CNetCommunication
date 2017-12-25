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
	/*QByteArray append("warnings.deviceserial=786297833");
	append.append("&warnings.warningType=1");
	append.append("&warnings.roomAreaTypeId=3");
	append.append("&warnings.warningState=0");
	append.append("&warnings.startTime=2020-11-11 10:10:10");
	append.append("&warnings.endTime=2020-12-12 12:12:12");
*/
	/*QJsonObject json;
	json.insert("warnings.deviceserial", "786297833");
	json.insert("warnings.warningType", 1);
	json.insert("warnings.roomAreaTypeId", 3);
	json.insert("warnings.warningState", 0);
	json.insert("warnings.startTime", "2022-11-11 11:11:11");
	json.insert("warnings.endTime", "2022-11-11 11:11:11");
	QJsonDocument document;
	document.setObject(json);
	QByteArray dataArray = document.toJson(QJsonDocument::Compact);
	qDebug() << dataArray;*/

	//QByteArray * b = &append;
	//QString u = "http://211.67.27.249:8080/MonitorWeb/warning/warning_add.action";
	//QString *uu = &u;
	//CNetCommunication * test = new CNetCommunication(uu,b);



	/*if (test->PostWarningInfo() != true)
	{
		qDebug() << test->postresult;
	}
	else
	{
		qDebug() << "true";
	}*/

	/*QString  U = "http://211.67.27.249:8080/MonitorWeb/roomAreaInfo/roomAreaInfo_getByDev.action?deviceserial=786297833";
	QString * u1 = &U;
	CNetCommunication * getTest = new CNetCommunication(u1);
	if (getTest->GetInfo() != true)
	{
		;
	}
	else
	{
		qDebug() << "true";
	}*/

	QString uu = "http://211.67.27.249:8080/MonitorWeb/roomCamera/roomCamera_getCameraElders.action?deviceSerial=786297833";
	QString *u = &uu;
	CNetCommunication * getPhoto = new CNetCommunication(u);
	//getPhoto->GetPhoto();
	return a.exec();
}
