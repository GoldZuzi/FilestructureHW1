#define _CRT_SECURE_NO_WARNINGS
#include "backup.h"

void makeLog(char* copiedFileName) {
	FILE *logFile;
	const char *logFileName = "mybackup.log";
	time_t current_Time;
	struct tm *tm;

	current_Time = time(NULL);
	tm = localtime(&current_Time);

	logFile = fopen(logFileName, "a");

	fprintf(logFile,"%d-%d-%d ", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
	fprintf(logFile, "%d:%d:%d    ", tm->tm_hour, tm->tm_min, tm->tm_sec);
	fprintf(logFile, "%s\n", copiedFileName);
	
	fclose(logFile);
}