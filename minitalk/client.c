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

void send_signal(int pid, char c)
{
	int arr[8];
	int i;
	int j;

	j = 128;
	i = 7;
	while (i >= 0)
	{
		if (c & j)
			arr[i] = 1;
		else
			arr[i] = 0;
		if (j > 0)
			j >>= 1;
		i--;
	}
	while (++i < 8)
	{
		if (arr[i] == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
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
