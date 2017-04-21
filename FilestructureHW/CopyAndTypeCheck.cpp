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