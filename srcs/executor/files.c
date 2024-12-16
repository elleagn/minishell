/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:14:12 by gozon             #+#    #+#             */
/*   Updated: 2024/12/16 09:03:37 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	open_redirections(t_command *command)
{
	t_redir	*redir;

	redir = command->redirs;
	while (redir)
	{
		if (redir->type == LESS || redir->type == LESSLESS)
			redir->fd = open(redir->filename, O_RDONLY);
		if (redir->type == GREATER)
			redir->fd = open(redir->filename,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (redir->type == GREATERGREATER)
			redir->fd = open(redir->filename,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (redir->fd == -1)
			perror("minishell");
		if (redir->type == LESSLESS)
			unlink(redir->filename);
		if (redir->fd == -1)
		{
			command->exit_code = 1;
			break ;
		}
	}
}

int	setup_pipes(t_command *command)
{
	int	fd[2];

	if (!command->next)
		return (0);
	if (pipe(fd))
		return (perror("minishell"), -1);
	command->pipe[1] = fd[1];
	command->next->pipe[0] = fd[0];
	return (0);
}

void	close_cmd_files(t_command *command)
{
	t_redir	*redir;

	if (command->pipe[0] > 2)
		close(command->pipe[0]);
	if (command->pipe[1] > 2)
		close(command->pipe[1]);
	redir = command->redirs;
	while (redir)
	{
		if (redir->fd > 2)
			close(redir->fd);
		redir = redir->next;
	}
}

void	close_all_files(t_command *command_list)
{
	t_command	*command;

	command = command_list;
	while (command)
	{
		close_cmd_files(command);
		command = command->next;
	}
}

int	setup_files(t_command *command_list)
{
	t_command	*command;

	command = command_list;
	while (command)
	{
		open_redirections(command);
		if (setup_pipes(command))
			return (close_all_files(command_list), -1);
		command = command->next;
	}
	return (0);
}
