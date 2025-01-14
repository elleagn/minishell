/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:06:58 by gozon             #+#    #+#             */
/*   Updated: 2025/01/14 10:40:41 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	normal_exit(t_command *command, t_data *data, int exit_code)
{
	close_all_files(command);
	full_cleanup(command, data);
	exit(exit_code);
}

int	is_numeric(char *str)
{
	int	i;
	int	is_not_zero;

	i = 0;
	if (str[i] == '-' && ft_isdigit(str[i + 1]))
		i = 1;
	is_not_zero = 0;
	while (str[i])
	{
		if (str[i] != '0')
			is_not_zero = 1;
		i++;
	}
	if (!ft_atoi(str) && is_not_zero)
		return (0);
	return (1);
}

void	write_non_numeric(char *str)
{
	char	*message;

	message = strjoin_three("minishell: exit: ",
			str, ": numeric argument required\n");
	if (!message)
	{
		perror("minishell");
		return ;
	}
	if (write(2, message, ft_strlen(message)) < 0)
		perror("minishell");
	free(message);
}

int	mini_exit(t_command *command, t_data *data)
{
	int	exit_code;

	exit_code = data->exit_code;
	if (command->pid == -1)
	{
		if (write(1, "exit\n", 6) < 0)
			return (perror("minishell"), -1);
	}
	if (!command->av[1])
		normal_exit(command, data, exit_code);
	if (!is_numeric(command->av[1]))
	{
		write_non_numeric(command->av[1]);
		normal_exit(command, data, 2);
	}
	if (command->av[2])
	{
		if (write(2, "minishell: exit: too many arguments\n", 37) < 0)
			return (perror("minishell"), -1);
		return (1);
	}
	normal_exit(command, data, ft_atoi(command->av[1]));
	return (-1);
}
