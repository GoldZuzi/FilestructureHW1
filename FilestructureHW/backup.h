#pragma once
#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

int fileTypeCheck(char* fileName);
int copy(char *sourceFile, char *destinationFile);
int wholeCopy(char *sourceDir, char* destinationDir);
int timeCheck(char* sourceFileName, char* destinationFileName);