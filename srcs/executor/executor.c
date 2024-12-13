/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:18:17 by gozon             #+#    #+#             */
/*   Updated: 2024/12/13 11:04:47 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_subshells(t_command *cmdlist, t_data *data)
{
	t_command	*cmd;
	int			error_code;

	cmd = cmdlist;
	error_code = 0;
	while (cmd)
	{
		if (!cmd->status)
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
	if (!cmdlist->next && cmdlist->builtin)
		error_code = handle_builtin(cmdlist, data);
	else
		error_code = handle_subshells(cmdlist, data);
	return (error_code);
}
