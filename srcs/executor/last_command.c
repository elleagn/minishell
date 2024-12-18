/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:46:03 by gozon             #+#    #+#             */
/*   Updated: 2024/12/18 12:51:46 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_underscore(t_command *command, t_data *data)
{
	int		i;
	char	*underscore;

	i = 0;
	while (command->av[i + 1])
		i++;
	underscore = ft_strjoin("_=", command->av[i]);
	if (!underscore)
	{
		perror("minishell");
		critical_exit(command, data);
	}
	if (add_var(underscore, data))
	{
		free(underscore);
		critical_exit(command, data);
	}
}

void	handle_last_command(t_command *command, t_data *data)
{
	data->exit_code = command->exit_code;
	update_underscore(command, data);
	if (command->exit_code == 131)
	{
		if (write(1, "Quit (core dumped)\n", 20) < 0)
		{
			perror("minishell");
			critical_exit(command, data);
		}
	}
	if (command->exit_code == 130)
	{
		if (write(1, "\n", 1) < 0)
		{
			perror("minishell");
			critical_exit(command, data);
		}
	}
}
