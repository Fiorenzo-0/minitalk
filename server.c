/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbruschi <lbruschi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:29:51 by lbruschi          #+#    #+#             */
/*   Updated: 2024/05/13 17:13:18 by lbruschi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig_of_bit, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bit_counter;

	(void)context;
	c <<= 1;
	c |= (sig_of_bit == SIGUSR1);
	bit_counter++;
	if (bit_counter == 8)
	{
		ft_printf("%c", c);
		if (c == 0)
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR2);
		}
		bit_counter = 0;
		c = 0;
	}
	usleep(42);
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		write(2, "Error: unexpected signal behavior\n", 35);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	struct sigaction	sig;

	ft_printf("PID of the server: %i\n", getpid());
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = handler;
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
	{
		write(2, "Error: setting of the signal's handler failled\n", 48);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sig, NULL) == -1)
	{
		write(2, "Error: setting of the signal's handler failled\n", 48);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
