/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:06:58 by gozon             #+#    #+#             */
/*   Updated: 2024/12/14 10:28:00 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	mini_exit(t_command *command, t_data *data)
{
	if (command->pid == -1)
	{
		if (write(1, "exit\n", 6) < 0)
			return (perror("minishell"), -1);
	}
	if (!command->av[1])
		return (data->exit_code);
	if (!is_numeric(command->av[1]))
	{
		if (write(2, "minishell: exit: numeric argument required\n", 44) < 0)
			return (perror("minishell"), -1);
		return (2);
	}
	if (command->av[2])
	{
		if (write(2, "minishell: exit: too many arguments\n", 37) < 0)
			return (perror("minishell"), -1);
		return (1);
	}
	return (ft_atoi(command->av[1]));
}
