/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:18:06 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/02 15:20:08 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	process_token(t_command **current, t_token **token, t_command *cmd_list)
{
	if ((*token)->type == PIPE)
	{
		if (!handle_pipe(current))
			return (clear_command_list(cmd_list), 0);
	}
	else if ((*token)->type == LESS || (*token)->type == LESSLESS ||
			(*token)->type == GREATER || (*token)->type == GREATERGREATER)
	{
		if (!handle_redirection(*current, token))
			return (clear_command_list(cmd_list), 0);
	}
	else if ((*token)->type == WORD || (*token)->type == STRING)
		add_arg(*current, (*token)->literal);
	return (1);
}

t_command	*parser(t_token *tokens)
{
	t_command	*cmd_list;
	t_command	*current;
	t_token		*token;

	if (!tokens)
		return (NULL);
	cmd_list = init_command();
	if (!cmd_list)
		return (NULL);
	current = cmd_list;
	token = tokens;
	while (token)
	{
		if (!process_token(&current, &token, cmd_list))
			return (NULL);
		token = token->next;
	}
	return (cmd_list);
}