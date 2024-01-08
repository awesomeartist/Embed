// 功能：获取系统时间并写入文本

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

// tm结构
// struct tm
// {
// 	int tm_sec; /* seconds */
// 	int tm_min; /* minutes */
// 	int tm_hour; /* hours */
// 	int tm_mday; /* day of the month */
// 	int tm_mon; /* month */
// 	int tm_year; /* year */
// 	int tm_wday; /* day of the week */
// 	int tm_yday; /* day in the year */
// 	int tm_isdst; /* daylight saving time */
// };

void writelog(const char *fileName,const char *log)
{
	time_t tDate;
	struct tm *eventTime;
	time(&tDate);       //得到系统时间
	eventTime = localtime(&tDate);      //将time_t 数据类型转化为 struct tm 结构

	int iYear=eventTime->tm_year + 1900;
	int iMon = eventTime->tm_mon + 1;
    int iDay = eventTime->tm_mday;
	int iHour = eventTime->tm_hour;
	int iMin = eventTime->tm_min;
	int iSec = eventTime->tm_sec;

	printf("tm_isdst = %d\n", eventTime->tm_isdst);

	char sDate[16];
	sprintf(sDate, "%04d-%02d-%02d", iYear, iMon, iDay);
	char sTime[16];
	sprintf(sTime, "%02d:%02d:%02d", iHour, iMin, iSec);
	char s[128];
	sprintf(s, "%s %s %s\n", sDate, sTime, log);
    
	FILE *p = fopen(fileName, "a+");
	if (p == NULL) {
		printf("write log %s error: %s\n", fileName, strerror(errno));
	}
	else {
		fputs(s, p);
		fclose(p);
	}
	return;
}

int main(int argc, char *argv[]) {

	if (argc < 2)
		return 0;
	writelog(argv[1], argv[2]);

	return 0;
}
// 运行结果
// user@ubuntu$./build.out log.txt log
// user@ubuntu$tm_isdst = 0
// user@ubuntu$cat log.txt
// 2023-04-04 11:19:29 log

