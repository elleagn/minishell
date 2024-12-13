/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:24:42 by lcluzan           #+#    #+#             */
/*   Updated: 2024/12/13 15:06:49 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pipe_error(t_data *data, t_command *command)
{
	if (command->input_fd != 0)
		close(command->input_fd);
	if (command->output_fd != 1)
		close(command->output_fd);
	data->exit_code = 1;
}

static void	pipe_fork(t_data *data, t_command *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (command->input_fd != 0)
		{
			dup2(command->input_fd, 0);
			close(command->input_fd);
		}
		if (command->output_fd != 1)
		{
			dup2(command->output_fd, 1);
			close(command->output_fd);
		}
		if (command_lookup(command, data) == -1)
			exit(1);
		exit(0);
	}
	else if (pid < 0)
		pipe_error(data, command);
	else
	{
		waitpid(pid, &command->status, 0);
		if (command->input_fd != 0)
			close(command->input_fd);
		if (command->output_fd != 1)
			close(command->output_fd);
	}
}

int	parse_pipe(t_data *data, t_shell *shell)
{
	t_command	*command;

	command = data->commands;
	while (command)
	{
		if (command->next)
		{
			if (pipe(command->pipe) == -1)
			{
				pipe_error(data, command);
				return (-1);
			}
			command->output_fd = command->pipe[1];
			command->next->input_fd = command->pipe[0];
		}
		pipe_fork(data, command);
		command = command->next;
	}
	return (0);
}
