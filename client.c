#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "./ft_printf/libft/libft.h"
#include <wchar.h>      /* wint_t */
#include "./ft_printf/ft_printf.h"

void handler1(){
    ft_printf("\033[0;32m");
    ft_printf("Message was received!\n");
    ft_printf("\033[0m");
}

void sendCharacter(int c, int pid)
{
    int i;

    i = 32;
    while(--i >= 0)
    {
        if((c >> i) & 0x01)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        usleep(20);
    }
}

int main(int argc, char *argv[])
{
    if(argc < 3)
        write(0, "you need 2 parameters: pid, message n", 36);
    int j;
    struct sigaction    sa;
    int len;

    sa.sa_handler = handler1;
    j = -1;
    len = ft_strlen(argv[2]) + 1;
    if(sigaction(SIGUSR1, &sa, NULL) == -1)
        perror("SIGACTION");
    sendCharacter(getpid(), ft_atoi(argv[1]));
    sendCharacter(len, ft_atoi(argv[1]));
    while(argv[2][++j])
    {
        sendCharacter(argv[2][j], ft_atoi(argv[1]));
    }
    sendCharacter('\n', ft_atoi(argv[1]));
}


