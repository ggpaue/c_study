#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define MAX_DIR_DEPTH 256

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

ino_t get_ino_byname(char *filename) {
	struct stat file_stat;
	if(0 != stat(filename, &file_stat)) {
		perror("stat");
		exit(-1);
	}
	return file_stat.st_ino;
}

char* find_name_byino(ino_t ino) {
	DIR *dp = NULL;
	struct dirent *dptr = NULL;
	char *filename = NULL;
	if(NULL == (dp = opendir("."))) {
		fprintf(stderr, "Can not open current directory\n");
		exit(-1);
	} else {
		while(NULL != (dptr = readdir(dp))) {
			if(dptr -> d_ino == ino) {
				filename = strdup(dptr -> d_name);
				break;
			}
		}
		closedir(dp);
	}
	return filename;
}

int main(int argc, char *argv[]) {
	char *dir_stack[MAX_DIR_DEPTH];
	unsigned current_depth = 0;

	for(;;) {
		ino_t current_ino = get_ino_byname(".");
		ino_t parent_ino = get_ino_byname("..");

		if(current_ino == parent_ino) {
			break;
		}

		chdir("..");
		dir_stack[current_depth++] = find_name_byino(current_ino);
		if(current_depth => MAX_DIR_DEPTH) {
			fprintf(stderr, "directory tree is too deep.\n");
			exit(-1);
		}
	}

	int i = current_depth - 1;
	for(i = current_depth - 1; i >= 0; i--) {
		fprintf(stdout, "/%s\n", dir_stack[i]);
	}
	fprintf(stdout, "%s\n", current_depth == 0 ? "/" : "");
	/*
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
	*/
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