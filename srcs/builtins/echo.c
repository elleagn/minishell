/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:33:23 by gozon             #+#    #+#             */
/*   Updated: 2024/12/07 17:01:41 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_args(char **args, int n_opt, int fd)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (write(fd, args[i], ft_strlen(args[i])) < 0)
			return (1);
		i++;
		if (args[i])
		{
			if (write(fd, " ", 1) < 0)
				return (1);
		}
	}
	if (!n_opt)
	{
		if (write(fd, "\n", 1) < 0)
			return (1);
	}
	return (0);
}

int	find_out_fd(t_command *command)
{
	t_redir	*redirs;
	int		out_fd;

	if (!command)
		return (-1);
	redirs = command->redirs;
	out_fd = command->pipe[1];
	while (redirs)
	{
		if (redirs->type == GREATER || redirs->type == GREATERGREATER)
			out_fd = redirs->fd;
		redirs = redirs->next;
	}
	return (out_fd);
}

int	mini_echo(t_command *command, t_data *data)
{
	int	n_opt;
	int	out_fd;

	(void)	*data;
	n_opt = 0;
	if (!command || !command->av[0])
		return (1);
	out_fd = find_out_fd(command);
	if (out_fd < 0)
		return (1);
	if (!ft_strncmp(command->av[1], "-n", 3))
		n_opt = 1;
	if (print_args(&command->av[1 + n_opt], n_opt, out_fd))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac)
		return (mini_echo(&av[1], NULL));
}
