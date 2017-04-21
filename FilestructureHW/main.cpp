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
	handle = _findfirst("C:\\*.*", &fd);  //��� �� ��� ������ ã�´�.

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
			/*�������� ������ ���丮�� �������*/
			if (fileTypeCheck(destinationFile) == notExist || fileTypeCheck(destinationFile) == files) {
				mkdir(destinationFile); //�ش� ���丮 ����
										/*Recursive ����*/
			}
			/*�������� ������ ���丮�� �̹� ���� ���*/
			if (/*������ ��¥ ��*/) {
				/*Recursive ����*/
			}
		}
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
				if (/*������ ��¥ ��*/) {
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
	return;
}