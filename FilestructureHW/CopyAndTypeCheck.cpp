#define _CRT_SECURE_NO_WARNINGS
#include "backup.h"

int fileTypeCheck(char* fileName) {
	_finddatai64_t c_file;
	intptr_t hFile;
	int result;

	if ((hFile = _findfirsti64(fileName, &c_file)) == -1L)
		result = -1; // 해당 파일이 없을 경우
	else
		if (c_file.attrib & _A_SUBDIR)
			result = 0; // 디렉토리일 경우
		else
			result = 1; // 파일일 경우

	_findclose(hFile);

	return result;
}

int copy(char *sourceFile, char *destinationFile)
{
	FILE *existFile, *newFile;
	int copiedData;
	if ((existFile = fopen(sourceFile, "rb")) == NULL)
		return -1;
	if ((newFile = fopen(destinationFile, "wb")) == NULL)
	{
		fclose(existFile);
		return -1;
	}

	while (1)
	{
		copiedData = fgetc(existFile);   //원본 파일에서 한 바이트를 읽어냄.

		if (!feof(existFile))      
			fputc(copiedData, newFile);  
		else                   
			break;               
	}

	fclose(existFile);
	fclose(newFile);

	return(0);   
}

int wholeCopy(char *sourceDir, char* destinationDir) {
	char *sourceFile;
	char *destinationFile;
	char *sourceFileList;
	char *newDestinationPath;
	char *newSourcePath;
	_finddatai64_t fd;
	long handle;
	int result = 1;
	const int notExist = -1, directory = 0, files = 1;
	
	sourceFileList = (char*)malloc(strlen(sourceDir) + strlen("*.*") + 1);
	strcpy(sourceFileList, sourceDir);
	strcat(sourceFileList, "*.*");

	handle = _findfirsti64(sourceFileList, &fd);  //경로 내 모든 파일을 찾는다.

	if (handle == -1)
	{
		printf("No file is in there or incorrect path input");
		return -1;
	}

	/*목적지 디렉토리가 없을 경우 생성*/
	if (fileTypeCheck(destinationDir) == notExist) {
		_mkdir(destinationDir);
	}

	/*파일 복사*/
	while (result != -1)
	{
		while (!strcmp(fd.name, ".") || !strcmp(fd.name, "..")) {
			result = _findnexti64(handle, &fd);
			if (result == -1) {
				break;
			}
		}
		if (result == -1) {
			break;
		}
		/*소스 파일 경로 + 파일 이름*/
		sourceFile = (char*)malloc(strlen(sourceDir) + strlen(fd.name) + 1);
		strcpy(sourceFile, sourceDir);
		strcat(sourceFile, fd.name);
		
		/*목적지 파일 경로 + 파일 이름*/
		destinationFile = (char*)malloc(strlen(destinationDir) + strlen(fd.name) + 1);		
		strcpy(destinationFile, destinationDir);
		strcat(destinationFile, fd.name);

		/*복사할 자료가 디렉토리일 경우*/
		if (fileTypeCheck(sourceFile) == directory) {
			/*해당 소스 디렉토리를 새로운 경로로 지정*/
			newSourcePath = (char*)malloc(strlen(sourceFile) + strlen("\\") + 1);
			strcpy(newSourcePath, sourceFile);
			strcat(newSourcePath, "\\");
			/*새로운 타겟 목적지 경로를 설정*/
			newDestinationPath = (char*)malloc(strlen(destinationFile) + strlen("\\") + 1);
			strcpy(newDestinationPath, destinationFile);
			strcat(newDestinationPath, "\\");

			/*목적지에 복사할 디렉토리가 없을경우*/
			if (fileTypeCheck(destinationFile) == notExist || fileTypeCheck(destinationFile) == files) {
				_mkdir(destinationFile); //해당 디렉토리 생성				
				wholeCopy(newSourcePath, newDestinationPath); /*Recursive 복사*/
			}
			/*목적지에 복사할 디렉토리가 이미 있을 경우*/
			else {				
				if (timeCheck(sourceFile, destinationFile) > 0) {
					wholeCopy(newSourcePath, newDestinationPath);
				}				
			}
			free(newSourcePath);
			free(newDestinationPath);
		}

		/*복사할 자료가 파일일 경우*/
		else if (fileTypeCheck(sourceFile) == files) {
			/*목적지에 복사할 파일이 존재하지 않을 경우*/
			if (fileTypeCheck(destinationFile) == notExist || fileTypeCheck(destinationFile) == directory) {
				if (copy(sourceFile, destinationFile) == 0)
					makeLog(destinationFile);
				else
					fprintf(stderr, "%s  실패\n", destinationFile);
			}
			/*목적지에 복사할 파일이 이미 존재할 경우*/
			else {
				if (timeCheck(sourceFile, destinationFile) > 0) {
					if (copy(sourceFile, destinationFile) == 0)
						makeLog(destinationFile);
					else
						fprintf(stderr, "%s  실패\n", destinationFile);
				}
			}
		}

		free(sourceFile);
		free(destinationFile);
		result = _findnexti64(handle, &fd);
	}

	_findclose(handle);
	return 0;
}