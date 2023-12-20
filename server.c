/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavina <msavina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:34:59 by msavina           #+#    #+#             */
/*   Updated: 2023/12/20 17:18:04 by msavina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		ft_putchar_fd(*(char *)lst->content, 1);
		lst = lst->next;
	}
}

/// @brief handler function of received signal. Called when server receives
// SIGUSER1 or SIGUSER2 signal from client;
/// @param sig_num signal number received (SIGUSR1 or SIGUSER2);
/// @param info ptr, provides PID in a member (si_pid) of the struct siginfo_t;
/// @param context ptr to execution context (register state, stack info, etc);

void	sig_handler_rcv(int sig_num, siginfo_t *info, void *context)
{
	static int				i;
	static unsigned char	c;
	static t_list			*list;
	char					*pc;

	(void)info;
	(void)context;
	c <<= 1;
	c |= (sig_num == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (c == '\0')
		{
			ft_lstprint(list);
			write(1, "\n", 1);
			ft_lstclear(&list, &free);
			c = 0;
			return ;
		}
		pc = malloc(1 * sizeof(char));
		if (pc == NULL)
		{
			ft_lstclear(&list, &free);
			exit(1);
		}
		*pc = c;
		ft_lstadd_back(&list, ft_lstnew(pc));
		c = 0;
	}
}

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
	write(1, "Server_PID: ", 12);
	write(1, X, ft_strlen(X));
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
