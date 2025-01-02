/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 07:02:36 by gozon             #+#    #+#             */
/*   Updated: 2025/01/02 16:05:26 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*parse_and_expand(t_token *tokens, t_data *data)
{
	t_command	*commands;

	commands = parser(tokens);
	if (!commands)
		return (NULL);
	if (!expander(commands, data))
		return (clear_command_list(commands), NULL);
	return (commands);
}

t_command	*process_line(char *input, t_data *data)
{
	t_token		*tokens;
	t_command	*command;

	tokens = lexer(input);
	if (!tokens)
		return (NULL);
	command = parse_and_expand(tokens, data);
	clear_token_list(&tokens);
	if (!command)
		return (NULL);
	return (command);
}

int	mini_loop(t_data *data)
{
	char		*input;
	t_command	*command;

	while (1)
	{
		input = readline("minishell $ ");
		if (!input)
			break ;
		command = process_line(input, data);
		free(input);
		if (!command)
		{
			data->exit_code = 1;
			break ;
		}
		executor(command, data);
		clear_command_list(command);
	}
	return (data->exit_code);
}