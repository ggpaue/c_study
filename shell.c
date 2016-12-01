#include <signal.h>

#define MAX 1024

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

void print_prompt();

void scan_command(char *command);

void *parse(char *command, int time);

void parse_semicolon(char *command);
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