/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:20:47 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/08 11:12:27 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir	*init_and_fill_redir(t_type type, t_token *filename)
{
	t_redir	*redir;

	if (!type || !filename)
		return (NULL);
	redir = init_redir();
	if (!redir)
		return (NULL);
	redir->type = type;
	// insert heredoc here
	redir->filename = ft_strdup(filename->literal);
	if (!redir->filename)
		return (clear_redir(redir), NULL);
	redir->backup = ft_strdup(filename->literal);
	if (!redir->filename)
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

int	handle_redirection(t_command *current, t_token **token)
{
	t_redir	*redir;

	if (!(*token)->next)
		return (0);
	redir = init_and_fill_redir((*token)->type, (*token)->next);
	if (!redir)
		return (0);
	add_redir(current, redir);
	*token = (*token)->next;
	return (1);
}
