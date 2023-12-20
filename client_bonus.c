/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavina <msavina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:27:04 by msavina           #+#    #+#             */
/*   Updated: 2023/12/19 17:45:58 by msavina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler_snd(int sig_num)
{
	static int	received;

	if (sig_num == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(EXIT_SUCCESS);
	}
}

void	ft_kill(int pid, char *str)
{
	int				i;
	unsigned char	bit;

	while (*str)
	{
		i = 8;
		bit = *str++;
		while (i--)
		{
			if (bit >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(150);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(150);
	}
}
void leaks()
{
	system("leaks client_bonus");
}

int	main(int argc, char **argv)
{
	atexit(leaks);
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		write(1, R, ft_strlen(R));
		write(1, "Provide the correct number of arguments.\n", 41);
		write(1, X, ft_strlen(X));
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(G, 1);
	ft_putstr_fd("Sent: ", 1);
	ft_putstr_fd(X, 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(G, 1);
	ft_putstr_fd("Received: ", 1);
	ft_putstr_fd(X, 1);
	signal(SIGUSR1, sig_handler_snd);
	signal(SIGUSR2, sig_handler_snd);
	ft_kill(ft_atoi(argv[1]), argv[2]);
	// while (1)
	// {
		// pause();
	// }
	return (EXIT_SUCCESS);
}