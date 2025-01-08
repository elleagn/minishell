/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 07:02:36 by gozon             #+#    #+#             */
/*   Updated: 2025/01/08 17:05:51 by gozon            ###   ########.fr       */
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
		if (data->exit_code == 2 || data->exit_code == 130)
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
	int			signal;
	int			init_readline;

	init_readline = 0;
	while (1)
	{
		input = readline("minishell $ ");
		signal = check_signal(data->stdin_fd, input, &init_readline);
		if (signal == -1)
		{
			data->exit_code = 1;
			break ;
		}
		if (!signal && !input)
			break ;
		if (!signal && process_and_execute(input, data))
			break ;
	}
	rl_clear_history();
	return (data->exit_code);
}
