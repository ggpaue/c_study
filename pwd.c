#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct stat file_stat;

void print_file_stat(struct stat *fs) {
	printf("inode: %ld\n", fs -> st_ino);
	printf("protection: %o\n", fs -> st_mode);
	printf("number of hard links: %lu\n", fs -> st_nlink);
	printf("user ID of owner: %d\n", fs -> st_uid);
	printf("group ID of owner: %d\n", fs -> st_gid);
	printf("file size in bytes: %ld\n", fs -> st_size);
	printf("time of last access: %s\n", ctime(&fs -> st_atime));
	printf("time of last modification: %s\n", ctime(&fs -> st_mtime));
	printf("time of last change: %s\n", ctime(&fs -> st_ctime));
}

int main(int argc, char *argv[]) {
	if(2 != argc) {
		fprintf(stderr, "Usage: %s filename...\n", argv[0]);
		exit(-1);
	}

	DIR *dp = NULL;
	struct dirent *dptr = NULL;
	if(NULL == (dp = opendir(argv[1]))) {
		fprintf(stderr, "Cannot open input directory %s\n", argv[1]);
		exit(-1);
	} else {
		printf("directory %s content list: \n", argv[1]);
		while(NULL != (dptr = readdir(dp))) {
			printf("inode-number: %-10ld \t filename: %s\n", dptr -> d_ino, dptr -> d_name);
		}
		closedir(dp)
	}
	/*
	if(0 != stat(argv[1], &file_stat)) {
		perror("stat");
		exit(-1);
	}

	print_file_stat(&file_stat);
	*/
	return 0;
}
/*
int main(void) {
	char buf[1024];
	char *cwd = getcwd(buf, sizeof(buf));

	if(NULL == cwd) {
		perror("Failed to get current working directory. \n");
		exit(-1);
	} else {
		printf("Current working directory is: %s\n", cwd);
	}
	return 0;
}
*/