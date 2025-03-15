/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:31:39 by nvallin           #+#    #+#             */
/*   Updated: 2024/06/14 15:30:30 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_signal(pid_t pid, char c)
{
	int	bit;

	bit = 8;
	while (bit-- > 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(420);
	}
	return (0);
}

int	ft_isnumber(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (ft_isdigit(*str) == 0)
		return (0);
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (!ft_isnumber(argv[1]) || kill(pid, 0) != 0)
		{
			ft_printf("invalid PID\n");
			return (0);
		}
		while (argv[2][i] != '\0')
			send_signal(pid, argv[2][i++]);
		i = 8;
		while (i-- > 0)
		{
			kill(pid, SIGUSR1);
			usleep(420);
		}
	}
	else
		ft_printf("invalid input\n");
	return (0);
}
