/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:34:16 by lcluzan           #+#    #+#             */
/*   Updated: 2024/12/17 17:14:20 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_command	*init_command_list(t_command *command_list)
{
	t_command	*current_command;

	current_command = create_new_command(command_list);
	if (!current_command)
		return (clear_command_list(command_list), NULL);
	return (current_command);
}

static t_command	*handle_token(t_token *current_token,
						t_command *current_command, t_command *command_list)
{
	t_redir		*new_redir;

	if (current_token->type == WORD || current_token->type == STRING)
	{
		if (!add_arg_to_command(*current_command, current_token->literal))
			return (clear_command_list(command_list), NULL);
	}
	else if (current_token->type >= LESS && current_token->type
		<= GREATERGREATER)
	{
		new_redir = create_redir(current_token);
		if (!new_redir || !add_redir_to_command(*current_command,
				new_redir, current_token))
			return (clear_command_list(command_list), NULL);
		current_token = current_token->next;
	}
	else if (current_token->type == PIPE)
	{
		current_command = init_command_list(command_list);
		if (!current_command)
			return (clear_command_list(command_list), NULL);
	}
	return (current_command);
}

t_command	*parse_tokens(t_token *token_list)
{
	t_command	*command_list;
	t_command	*current_command;
	t_token		*current_token;

	command_list = init_command_list(NULL);
	if (!command_list)
		return (NULL);
	current_command = command_list;
	current_token = token_list;
	while (current_token)
	{
		current_command = handle_token(current_token, current_command,
				command_list);
		if (!current_command)
			return (NULL);
		current_token = current_token->next;
	}
	return (command_list);
}
