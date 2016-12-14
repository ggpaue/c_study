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


static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

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