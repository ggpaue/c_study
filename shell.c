#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>


#define MAX 1024
#define MAX_COMM  100
void sig_handle(int sig) {
	if(sig == 2) {
		printf("\nInstead of Ctrl-C type quit\n");
		print_prompt();
	}
	else if(sig == 3) {
		printf("\nType quit to exit\n");
		print_prompt();
	}
	signal(sig, sig_handle);
}

void print_prompt() {
	struct utsname unam_ptr;
	unmae(&uname_ptr);

	getcwd(cwd, sizeof(cwd));
	setbuf(stdout, NULL);
	printf("<%s@%s: %s>", uname_ptr.nodename, uname_ptr.sysname, cwd);
}

void scan_command(char *command) {
	int bytes_read;
	size_t nbytes = MAX;
	bytes_read = getline(&command, &nbytes, stdin);

	bytes_read = -1;
	command[bytes_read] = '\0';
}

void *parse(char *command, int time) {
	char *comm;
	if(time == 0) {
		comm = strtok(command, " ");
	} else {
		comm = strtok(NULL, " ");
	}
	return comm;
}

void parse_semicolon(char *command) {
	int i;
	for(i = 0; i < MAX; i++) {
		all[i] = (char *)malloc(MAX_COMM * sizeof(char));
	}
	i = 0;
	all[i] = strtok(command, ";");
	while(1) {
		i += 1;
		all[i] = strtok(NULL, ";");
		if(all[i] == NULL) {
			break;
		}
	}
}

void cd(char *arg) {
	if(arg == NULL) {
		printf("insufficient arguments\n");
	} else {
		int cond;
		cond = chdir(arg);
		if(cond == -1) {
			printf("wrong path\n");
		}
	}
}

void execute(char *command) {
	char *arg[MAX_COMM];
	char *try;

	arg[0] = parse(command, 0);
	int t =1;
	arg[t] = NULL;

	if(strcmp(arg[0], "cd") == 0) {
		try = parse(command, 1);
		cd(try);
		return;
	}

	if(strcmp(arg[0], "exit") == 0) {
		exit(0);
	}

	while(1) {
		try = parse(command, 1);
		if(try == NULL) break;

		else if(strcmp(try, ">") == 0) {
			try = parse(command, 1);
			file_out(arg, try, 0);
			return;
		}
	}
}

void file_out(char *arg[], char *out_file, int type) {
	int f;
	current_out = dup(1);
	if(type == 0) {
		f = open(out_file, O_WRONLY | O_CREAT, 0777);
		dup2(f,1);
		close(f);
		bf_exec(arg, 0);
	}
}

void file_in(char *arg[], char *in_file, char *out_file, int type) {
	int in;
	in = open(in_file, O_RDONLY);
	current_in = dup(0);
	dup2(in, 0);
	close(in);
	if(type == 0) {
		printf("Going to eecute bf_exec \n");
		bf_exec(arg, 0);
	}

	else if(type == 1) {
		file_out(arg, out_file, 0);
	}

	else {
		file_out(arg, out_file, 1);
	}
	return;
}

int main() {
	char *command;
	int iter = 0;

	command = (char *)malloc(MAX+1);

	while(1) {
		iter = 0;
		signal(SIGINT, sig_handle);
		signal(SIGQUIT, sig_handle);
		signal(SIGCHLD, sig_handle);
		signal(SIGTSTP, SIG_IGN);

		print_prompt();

		scan_command(command);
		parse_semicolon(command);

		while(all[iter] != NULL) {
			execute(all[iter]);
			iter += 1;
		}
	}
}