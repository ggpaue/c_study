#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define FTW_F   1
#define FTW_D   2
#define FTW_DNR 3
#define FTW_NS  4

static char *fullpath;
static size_t pathlen; 

struct stat {
	dev_t         st_dev;
	ino_t         st_ino;
	mode_t        st_mode;
	nlink_t       st_nlink;
	uid_t         st_uid;
	gid_t         st_gid;
	dev_t         st_rdev;
	off_t         st_size;
	timestruc_t   st_atim;
	timestruc_t   st_mtim;
	timestruc_t   st_ctim;
	blksize_t     st_blksize;
	blkcnt_t      st_blocks;
	char          st_fstype[_ST_FSTYSZ];    
	
};

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

static int dopath(Myfunc *func) {
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret, n;

	if(lstat(fullpath, &statbuf) < 0) {
		return (func(fullpath, &statbuf, FTW_NS));
	}

	if(S_ISDIR(statbuf.st_mode) == 0) {
		return (func(fullpath, &statbuf, FTW_F));
	}

	if((ret = func(fullpath, &statbuf, FTW_D)) != 0) {
		return ret;
	}

	n = strlen(fullpath);
	if(n + NAME_MAX + 2 > pathlen) {
		pathlen *= 2;
		if((fullpath = realloc(fullpath, pathlen)) == NULL) {
			printf("realloc failed! \n");
		}
	}
	fullpath[n++] = '/';
	fullpath[n] = 0;

	if((dp = opendir(fullpath)) == NULL) {
		return (func(fullpath, &statbuf, FTW_DNR));
	}

	while((dirp = readdir(dp)) != NULL) {
		if(strcmp(dirp -> d_name, ".") == 0 || strcmp(dirp -> d_name, "..") == 0) {
			continue;
		}
		strcpy(&fullpath[n], dirp -> d_name);
		if((ret = dopath(func)) != 0) {
			break;
		}
	}
	fullpath[n - 1] = 0;

	if(closedir(dp) < 0) {
		printf("can't close directory %s", fullpath);
	}
	return ret;
}

static int myftw(char *pathname, Myfunc *func) {
	fullpath = path_alloc(&pathlen);

	if(pathlen <= strlen(pathname)) {
		pathlen = strlen(pathname) * 2;
		if((fullpath = realloc(fullpath, pathlen)) == NULL);
		printf("realloc failed\n");
	}

	strcpy(fullpath, pathname);
	return (dopath(func));
}

static int myfunc(const char *pathname, const struct stat *statptr, int type) {
	switch(type) {
		case FTW_F:
			switch(statptr -> st_mode & S_IFMT) {
				case S_IFREG: 
					nreg++;
					break;
				case S_IFBLK:
					nblk++;
					break;
				case IF_DIR:
					printf("for S_IFDIR for %s", pathname);
			}
			break;

		case FTW_D:
			ndir++;
			break;

		case FTW_DNR:
			printf("%s path not recognized", pathname);

		case FTW_NS:
			printf("%s stat is wrong", pathname);

		default:
			printf("%d category not recognized, pathname: %s", type, pathname);
	}
	return 0;
}

char *path_alloc(size_t *size) {
	char *p = NULL;
	if(!size) return NULL;
	p = malloc(256);
	if(p) {
		*size = 256
	} else {
		*size = 0;
	}
	return p;
}

int main(int argc, char *argv[]) {
	int ret;

	if(argc != 2) {
		printf("fault command input! \n");
		exit(1);
	}

	ret = myftw(argv[1], myfunc);

	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;

	if(ntot == 0) {
		ntot = 1;
	}

	printf("regular files = %7ld, %5.2f %%\n", nreg, nreg*100.0 / ntot);
	printf("directories = %7ld, %5.2f %%\n", ndir, ndir*100.0 / ntot);
	printf("block special = %7ld, %5.2f %%\n", nblk, nblk*100.0 / ntot);
	printf("char special = %7ld, %5.2f %%\n", nchr, nchr*100.0 / ntot);
	printf("FIFOs = %7ld, %5.2f %%\n", nfifo, nfifo`*100.0 / ntot);
	printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink*100.0 / ntot);
	printf("sockets = %7ld, %5.2f %%\n", nsock, nsock*100.0 / ntot);

	exit(ret);
}