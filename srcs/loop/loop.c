/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 07:02:36 by gozon             #+#    #+#             */
/*   Updated: 2025/01/13 08:40:39 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*process_line(char *input, t_data *data)
{
	t_token		*tokens;
	t_command	*commands;

	tokens = lexer(input);
	if (!tokens)
		return (NULL);
	if (expander(&tokens, data))
		return (clear_token_list(&tokens), NULL);
	commands = parser(tokens, data);
	clear_token_list(&tokens);
	return (commands);
}

int	process_and_execute(char *input, t_data *data)
{
	t_command	*command;

	add_history(input);
	command = process_line(input, data);
	free(input);
	if (!command)
	{
		if (data->exit_code != -1)
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
	int			init_readline;

	init_readline = 0;
	while (1)
	{
		input = readline("minishell$ ");
		data->line += 1;
		if (!g_flag && !input)
			break ;
		data->exit_code = check_signal(data, &init_readline);
		if (data->exit_code == -1)
		{
			data->exit_code = 1;
			break ;
		}
		if (input && process_and_execute(input, data))
			break ;
	}
	rl_clear_history();
	return (data->exit_code);
}
