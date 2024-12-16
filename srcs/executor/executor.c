/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:18:17 by gozon             #+#    #+#             */
/*   Updated: 2024/12/16 14:13:47 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_builtin(t_command *command, t_data *data)
{
	int	error_code;

	error_code = 0;
	if (command->builtin == 6)
	{
		command->exit_code = mini_exit(command, data);
		error_code = -2;
	}
	else
	{
		command->exit_code = data->builtin[command->builtin](command, data);
		if (command->exit_code < 0)
			error_code = -1;
	}
	if (error_code != -1)
		data->exit_code = command->exit_code;
	return (error_code);
}

int	fork_and_execute(t_command *cmdlist, t_data *data)
{
	t_command	*cmd;
	int			error_code;

	cmd = cmdlist;
	error_code = 0;
	while (cmd)
	{
		if (!cmd->exit_code)
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				execute_command(cmd, data);
			if (cmd->pid > 0)
				close_cmd_files(cmd);
			if (cmd->pid < 0)
			{
				close_all_files(cmd);
				error_code = -1;
			}
		}
		close_all_files(cmd);
		cmd = cmd->next;
	}
	error_code = wait_for_children(cmdlist, data, error_code);
	return (error_code);
}

int	executor(t_command *cmdlist, t_data *data)
{
	int	error_code;

	if (setup_files(cmdlist))
		return (-1);
	if (command_lookup(cmdlist, data))
		return (-1);
	if (!cmdlist->next && cmdlist->builtin >= 0)
		error_code = handle_builtin(cmdlist, data);
	else
	{
		error_code = fork_and_execute(cmdlist, data);
	}
	return (error_code);
}
