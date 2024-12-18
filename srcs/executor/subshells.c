/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:07:06 by gozon             #+#    #+#             */
/*   Updated: 2024/12/18 11:41:02 by gozon            ###   ########.fr       */
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

void	replace_stds(t_command *command, t_data *data)
{
	int	in;
	int	out;

	out = find_out_fd(command);
	in = find_in_fd(command);
	if (in != 0 && dup2(in, 0) < 0)
	{
		perror("minishell");
		close_all_files(command);
		full_cleanup(command, data);
		exit(EXIT_FAILURE);
	}
	if (out != 1 && dup2(out, 1) < 0)
	{
		perror("minishell");
		close_all_files(command);
		full_cleanup(command, data);
		exit(EXIT_FAILURE);
	}
}

void	execute_command(t_command *command, t_data *data)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (command->builtin >= 0)
	{
		status = data->builtin[command->builtin](command, data);
		close_all_files(command);
		full_cleanup(command, data);
		exit(status);
	}
	replace_stds(command, data);
	close_all_files(command);
	execve(*(command->av), command->av, data->env);
	perror("minishell");
	full_cleanup(command, data);
	exit(EXIT_FAILURE);
}

void	handle_last_command(t_command *command, t_data *data)
{
	data->exit_code = command->exit_code;
	if (command->exit_code == 131)
	{
		if (write(1, "Quit (core dumped)\n", 20))
		{
			perror("minishell");
			critical_exit(command, data);
		}
	}
	if (command->exit_code == 130)
	{
		if (write(1, "\n", 1))
		{
			perror("minishell");
			critical_exit(command, data);
		}
	}
}

void	wait_for_children(t_command *cmd, t_data *data)
{
	int			status;

	while (cmd)
	{
		if (!cmd->exit_code)
		{
			if (waitpid(cmd->pid, &status, 0) == -1)
				wait_and_exit(cmd, data);
			if (WIFEXITED(status))
				cmd->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				cmd->exit_code = 128 + WTERMSIG(status);
			cmd->pid = -1;
		}
		if (cmd->exit_code == -1)
			wait_and_exit(cmd, data);
		if (!cmd->next)
		{
			data->exit_code = cmd->exit_code;
			if (cmd->exit_code == 131)
				write(1, "Quit (core dumped)\n", 20);
		}
		cmd = cmd->next;
	}
}
