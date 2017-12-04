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
		if (iteratorText.name() == "success")//判断是否数据格式是否成功
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
	request.setUrl(QUrl(*url)); //地址信息

	if (postData != NULL)
	{
		QEventLoop loop;
		reply = manager->post(request,*postData);

		connect(reply, SIGNAL(finished()), &loop, SLOT(quit())); //请求完成信号
		loop.exec();
		int nHttpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
		if (nHttpCode == 200)//成功
		{
			//请求成功
			postresult = reply->readAll();
			if (AnalysePostReturn(postresult) == false)//数据格式是否有误
			{
				status = false;
			}
			else
			{
				status = true;
			}
			reply->deleteLater();
			this->deleteLater(); //释放内存
		}
		else//http状态码显示错误
		{
			//请求失败
			status = false;
			reply->deleteLater();
			this->deleteLater(); //释放内存
		}
	}
	return status;
}


void CNetCommunication::ParseJson(QByteArray bytearray)
{
	QByteArray bytearray1 = bytearray;
	QJsonParseError jsonError;
	QJsonDocument doucment = QJsonDocument::fromJson(bytearray1, &jsonError);
	if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))   // 解析未发生错误
	{
		if (doucment.isObject()) // JSON 文档为对象
		{
			QJsonObject object = doucment.object();  // 转化为对象
		}
	}
}

void CNetCommunication::GetInfo()
{
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
	request.setUrl(*url); //地址信息
	QEventLoop loop;
	reply = manager->get(request); //发起get请求
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit())); //请求完成信号
	loop.exec();
	int nHttpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
	if (nHttpCode == 200)//成功
	{
		//请求成功
		getresult = reply->readAll();
		ParseJson(getresult);
		reply->deleteLater();
		this->deleteLater(); //释放内存
	}
	else//http状态码显示错误
	{
		//请求失败
		reply->deleteLater();
		this->deleteLater(); //释放内存
	}
}
