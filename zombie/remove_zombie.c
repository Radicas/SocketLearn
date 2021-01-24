#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig);

int main(int argc, char* argv[])
{
	pid_t pid;
	struct sigaction act;
	act.sa_handler = read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGCHLD, &act, 0);

	pid = fork();
	if(pid==0)
	{
		puts("im child process");
		sleep(10);
		return 12;
	}else
	{
		printf("child process id: %d \n", pid);	
		pid = fork();
		if(pid==0)
		{
			puts("im child process 2");		
			sleep(10);
			exit(24);
		}else
		{
			int i;
			printf("child process id: %d \n", pid);	
			for(i=0; i<5; i++)
			{
				puts("wait");
				sleep(5);
			}
		}
	}
	return 0;
}

void read_childproc(int sig)
{
	int status;
	pid_t id = waitpid(-1, &status, WNOHANG);	
	if(WIFEXITED(status))
	{
		printf("removed process id: %d \n", id);
		printf("child send: %d", WEXITSTATUS(status));
	}
}
