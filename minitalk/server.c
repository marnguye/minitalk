/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:46:08 by marnguye          #+#    #+#             */
/*   Updated: 2024/01/20 16:46:11 by marnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr(long nbr)
{
	char	buff;

	if (nbr / 10 > 0)
		ft_putnbr(nbr / 10);
	buff = nbr % 10 + '0';
	write (1, &buff, 1);
}

void	handle_signal(int signal)
{
	static int	i;
	static int	j;
	int			num;

	num = 0;
	if (signal == SIGUSR1)
		num = 0;
	j = (j << 1) + num;
	i++;
	if (i == 8)
	{
		write (1, &j, 1);
		i = 0;
		j = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	action.sa_handler = handle_signal;
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	write(1, "What's up bro welcome to my minitalk. Let's chat a bit.", 55);
	write(1, "\n", 1);
	write(1, "PID: ", 5);
	ft_putnbr(getpid());
	while (1)
		usleep(1);
	return (0);
}
