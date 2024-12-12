/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:10:30 by gozon             #+#    #+#             */
/*   Updated: 2024/12/10 08:21:03 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_env(char **env, int fd)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		if (write(fd, env[i], ft_strlen(env[i])) < 0)
			return (perror("minishell"), 1);
		if (write(fd, "\n", 1) < 0)
			return (perror("minishell"), 1);
		i++;
	}
	return (0);
}

int	mini_env(t_command *command, t_data *data)
{
	int	out_fd;

	if (!command || !command->av || !command->av[0])
		return (1);
	if (command->av[1])
	{
		write(2, "minishell: env: too many arguments\n", 36);
		return (1);
	}
	out_fd = find_out_fd(command);
	if (out_fd < 0)
		return (1);
	if (print_env(data->env, out_fd))
		return (1);
	return (0);
}
