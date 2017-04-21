#pragma warning(disable:4996)
#include "backup.h"
#include <string>
#include <iostream>
using namespace std;

int timeCheck(char* sourceFileName, char* destinationFileName) {

	struct _stat buf_source;
	struct _stat buf_destination;
	string sourceFileDate;
	string destinationFileDate;
	int compare = 0;
	
	_stat(sourceFileName, &buf_source);
	_stat(destinationFileName, &buf_destination);
	
	sourceFileDate = "" + to_string(localtime(&buf_source.st_mtime)->tm_year) + to_string(localtime(&buf_source.st_mtime)->tm_mon) + to_string(localtime(&buf_source.st_mtime)->tm_mday)\
						+ to_string(localtime(&buf_source.st_mtime)->tm_hour) + to_string(localtime(&buf_source.st_mtime)->tm_min) + to_string(localtime(&buf_source.st_mtime)->tm_sec);
	destinationFileDate = "" + to_string(localtime(&buf_destination.st_mtime)->tm_year) + to_string(localtime(&buf_destination.st_mtime)->tm_mon) + to_string(localtime(&buf_destination.st_mtime)->tm_mday)\
							 + to_string(localtime(&buf_destination.st_mtime)->tm_hour) + to_string(localtime(&buf_destination.st_mtime)->tm_min) + to_string(localtime(&buf_destination.st_mtime)->tm_sec);
	//cout << sourceFileDate << endl;
	//cout << sourceFileDate << endl;
	compare = sourceFileDate.compare(destinationFileDate);
	return compare;
}
