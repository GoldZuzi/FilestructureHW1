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
	_finddata_t fd;
	long handle;
	int result = 1;
	const int notExist = -1, directory = 0, files = 1;
	
	sourceFileList = (char*)malloc(strlen(sourceDir) + strlen("*.*") + 1);
	strcpy(sourceFileList, sourceDir);
	strcat(sourceFileList, "*.*");

	handle = _findfirst(sourceFileList, &fd);  //��� �� ��� ������ ã�´�.
	_findnext(handle, &fd); //. ����
	_findnext(handle, &fd); //.. ����

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

			newSourcePath = (char*)malloc(strlen(sourceFile) + strlen("\\") + 1);
			strcpy(newSourcePath, sourceFile);
			strcat(newSourcePath, "\\");

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
					printf("����\n");
				else
					fprintf(stderr, "����\n");
			}
			/*�������� ������ ������ �̹� ������ ���*/
			else {
				if (timeCheck(sourceFile, destinationFile) > 0) {
					if (copy(sourceFile, destinationFile) == 0)
						printf("����\n");
					else
						fprintf(stderr, "����\n");
				}
			}
		}

		free(sourceFile);
		free(destinationFile);
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	return 0;
}