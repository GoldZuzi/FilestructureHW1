#define _CRT_SECURE_NO_WARNINGS
#include "backup.h"

void main()
{
	char *destinationPath = "C:\\backup\\";
	char *sourcePath = "C:\\";
	char *sourceFile;
	char *destinationFile;
	_finddata_t fd;
	long handle;
	int result = 1;
	const int notExist = -1, directory = 0, files = 1;
	handle = _findfirst("C:\\*.*", &fd);  //경로 내 모든 파일을 찾는다.

	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	while (result != -1)
	{
		sourceFile = (char*)malloc(strlen(sourcePath) + strlen(fd.name) + 1);
		destinationFile = (char*)malloc(strlen(destinationPath) + strlen(fd.name) + 1);
		strcpy(sourceFile, sourcePath);
		strcat(sourceFile, fd.name);
		strcpy(destinationFile, destinationPath);
		strcat(destinationFile, fd.name);

		if (fileTypeCheck(sourceFile) == directory) {
			/*목적지에 복사할 디렉토리가 없을경우*/
			if (fileTypeCheck(destinationFile) == notExist || fileTypeCheck(destinationFile) == files) {
				mkdir(destinationFile); //해당 디렉토리 생성
										/*Recursive 복사*/
			}
			/*목적지에 복사할 디렉토리가 이미 있을 경우*/
			if (/*수정된 날짜 비교*/) {
				/*Recursive 복사*/
			}
		}
		else if (fileTypeCheck(sourceFile) == files) {
			/*목적지에 복사할 파일이 존재하지 않을 경우*/
			if (fileTypeCheck(destinationFile) == notExist || fileTypeCheck(destinationFile) == directory) {
				if (copy(sourceFile, destinationFile) == 0)
					printf("성공\n");
				else
					fprintf(stderr, "실패\n");
			}
			/*목적지에 복사할 파일이 이미 존재할 경우*/
			else {
				if (/*수정된 날짜 비교*/) {
					if (copy(sourceFile, destinationFile) == 0)
						printf("성공\n");
					else
						fprintf(stderr, "실패\n");
				}
			}
		}

		free(sourceFile);
		free(destinationFile);
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	return;
}