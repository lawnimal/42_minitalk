/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavina <msavina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:26:48 by msavina           #+#    #+#             */
/*   Updated: 2023/12/19 14:26:51 by msavina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/// @brief handler function of received signal. Called when server receives
// SIGUSER1 or SIGUSER2 signal from client;
/// @param sig_num signal number received (SIGUSR1 or SIGUSER2);
/// @param info provides add-info about the signal, e.g. client's PID;
/// @param context pointer to the execution context (register state, stack
//info, signal mask)

void	sig_handler_rcv(int sig_num, siginfo_t *info, void *context)
{
	static int				i;
	static pid_t			client_pid;
	static unsigned char	c;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	c <<= 1;
	c |= (sig_num == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			write(1, "\n", 1);
			client_pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
	}
}
/// @brief data structure for signal handling, members: sa_handler holds
// the address of signal handler function; sa_mask blocks signals
// during execution of signal handler; sigemptyset function intializes
// the signal set pointet by &sa.sa_mask, which emtying it; member sa_flags
// receives add information about signal, SA_SIGINFO handler func receives
// siginfo_t (PID),func sigaction error handling of SIGUSER1 & SIGUSER2;
/// @param  void
/// @return void. Programm end with infinite loop and pause() 
// This ensures that program keeps waiting for signals indefinitely;

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &sig_handler_rcv;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (write(2, "Error handling SIGUSR1\n", 24), EXIT_FAILURE);
	else if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(2, "Error handling SIGUSR2\n", 24), EXIT_FAILURE);
	write(1, Y, ft_strlen(Y));
	write(1, "\nServer_PID: ", 13);
	write(1, X, ft_strlen(X));
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}