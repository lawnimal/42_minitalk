/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavina <msavina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:34:44 by msavina           #+#    #+#             */
/*   Updated: 2023/12/20 21:04:58 by msavina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
			usleep(160);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(160);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		write(1, R, ft_strlen(R));
		write(1, "Provide the correct number of arguments.\n", 41);
		write(1, X, ft_strlen(X));
		return (EXIT_FAILURE);
	}
	ft_kill(ft_atoi(argv[1]), argv[2]);
	return (EXIT_SUCCESS);
}
