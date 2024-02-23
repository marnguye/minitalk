/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnguye <marnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:05:35 by marnguye          #+#    #+#             */
/*   Updated: 2024/02/23 14:44:53 by marnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

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

void	send_signal(int pid, char c)
{
	send_bit(pid, c, 0);
}

void	send_bit(int pid, char c, int i)
{
	if (i < 8)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
		send_bit(pid, c, i + 1);
	}
}


int	main(int argc, char **argv)
{
	int	pid;

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
