/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 07:02:36 by gozon             #+#    #+#             */
/*   Updated: 2024/12/23 07:40:23 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*process_line(char *input, t_data *data)
{
	t_token		*tokens;
	t_command	*command;

	tokens = lexer(input);
	if (!tokens)
		return (NULL);
	command = parse_and_expand(tokens, data);
	clear_token_list(tokens);
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
