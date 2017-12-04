#include <CNetCommunication.h>

CNetCommunication::CNetCommunication(QString * url,QByteArray * bytearray)
{
	this->postData = bytearray;
	this->url = url;
	//*(this->url)+= "warnings.deviceserial=786297833&warnings.warningType=1&warnings.roomAreaTypeId=2&warnings.warningState=0&warnings.startTime=2000-1-1&warnings.endTime=2000-1-1 ";
	manager = new QNetworkAccessManager(this);
	reply = NULL;
	status = NULL;
}

bool CNetCommunication::AnalysePostReturn(QString json)
{
	QString JsonText = json;
	QString TextValue = "";
	QScriptValue jsontext;
	QScriptEngine engineText;
	jsontext = engineText.evaluate("value = " + JsonText);
	QScriptValueIterator iteratorText(jsontext);
	while (iteratorText.hasNext())
	{
		iteratorText.next();
		if (iteratorText.name() == "success")//�ж��Ƿ����ݸ�ʽ�Ƿ�ɹ�
		{
			TextValue = iteratorText.value().toString();
			if (TextValue == "true")
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool CNetCommunication::PostWarningInfo()
{
	QNetworkRequest request;
	//request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
	request.setUrl(QUrl(*url)); //��ַ��Ϣ

	if (postData != NULL)
	{
		QEventLoop loop;
		reply = manager->post(request,*postData);

		connect(reply, SIGNAL(finished()), &loop, SLOT(quit())); //��������ź�
		loop.exec();
		int nHttpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http������
		if (nHttpCode == 200)//�ɹ�
		{
			//����ɹ�
			postresult = reply->readAll();
			if (AnalysePostReturn(postresult) == false)//���ݸ�ʽ�Ƿ�����
			{
				status = false;
			}
			else
			{
				status = true;
			}
			reply->deleteLater();
			this->deleteLater(); //�ͷ��ڴ�
		}
		else//http״̬����ʾ����
		{
			//����ʧ��
			status = false;
			reply->deleteLater();
			this->deleteLater(); //�ͷ��ڴ�
		}
	}
	return status;
}


void CNetCommunication::ParseJson(QByteArray bytearray)
{
	QByteArray bytearray1 = bytearray;
	QJsonParseError jsonError;
	QJsonDocument doucment = QJsonDocument::fromJson(bytearray1, &jsonError);
	if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))   // ����δ��������
	{
		if (doucment.isObject()) // JSON �ĵ�Ϊ����
		{
			QJsonObject object = doucment.object();  // ת��Ϊ����
		}
	}
}

void CNetCommunication::GetInfo()
{
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
	request.setUrl(*url); //��ַ��Ϣ
	QEventLoop loop;
	reply = manager->get(request); //����get����
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit())); //��������ź�
	loop.exec();
	int nHttpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http������
	if (nHttpCode == 200)//�ɹ�
	{
		//����ɹ�
		getresult = reply->readAll();
		ParseJson(getresult);
		reply->deleteLater();
		this->deleteLater(); //�ͷ��ڴ�
	}
	else//http״̬����ʾ����
	{
		//����ʧ��
		reply->deleteLater();
		this->deleteLater(); //�ͷ��ڴ�
	}
}
