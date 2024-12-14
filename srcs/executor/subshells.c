/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:07:06 by gozon             #+#    #+#             */
/*   Updated: 2024/12/14 10:35:28 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_in_fd(t_command *command)
{
	t_redir	*redirs;
	int		in_fd;

	if (!command)
		return (-1);
	redirs = command->redirs;
	in_fd = command->pipe[0];
	while (redirs)
	{
		if (redirs->type == LESS || redirs->type == LESSLESS)
			in_fd = redirs->fd;
		redirs = redirs->next;
	}
	return (in_fd);
}

void	execute_command(t_command *command, t_data *data)
{
	int	in;
	int	out;
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (command->builtin >= 0)
	{
		status = data->builtin[command->builtin](command, data);
		close_all_files(command);
		exit(status);
	}
	out = find_out_fd(command);
	in = find_in_fd(command);
	if (dup2(in, 0) || dup2(out, 1))
	{
		close_all_files(command);
		exit(EXIT_FAILURE);
	}
	close_all_files(command);
	execve(*(command->av), command->av, data->env);
	exit(EXIT_FAILURE);
}

int	wait_for_children(t_command *cmd, t_data *data, int error_code)
{
	int	status;

	while (cmd)
	{
		if (!cmd->exit_code)
		{
			if (waitpid(cmd->pid, &status, 0) == -1)
				return (-1);
			if (WIFEXITED(status))
				cmd->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				cmd->exit_code = 128 + WTERMSIG(status);
		}
		if (!cmd->next)
			data->exit_code = cmd->exit_code;
	}
	if (error_code)
		return (error_code);
	return (0);
}
