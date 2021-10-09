/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:38:30 by echerell          #+#    #+#             */
/*   Updated: 2021/10/09 18:58:43 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error(int err)
{
	if (err == 0)
		ft_putstr_fd("Wrong format. format: <server_pid> <message>\n", 1);
	else if (err == 1)
		ft_putstr_fd("Wrong server pid\n", STDOUT_FILENO);
	else if (err == 2)
		ft_putstr_fd("Signal cannot reach the server\n", STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	received(int signum)
{
	(void)signum;
	ft_putstr_fd("SUCCESSFULLY RECEIVED!", STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	send_msg(int pid, unsigned char c)
{
	int	bit_shift;

	bit_shift = 8;
	while (bit_shift--)
	{
		if (c & 1 << bit_shift)
		{
			if (kill(pid, SIGUSR1) == -1)
				error(SIGNAL_ERR);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error(SIGNAL_ERR);
		}
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	server_pid;

	if (argc != 3)
		error(FORMAT_ERR);
	i = 0;
	server_pid = ft_atoi(argv[1]);
	if (server_pid == 0 || server_pid == -1)
		error(PID_ERR);
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
