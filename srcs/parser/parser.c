/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:18:06 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/08 14:20:44 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_separator_type(t_token *token)
{
	if (token->type != WORD && token->type != STRING)
		return (1);
	return (0);
}

char	*separator_literal(t_token *token)
{
	char	*literal;

	if (!token)
		literal = ft_strdup("newline");
	else if (token->type == INFILE)
		literal = ft_strdup("<");
	else if (token->type == HERE_DOC)
		literal = ft_strdup("<<");
	else if (token->type == PIPE)
		literal = ft_strdup("|");
	else if (token->type == OUTFILE)
		literal = ft_strdup(">");
	else
		literal = ft_strdup(">>");
	if (!literal)
		perror("minishell");
	return (literal);
}

int	unexpected_token(t_token *token)
{
	char	*token_literal;

	if (is_separator_type(token)
		&& (token->next == NULL || is_separator_type(token->next)))
	{
		token_literal = separator_literal(token->next);
		if (!token_literal)
			return (1);
		ft_printf("minishell: syntax error near unexpected token `%s'\n",
			token_literal);
		free(token_literal);
		return (1);
	}
	return (0);
}

int	process_token(t_command **current, t_token **token, int *exit_code)
{
	if (unexpected_token(*token))
	{
		*exit_code = 2;
		return (clear_command_list(*current), 0);
	}
	if ((*token)->type == PIPE)
	{
		if (!handle_pipe(current))
			return (clear_command_list(*current), 0);
	}
	else if ((*token)->type == INFILE || (*token)->type == HERE_DOC
		|| (*token)->type == OUTFILE || (*token)->type == APPEND)
	{
		if (!handle_redirection(*current, token))
			return (clear_command_list(*current), 0);
	}
	else if ((*token)->type == WORD || (*token)->type == STRING)
		add_arg(*current, (*token)->literal);
	return (1);
}

t_command	*parser(t_token *tokens, int *exit_code)
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
		if (!process_token(&current, &token, exit_code))
			return (NULL);
		token = token->next;
	}
	return (cmd_list);
}
