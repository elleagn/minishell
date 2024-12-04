/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:43:58 by lcluzan           #+#    #+#             */
/*   Updated: 2024/12/02 13:33:37 by gozon            ###   ########.fr       */
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

int	is_separator(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	is_string(char *input)
{
	int	i;

	i = 0;
	while (input[i] && !is_separator(input[i]))
	{
		if (input[i] == '\'' && find_closing_quote(input, i, '\'') >= 0)
			return (1);
		if (input[i] == '\"' && find_closing_quote(input, i, '\"') >= 0)
			return (1);
		i++;
	}
	return (0);
}

/* update the token type */
void	update_token_type(t_token *token, char *input)
{
	if (!token || !input)
		return ;
	if (ft_strncmp(input, "<<", 2) == 0)
		token->type = LESSLESS;
	else if (ft_strncmp(input, "<", 1) == 0)
		token->type = LESS;
	else if (ft_strncmp(input, ">>", 2) == 0)
		token->type = GREATERGREATER;
	else if (ft_strncmp(input, ">", 1) == 0)
		token->type = GREATER;
	else if (ft_strncmp(input, "|", 1) == 0)
		token->type = PIPE;
	else if (is_string(input))
		token->type = STRING;
	else
		token->type = WORD;
}

// find_closing_quote

// int	main(void)
// {
// 	char	str[] = "";

// 	printf("%i\n", find_closing_quote(str, 0, '\''));
// 	return (0);
// }

// update_token_type

// int	main(void)
// {
// 	t_token	*token;
// 	char	*input = "'xsusj\"'";

// 	token = init_token();
// 	if (!token)
// 		return (1);
// 	update_token_type(token, input);
// 	if (token->type == STRING_SIMPLE)
// 		printf("OK\n");
// 	else
// 		printf("KO");
// 	clear_token(token);
// 	return (0);
// }
