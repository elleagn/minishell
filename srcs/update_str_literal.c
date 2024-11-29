/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_str_literal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:49:04 by nouillebobb       #+#    #+#             */
/*   Updated: 2024/11/29 11:09:31 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*remove_quotes(char *str)
{
	int		len;
	char	*new_str;

	if (!str || str[0] == '\0')
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (str);
	if ((str[0] == '\'' || str[0] == '"') && str[0] == str[len - 1])
	{
		new_str = ft_substr(str, 1, len - 2);
		free(str);
		return (new_str);
	}
	return (str);
}

void	update_str_literal(t_token *token, char *input)
{
	int		start;
	int		end;
	char	quote_type;
	char	*tmp;

	if (!token || !input || !token->literal)
		return ;
	start = 0;
	quote_type = token->literal[start];
	if (quote_type == '\'' || quote_type == '"')
	{
		end = find_closing_quote(input, start, quote_type);
		if (end != -1)
		{
			tmp = ft_strdup(token->literal);
			free(token->literal);
			token->literal = remove_quotes(tmp);
		}
	}
}
