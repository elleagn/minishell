/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:18:17 by gozon             #+#    #+#             */
/*   Updated: 2025/01/10 15:10:05 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_builtin(t_command *command, t_data *data)
{
	command->exit_code = data->builtin[command->builtin](command, data);
	if (command->exit_code < 0)
		critical_exit(command, data);
	data->exit_code = command->exit_code;
}

void	wait_and_exit(t_command *cmdlist, t_data *data)
{
	t_command	*command;
	int			status;

	command = cmdlist;
	while (command->previous)
		command = command->previous;
	while (command)
	{
		if (command->pid > 0)
			waitpid(command->pid, &status, 0);
		command = command->next;
	}
	full_cleanup(cmdlist, data);
	exit(EXIT_FAILURE);
}

void	fork_and_execute(t_command *cmdlist, t_data *data)
{
	t_command	*cmd;

	cmd = cmdlist;
	while (cmd)
	{
		if (!cmd->exit_code && cmd->av)
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				execute_command(cmd, data);
			if (cmd->pid < 0)
			{
				close_all_files(cmd);
				wait_and_exit(cmdlist, data);
			}
		}
		close_cmd_files(cmd);
		cmd = cmd->next;
	}
	wait_for_children(cmdlist, data);
}

void	executor(t_command *cmdlist, t_data *data)
{
	if (setup_files(cmdlist))
		critical_exit(cmdlist, data);
	command_lookup(cmdlist, data);
	if (!cmdlist->next && cmdlist->builtin >= 0)
		handle_builtin(cmdlist, data);
	else
		fork_and_execute(cmdlist, data);
}
