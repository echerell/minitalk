/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:53:41 by echerell          #+#    #+#             */
/*   Updated: 2021/10/10 16:41:20 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlen(const char *s)
{
	size_t	n;

	if (!s)
		return (0);
	n = 0;
	while (s[n])
		n++;
	return (n);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

int	ft_atoi(const char *nptr)
{
	int		i;
	long	n;
	long	sign;

	sign = 1;
	n = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + (nptr[i++] - '0');
		if (n < 0 && (sign == -1 || sign == 1))
			return (0);
	}
	if ((nptr[i] < '0' || nptr[i] > '9') && nptr[i])
		return (0);
	return ((int)(n * sign));
}

void	error(int err)
{
	if (err == FORMAT_ERR)
		ft_putstr_fd("Wrong format. format: <server_pid> <message>\n", 1);
	else if (err == PID_ERR)
		ft_putstr_fd("Wrong server pid\n", STDOUT_FILENO);
	else if (err == SIGNAL_ERR)
		ft_putstr_fd("Signal cannot reach the server\n", STDOUT_FILENO);
	else if (err == EMPTY_ERR)
		ft_putstr_fd("Client should send at least one symbol\n", 1);
	else if (err == SERVER_ERR)
		ft_putstr_fd("Server runs without any arguments\n", STDOUT_FILENO);
	exit(EXIT_FAILURE);
}
