/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:38:30 by echerell          #+#    #+#             */
/*   Updated: 2021/10/08 01:07:28 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	received(int signum)
{
	(void)signum;
	ft_putstr_fd("SUCCESSFULLY RECEIVED!", STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	send_msg(int pid, int c)
{
	int	bit_shift;

	bit_shift = 8;
	while (bit_shift--)
	{
		if (c & 1 << bit_shift)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	server_pid;

	if (argc != 3)
		exit(EXIT_FAILURE);
	i = 0;
	server_pid = ft_atoi(argv[1]);
	signal(SIGUSR2, received);
	while (argv[2][i])
	{
		send_msg(server_pid, argv[2][i]);
		i++;
	}
	send_msg(server_pid, 0);
	while (1)
		pause();
	return (0);
}
