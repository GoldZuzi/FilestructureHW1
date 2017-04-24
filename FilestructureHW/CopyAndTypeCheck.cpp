#define _CRT_SECURE_NO_WARNINGS
#include "backup.h"

int fileTypeCheck(char* fileName) {
	_finddatai64_t c_file;
	intptr_t hFile;
	int result;

	if ((hFile = _findfirsti64(fileName, &c_file)) == -1L)
		result = -1; // �ش� ������ ���� ���
	else
		if (c_file.attrib & _A_SUBDIR)
			result = 0; // ���丮�� ���
		else
			result = 1; // ������ ���

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
		copiedData = fgetc(existFile);   //���� ���Ͽ��� �� ����Ʈ�� �о.

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

	handle = _findfirsti64(sourceFileList, &fd);  //��� �� ��� ������ ã�´�.

	if (handle == -1)
	{
		printf("No file is in there or incorrect path input");
		return -1;
	}

	/*������ ���丮�� ���� ��� ����*/
	if (fileTypeCheck(destinationDir) == notExist) {
		_mkdir(destinationDir);
	}

	/*���� ����*/
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
		/*�ҽ� ���� ��� + ���� �̸�*/
		sourceFile = (char*)malloc(strlen(sourceDir) + strlen(fd.name) + 1);
		strcpy(sourceFile, sourceDir);
		strcat(sourceFile, fd.name);
		
		/*������ ���� ��� + ���� �̸�*/
		destinationFile = (char*)malloc(strlen(destinationDir) + strlen(fd.name) + 1);		
		strcpy(destinationFile, destinationDir);
		strcat(destinationFile, fd.name);

		/*������ �ڷᰡ ���丮�� ���*/
		if (fileTypeCheck(sourceFile) == directory) {
			/*�ش� �ҽ� ���丮�� ���ο� ��η� ����*/
			newSourcePath = (char*)malloc(strlen(sourceFile) + strlen("\\") + 1);
			strcpy(newSourcePath, sourceFile);
			strcat(newSourcePath, "\\");
			/*���ο� Ÿ�� ������ ��θ� ����*/
			newDestinationPath = (char*)malloc(strlen(destinationFile) + strlen("\\") + 1);
			strcpy(newDestinationPath, destinationFile);
			strcat(newDestinationPath, "\\");

			/*�������� ������ ���丮�� �������*/
			if (fileTypeCheck(destinationFile) == notExist || fileTypeCheck(destinationFile) == files) {
				_mkdir(destinationFile); //�ش� ���丮 ����				
				wholeCopy(newSourcePath, newDestinationPath); /*Recursive ����*/
			}
			/*�������� ������ ���丮�� �̹� ���� ���*/
			else {				
				if (timeCheck(sourceFile, destinationFile) > 0) {
					wholeCopy(newSourcePath, newDestinationPath);
				}				
			}
			free(newSourcePath);
			free(newDestinationPath);
		}

		/*������ �ڷᰡ ������ ���*/
		else if (fileTypeCheck(sourceFile) == files) {
			/*�������� ������ ������ �������� ���� ���*/
			if (fileTypeCheck(destinationFile) == notExist || fileTypeCheck(destinationFile) == directory) {
				if (copy(sourceFile, destinationFile) == 0)
					makeLog(destinationFile);
				else
					fprintf(stderr, "%s  ����\n", destinationFile);
			}
			/*�������� ������ ������ �̹� ������ ���*/
			else {
				if (timeCheck(sourceFile, destinationFile) > 0) {
					if (copy(sourceFile, destinationFile) == 0)
						makeLog(destinationFile);
					else
						fprintf(stderr, "%s  ����\n", destinationFile);
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