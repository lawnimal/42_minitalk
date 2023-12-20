/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavina <msavina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:02:46 by msavina           #+#    #+#             */
/*   Updated: 2023/12/20 21:03:41 by msavina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define Y "\033[33m"
# define R "\033[31m"
# define G "\033[32m"
# define X "\033[0m"

int		ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *s);
void	ft_kill(int pid, char*str);
void	sig_handler_rcv(int sig_num, siginfo_t *info, void *context);
void	sig_handler_snd(int sig_num);
void	ft_lstprint(t_list *lst);

#endif