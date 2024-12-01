/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_str_literal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:49:04 by nouillebobb       #+#    #+#             */
/*   Updated: 2024/12/01 23:00:44 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static char	*remove_quotes(char *str)
// {
// 	int		len;
// 	char	*new_str;

// 	if (!str || str[0] == '\0')
// 		return (NULL);
// 	len = ft_strlen(str);
// 	if (len < 2)
// 		return (str);
// 	if ((str[0] == '\'' || str[0] == '"') && str[0] == str[len - 1])
// 	{
// 		new_str = ft_substr(str, 1, len - 2);
// 		free(str);
// 		return (new_str);
// 	}
// 	return (str);
// }

int	get_str_len(char *input)
{
	int	i;
	int	quote_end;

	i = 1;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '<' || input[i] == '>' 
			|| input[i] == '|')
			return (i);
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote_end = find_closing_quote(input, i, input[i]);
			if (quote_end >= 0)
				return (quote_end + 1);
		}
		i++;
	}
	return (i);
}

void	update_str_literal(t_token *token, char *input)
{
	char	*str_literal;
	int		len;

	len = get_str_len(input);
	str_literal = space_strdup(input, ' ');
	if (str_literal)
		token->literal = str_literal;
}
