/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 08:33:40 by gozon             #+#    #+#             */
/*   Updated: 2025/01/13 13:42:51 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_until_char(char **expanded, char *str, t_data *data, char *delim)
{
	char	*segment;
	int		end;
	char	*tmp;

	segment = delims_strdup(str, delim);
	if (!segment)
	{
		data->exit_code = -1;
		return (-1);
	}
	tmp = ft_strjoin(*expanded, segment);
	if (!tmp)
	{
		data->exit_code = 1;
		free(segment);
		return (-1);
	}
	replace_string(expanded, tmp);
	end = ft_strlen(segment);
	free(segment);
	return (end);
}

int	remove_double_quotes(char **expanded, char *str, t_data *data)
{
	int		i;

	i = 1;
	while (str[i] != '"')
	{
		if (str[i] == '$')
			i += join_var(expanded, &str[i], data);
		else
			i += add_until_char(expanded, &str[i], data, "\"$");
		if (data->exit_code == -1)
			return (-1);
	}
	return (i + 1);
}

int	no_quotes(char **expanded, char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '"' && str[i] != '\'')
	{
		if (str[i] == '$')
			i += join_var(expanded, &str[i], data);
		else
			i += add_until_char(expanded, &str[i], data, "\"$'");
		if (data->exit_code == -1)
			return (-1);
	}
	return (i);
}

void	remove_quotes_without_expand(t_token *token, t_data *data)
{
	char	*literal;
	char	*unquoted;
	int		i;

	i = 0;
	unquoted = NULL;
	literal = token->literal;
	while (literal[i])
	{
		if (literal[i] == '\'')
			i += add_until_char(&unquoted, &literal[i + 1], data, "'") + 2;
		else if (literal[i] == '"')
			i += add_until_char(&unquoted, &literal[i + 1], data, "\"") + 2;
		else
			i += add_until_char(&unquoted, &literal[i], data, "\"'");
		if (data->exit_code == -1)
			return ;
	}
	replace_string(&token->literal, unquoted);
}

t_token	*remove_quotes(t_token *token, t_data *data)
{
	int		i;
	char	*expanded;
	char	*literal;

	i = 0;
	expanded = NULL;
	literal = token->literal;
	if (token->prev && token->prev->type == HERE_DOC)
		return (remove_quotes_without_expand(token, data), token->next);
	while (literal[i])
	{
		if (literal[i] == '\'')
			i += add_until_char(&expanded, &literal[i + 1], data, "'") + 2;
		else if (literal[i] == '"')
			i += remove_double_quotes(&expanded, &literal[i], data);
		else
			i += no_quotes(&expanded, &literal[i], data);
		if (data->exit_code == -1)
			return (token->next);
	}
	replace_string(&token->literal, expanded);
	return (token->next);
}
