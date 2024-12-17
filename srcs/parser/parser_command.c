/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:21:26 by lcluzan           #+#    #+#             */
/*   Updated: 2024/12/17 15:31:11 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*create_new_command(t_command *command_list)
{
	t_command	*new_command;
	t_command	*tmp;

	new_command = init_command();
	if (!new_command)
		return (NULL);
	if (!command_list)
		return (new_command);
	tmp = command_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_command;
	return (new_command);
}

int	add_redir_to_command(t_command *command, t_redir *new_redir, t_token *token)
{
	t_redir	*tmp;

	if (token->next && token->next->type == WORD || token->next->type == STRING)
	{
		new_redir->filename = ft_strdup(token->next->literal);
		if (!new_redir->filename)
			return (0);
	}
	else
	{
		tmp = command->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
	return (1);
}
