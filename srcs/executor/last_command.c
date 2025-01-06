/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:46:03 by gozon             #+#    #+#             */
/*   Updated: 2024/12/19 12:38:06 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_last_command(t_command *command, t_data *data)
{
	data->exit_code = command->exit_code;
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
