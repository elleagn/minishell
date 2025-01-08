/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 07:02:36 by gozon             #+#    #+#             */
/*   Updated: 2025/01/08 12:15:45 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*parse_and_expand(t_token *tokens, t_data *data)
{
	t_command	*commands;

	commands = parser(tokens, &(data->exit_code));
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

int	process_and_execute(char *input, t_data *data)
{
	t_command	*command;

	add_history(input);
	command = process_line(input, data);
	free(input);
	if (!command)
	{
		if (data->exit_code == 2)
			return (0);
		data->exit_code = 1;
		return (1);
	}
	executor(command, data);
	clear_command_list(command);
	return (0);
}

int	mini_loop(t_data *data)
{
	char		*input;

	while (1)
	{
		input = readline("minishell $ ");
		if (!input)
			break ;
		if (process_and_execute(input, data))
			break ;
	}
	rl_clear_history();
	return (data->exit_code);
}
