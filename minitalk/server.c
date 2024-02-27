#include "minitalk.h"

void ft_putnbr(long nbr)
{
	char buff;
	if (nbr / 10 > 0)
		ft_putnbr(nbr / 10);
	buff = nbr % 10 + '0';
	write(1, &buff, 1);
}

void handle_signal(int signal)
{
	static int i;
	static int j;
	int num;

	if (signal == SIGUSR1)
		num = 0;
	else
		num = 1;
	j = (j << 1) + num;
	i++;
	if (i == 8)
	{
		write(1, &j, 1);
		i = 0;
		j = 0;
	}
}

int main(void)
{
	struct sigaction action;
	action.sa_handler = handle_signal;
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	write(1, "What's up bro, welcome to the minitalk, let's talk a bit.", 58);
	write(1, " PID: ", 7);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}