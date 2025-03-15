/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:26:10 by nvallin           #+#    #+#             */
/*   Updated: 2024/06/24 15:13:27 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_add_size(char *str, size_t *buffer)
{
	char	*new;
	int		i;

	i = 0;
	*buffer = *buffer * 2;
	new = malloc((sizeof(char) * *buffer));
	if (!new)
	{
		ft_putstr_fd("malloc fail\n", 2);
		free(str);
		exit (0);
	}
	ft_bzero(new, *buffer);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	str = NULL;
	return (new);
}

char	*ft_init_str(char *str, size_t len)
{
	str = malloc(sizeof(char) * len);
	if (!str)
	{
		ft_putstr_fd("malloc fail\n", 2);
		exit (0);
	}
	ft_bzero(str, len);
	return (str);
}

char	*ft_print_and_reset(char *str, size_t *bytes, size_t *buffer)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		write(1, &str[i++], 1);
	write(1, "\n", 1);
	free(str);
	str = NULL;
	*bytes = 0;
	*buffer = 5;
	return (str);
}

void	ft_sigusr_handler(int signal)
{
	static int		bit = 0;
	static size_t	buffer = 5;
	static size_t	bytes = 0;
	static char		c = 0;
	static char		*str = NULL;

	if (!str)
		str = ft_init_str(str, buffer);
	if (signal == SIGUSR1)
		c = c << 1;
	if (signal == SIGUSR2)
		c = (c << 1) | 1;
	if (++bit > 7)
	{
		if (++bytes >= buffer - 1)
			str = ft_add_size(str, &buffer);
		if (c == 0)
			str = ft_print_and_reset(str, &bytes, &buffer);
		else
			str[ft_strlen(str)] = c;
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	act;

	pid = getpid();
	act.sa_handler = ft_sigusr_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_printf("%d\n", pid);
	while (1)
		pause();
	return (0);
}
