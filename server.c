#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "./ft_printf/libft/libft.h"
#include "./ft_printf/ft_printf.h"

static int character[5];
//character[0]	character
//character[1]	index
//character[2]	pid
//character[3]	pid status
//character[4]	message

void handler1(){
	if(character[1] == 0)
	{

		if(character[3] == 0)
			character[3] = 1;

		else if(character[3] == 1)
			character[3] = 2;
		else
			write(0, &character[0], 1);
		character[1] = 31;
		character[0] = 0;
		if(character[3] == 2)
		{
		if(character[4] > 0)
			character[4]--;
		else
		{
			kill(character[2], SIGUSR1);
			character[3] = 0;
			character[2] = 0;
		}		
		}
	}
	else
	{
		character[1]--;
	}
	}


void handler2(){
	if(character[3] == 0)
		character[2] |= 1UL << character[1];
	else if(character[3] == 1)
		character[4] |= 1UL << character[1];
	else
		character[0] |= 1UL << character[1];
	if(!character[1])
	{
		if(character[3] == 0)
			character[3] = 1;
		else if(character[3] == 1)
			character[3] = 2;
		else
			write(0, &character[0], 1);
		character[1] = 31;
		character[0] = 0;
		if(character[3] == 2)
		{
		if(character[4] > 0)
			character[4]--;
		else
		{
			kill(character[2], SIGUSR1);
			character[3] = 0;
			character[2] = 0;
		}		
		}
	}
	else
		character[1]--;
	}

int main (void)
{
    struct sigaction	sa1;
	struct sigaction	sa2;

	character[0] = 0;
	character[1] = 31;
	character[2] = 0;
	character[3] = 0;
	character[4] = 0;
    sa1.sa_handler = handler1;
	sa2.sa_handler = handler2;
	ft_printf("pid: %d\n", getpid());
  	if(sigaction(SIGUSR2, &sa2, NULL) == -1)
	{
		kill(character[2], SIGUSR2);
        perror("SIGACTION");
	}
	if(sigaction(SIGUSR1, &sa1, NULL) == -1)
	{
		kill(character[2], SIGUSR2);
        perror("SIGACTION");	
	}
    while (1)
    {
    }
}