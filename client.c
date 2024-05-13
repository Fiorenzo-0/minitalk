/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbruschi <lbruschi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:29:42 by lbruschi          #+#    #+#             */
/*   Updated: 2024/05/13 15:54:01 by lbruschi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_character(int pid, unsigned char c)
{
	int	bit;

	bit = 8;
	while (bit > 0)
	{
		bit--;
		if ((c >> bit) % 2 == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				write(2, "Error: unexpected signal 2 behavior\n", 37);
				exit(EXIT_FAILURE);
			}
		}
		else if (kill(pid, SIGUSR1) == -1)
		{
			write(2, "Error: unexpected signal 1 behavior\n", 37);
			exit(EXIT_FAILURE);
		}
		pause();
		usleep(42);
	}
}

void	return_message(int sig)
{
	if (sig == SIGUSR2)
	{
		ft_printf("<client [%i]>\n", getpid());
		ft_printf("[Message received]\n");
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	i = 0;
	signal(SIGUSR1, return_message);
	signal(SIGUSR2, return_message);
	if (argc != 3)
	{
		write(2, "ERROR: wrong number of arg\n", 28);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(2, "ERROR: invalid Pid\n", 20);
		exit(EXIT_FAILURE);
	}
	while (argv[2][i])
		send_character(pid, argv[2][i++]);
	send_character(pid, '\0');
	return (0);
}
