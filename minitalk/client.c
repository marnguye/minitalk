/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:45:58 by marnguye          #+#    #+#             */
/*   Updated: 2024/01/20 16:46:02 by marnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *str)
{
	int	num;
	int	i;
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	i = 0;
	num = 0;
	while (i < len)
		num = (num * 10) + (str[i++] - 48);
	return (num);
}

void	send_signal(int pid, char c)
{
	int	arr[8];
	int	i;
	int	j;

	i = 7;
	j = 128;
	while (i >= 0)
	{
		if (c & j)
			arr[i] = 1;
		else
			arr[i] = 0;
		j >>= 1;
		i--;
	}
	while (++i < 8)
	{
		if (arr[i] == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	long	pid;

	if (argc != 3)
		write(1, "Error", 6);
	else
	{
		pid = ft_atoi(argv[1]);
		while (argv[2] && *argv[2])
			send_signal(pid, *argv[2]++);
		send_signal(pid, '\n');
	}
	return (0);
}
