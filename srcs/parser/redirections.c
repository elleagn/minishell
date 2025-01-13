/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:20:47 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/13 14:44:24 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_filename(t_redir *redir, t_data *data, t_token *filename)
{
	if (redir->type == HERE_DOC)
	{
		redir->filename = here_doc(filename, data);
		if (!redir->filename)
			return (1);
	}
	else
	{
		redir->filename = ft_strdup(filename->literal);
		if (!redir->filename && filename->literal)
		{
			perror("minishell");
			data->exit_code = -1;
		}
	}
	return (0);
}

t_redir	*init_and_fill_redir(t_type type, t_token *filename, t_data *data)
{
	t_redir	*redir;

	if (!type || !filename)
		return (NULL);
	redir = init_redir();
	if (!redir)
		return (NULL);
	redir->type = type;
	if (add_filename(redir, data, filename))
		return (clear_redir_list(redir), NULL);
	redir->backup = ft_strdup(filename->backup);
	if (!redir->filename && filename->literal)
		return (perror("minishell"), clear_redir(redir), NULL);
	return (redir);
}

void	add_redir(t_command *cmd, t_redir *redir)
{
	t_redir	*current;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	current = cmd->redirs;
	while (current->next)
		current = current->next;
	current->next = redir;
}

int	handle_redirection(t_command *current, t_token **token, t_data *data)
{
	t_redir	*redir;

	if (!(*token)->next)
		return (0);
	redir = init_and_fill_redir((*token)->type, (*token)->next, data);
	if (!redir)
		return (0);
	add_redir(current, redir);
	*token = (*token)->next;
	return (1);
}
