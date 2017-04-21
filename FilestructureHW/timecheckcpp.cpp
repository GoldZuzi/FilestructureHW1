#pragma warning(disable:4996)

#include <stdio.h>

#include <sys/stat.h>

#include <time.h>

#include <errno.h>

int timecheck(char* sourceFilename, char* destinationFilename) {

	struct _stat buf_source;
	struct _stat buf_destination;
	char* filename = "sourceFilename";
	




	if (_stat(filename, &buf_source) != 0) {

		switch (errno) {

		case ENOENT:

			fprintf(stderr, "File %s not found.\n", filename); break;

		case EINVAL:

			fprintf(stderr, "Invalid parameter to _stat.\n"); break;

		default:

			fprintf(stderr, "Unexpected error in _stat.\n");

		}

	}

	else {

		
		1900 + localtime(&buf_source.st_ctime)->tm_year);
		printf("\tTime Creation     : %d\n", 1 + localtime(&buf_source.st_ctime)->tm_mon);
		printf("\tTime Creation     : %d\n", localtime(&buf_source.st_ctime)->tm_mday);
		printf("\tTime Creation     : %d\n", localtime(&buf_source.st_ctime)->tm_hour);
		printf("\tTime Creation     : %d\n", localtime(&buf_source.st_ctime)->tm_min);
		printf("\tTime Creation     : %d\n", localtime(&buf_source.st_ctime)->tm_sec);


		if()



	}

}
