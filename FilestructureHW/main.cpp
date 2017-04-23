#define _CRT_SECURE_NO_WARNINGS
#include "backup.h"

int main(int argc, char *argv[])
{
	if (argv[1] == NULL || argv[2] == NULL) {
		printf("Execution Form: ExecutionFile SourcePath DestinationPath\n");
		return -1;
	}
	char *source = argv[1];
	char *destination = argv[2];
	wholeCopy(source, destination);

	return 0;
}