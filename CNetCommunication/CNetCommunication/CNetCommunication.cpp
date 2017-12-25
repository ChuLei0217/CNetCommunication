#include <CNetCommunication.h>

CNetCommunication::CNetCommunication(QString * url, QByteArray * warninginfo)
{
	this->postData = warninginfo;
	this->url = url;
	manager = new QNetworkAccessManager(this);
	reply = NULL;
	status = NULL;
}

CNetCommunication::CNetCommunication(QString * Url)
{
	this->url = Url;
	manager = new QNetworkAccessManager(this);
	reply = NULL;
}

bool CNetCommunication::AnalysePostReturn(QString json)//分析post后返回的json数据
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
	//request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json; charset=utf-8"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
	request.setUrl(QUrl(*url)); //地址信息

	if (postData != NULL)
	{
		QEventLoop loop;
		reply = manager->post(request, *postData);

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
	QString JsonText = bytearray;
	QScriptValue jsontext;
	QScriptEngine engineText;
	jsontext = engineText.evaluate("value = " + JsonText);
	qDebug() << "success: " << jsontext.property("success").toBool();
	bool isSuccess = jsontext.property("success").toBool();
	if (jsontext.property("result").isArray() && isSuccess != false)   //解析json数组  
	{
		QScriptValueIterator it(jsontext.property("result"));
		while (it.hasNext())
		{
			it.next();
			if (!it.value().property("deviceserial").toString().isEmpty())
			{
				qDebug() << "areaTypeId :" << it.value().property("areaTypeId").toInteger();
				qDebug() << "height :" << it.value().property("height").toInteger();
				qDebug() << "pointX :" << it.value().property("pointX").toInteger();
				qDebug() << "pointY :" << it.value().property("pointY").toInteger();
				qDebug() << "width :" << it.value().property("width").toInteger();
			}
		}
	}
}

bool CNetCommunication::GetInfo()//获得电子围栏的信息
{
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
	request.setUrl(QUrl(*url)); //地址信息
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
		return true;
	}
	else//http状态码显示错误
	{
		//请求失败
		reply->deleteLater();
		this->deleteLater(); //释放内存
		return false;
	}
}

void CNetCommunication::DownloadPhoto(QString url)
{
	QNetworkAccessManager* manager1 = new QNetworkAccessManager();
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
	request.setUrl(QUrl(url)); //地址信息
	QEventLoop loop;
	QNetworkReply* reply1 = manager1->get(request); //发起get请求
	connect(reply1, SIGNAL(finished()), &loop, SLOT(quit())); //请求完成信号
	loop.exec();
	int nHttpCode = reply1->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
	if (nHttpCode == 200)//成功
	{
		//请求成功
		QByteArray photoByte = reply1->readAll();
		QBuffer buffer(&photoByte);
		buffer.open(QIODevice::ReadOnly);
		QImageReader reader(&buffer,"JPG");
		QImage image = reader.read();
		//image.save("456.jpg");
		cv::Mat mat;
		switch (image.format())
		{
		case QImage::Format_ARGB32:
		case QImage::Format_RGB32:
		case QImage::Format_ARGB32_Premultiplied:
			mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
			break;
		case QImage::Format_RGB888:
			mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
			cv::cvtColor(mat, mat, CV_BGR2RGB);
			break;
		case QImage::Format_Indexed8:
			mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
			break;
		}
		cv::imshow("", mat);
		this->Photo->push_back(mat);
		reply1->deleteLater();
		//this->deleteLater(); //释放内存
	}
	else//http状态码显示错误
	{
		//请求失败
		reply1->deleteLater();
		//this->deleteLater(); //释放内存
	}

}

void CNetCommunication::ParsePhotoJson(QByteArray bytearray)
{
	this->Photo->clear();
	QString JsonText = bytearray;
	QScriptValue jsontext;
	QScriptEngine engineText;
	QScriptValue elders;
	jsontext = engineText.evaluate("value = " + JsonText);
	qDebug() << "success: " << jsontext.property("success").toBool();
	bool isSuccess = jsontext.property("success").toBool();
	elders=jsontext.property("result").toObject();
	if (elders.property("elders").isArray() && isSuccess != false)   //解析elders数组  
	{
		QScriptValueIterator it(elders.property("elders"));
		while (it.hasNext())
		{
			it.next();
			if (!it.value().property("picPath").toString().isEmpty())
			{
				qDebug() << "picPath :" << it.value().property("picPath").toString();
				DownloadPhoto(it.value().property("picPath").toString());
				//下载照片，保存到photo里面
			}
		}
	}
}

void CNetCommunication::GetPhoto(std::vector<cv::Mat> * photo)
{
	this->Photo = photo;
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
	request.setUrl(QUrl(*url)); //地址信息
	QEventLoop loop;
	reply = manager->get(request); //发起get请求
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit())); //请求完成信号
	loop.exec();
	int nHttpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
	if (nHttpCode == 200)//成功
	{
		//请求成功
		QByteArray photoinfo = reply->readAll();
		ParsePhotoJson(photoinfo);
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
