#include "minitalk.h"

int ft_atoi(const char *str)
{
	int result;
	int sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		sign = -1;
	else if (*str == '+')
		sign = 1;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}

void send_bit(int pid, char c, int bit)
{
	int mask;
	int signal;

	if (bit < 0)
		return;
	mask = 1 << bit;
	if (c & mask)
		signal = SIGUSR2;
	else
		signal = SIGUSR1;
	kill(pid, signal);
	usleep(100);
	send_bit(pid, c, bit - 1);
}

void send_signal(int pid, char c)
{
	send_bit(pid, c, 7);
}

int main(int argc, char **argv)
{
	int pid;

	if (argc != 3)
		write(1, "Error bro, something is wrong!", 31);
	else
	{
		pid = ft_atoi(argv[1]);
		while (argv[2] && *argv[2])
			send_signal(pid, *argv[2]++);
		send_signal(pid, '\n');
	}
	return (0);
}
