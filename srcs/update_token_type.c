/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:43:58 by lcluzan           #+#    #+#             */
/*   Updated: 2024/11/29 10:47:09 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* search for the closing quote */
int	find_closing_quote(char *input, int start, char quote_type)
{
	int	i;

	i = start + 1;
	while (input[i])
	{
		if (input[i] == quote_type)
			return (i);
		i++;
	}
	return (-1);
}

/* check if the token is a quote and update its type */
static void	handle_quote_token(t_token *token, char *input)
{
	char	quote_type;
	int		closing_index;

	quote_type = input[0];
	closing_index = find_closing_quote(input, 0, quote_type);
	if (closing_index != -1)
	{
		if (quote_type == '"')
			token->type = STRING_DOUBLE;
		else
			token->type = STRING_SIMPLE;
	}
}

/* update the token type */
void	update_token_type(t_token *token, char *input)
{
	if (!token || !input)
		return ;
	if (input[0] == '"' || input[0] == '\'')
	{
		handle_quote_token(token, input);
		return ;
	}
	else if (ft_strncmp(input, "<<", 2) == 0)
		token->type = LESSLESS;
	if (ft_strncmp(input, "<", 1) == 0)
		token->type = LESS;
	else if (ft_strncmp(input, ">>", 2) == 0)
		token->type = GREATERGREATER;
	else if (ft_strncmp(input, ">", 1) == 0)
		token->type = GREATER;
	else if (ft_strncmp(input, "|", 1) == 0)
		token->type = PIPE;
	else
		token->type = WORD;
}
