/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:13:53 by lcluzan           #+#    #+#             */
/*   Updated: 2024/12/13 14:53:57 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_heredoc(t_command *command, t_data *data)
{
	t_redir	*redir;
	t_token	*token;

	redir = init_redir();
	redir->type = HEREDOC; // HEREDOC is not defined in the enum t_type + HEREDOC is not used in the struct s_redir = find a way to fix this
	redir->filename = ft_strdup("heredoc");
	redir->fd = -1;
	token = data->lexer_list;
	while (token && token->type != LESSLESS)
		token = token->next;
	token = token->next;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			if (redir->fd == -1)
				redir->fd = open(redir->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
			write(redir->fd, token->literal, ft_strlen(token->literal));
			write(redir->fd, "\n", 1);
		}
		token = token->next;
	}
	if (redir->fd != -1)
		close(redir->fd);
	add_redir_to_list(&command->redirs, redir);
}

static char	*get_heredoc_filename(t_data *data)
{
	t_token	*token;

	token = data->lexer_list;
	while (token && token->type != LESSLESS)
		token = token->next;
	token = token->next;
	if (token && token->type == WORD)
		return (ft_strdup(token->literal));
	return (NULL);
}

void	parse_heredoc(t_data *data)
{
	t_command	*command;
	t_redir		*redir;
	char		*filename;

	command = data->command_list;
	while (command)
	{
		redir = command->redirs;
		while (redir)
		{
			if (redir->type == LESSLESS)
			{
				filename = get_heredoc_filename(data);
				if (filename)
				{
					redir->filename = filename;
					get_heredoc(command, data);
				}
			}
			redir = redir->next;
		}
		command = command->next;
	}
}
