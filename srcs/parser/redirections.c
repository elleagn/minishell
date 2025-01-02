/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:20:47 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/02 15:22:39 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir	*init_redir(t_type type, t_token *filename)
{
	t_redir	*redir;

	if (!type || !filename)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename->literal);
	redir->backup = ft_strdup(filename->literal); // Store original for error messages
	redir->fd = -1; // Will be set during execution
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_command *cmd, t_redir *redir)
{
	t_redir	*current;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return;
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
	redir = init_redir((*token)->type, (*token)->next);
	if (!redir)
		return (0);
	add_redir(current, redir);
	*token = (*token)->next; // Skip filename token
	return (1);
}