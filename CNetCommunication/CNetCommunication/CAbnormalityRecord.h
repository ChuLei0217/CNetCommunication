#pragma once
#include <sstream>
#include <time.h> 
class AbnormalityRecord
{
public:
	/*std::string room_id;
	std::string room_camera_id;
	std::string deviceSerial;
	std::string warning_type;
	std::string warning_detail;
	std::string warning_state;*/
	std::string deviceserial;
	std::string warningType;
	std::string warningDetail;
	int roomAreaTypeId;
	int warningState;

	int start_time_year;
	int start_time_month;
	int start_time_day;
	int start_time_hour;
	int start_time_min;
	int start_time_sec;
	int end_time_year;
	int end_time_month;
	int end_time_day;
	int end_time_hour;
	int end_time_min;
	int end_time_sec;
public:
	AbnormalityRecord(){};
	virtual ~AbnormalityRecord(){};
	std::string getStart_time_toString(){
		std::stringstream ss;
		ss << start_time_year << "-" << start_time_month << "-" << start_time_day << " ";
		std::stringstream stime;
		stime.fill('0');
		stime.width(2);
		stime << start_time_hour << ":";
		stime.width(2);
		stime << start_time_min << ":";
		stime.width(2);
		stime << start_time_sec;
		return (ss.str() + stime.str());
	}
	std::string getEnd_time_toString(){
		std::stringstream ss;
		ss << end_time_year << "-" << end_time_month << "-" << end_time_day << " ";
		std::stringstream stime;
		stime.fill('0');
		stime.width(2);
		stime << end_time_hour << ":";
		stime.width(2);
		stime << end_time_min << ":";
		stime.width(2);
		stime << end_time_sec;
		return (ss.str() + stime.str());
	}
};