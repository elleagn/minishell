/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:58:12 by gozon             #+#    #+#             */
/*   Updated: 2024/12/10 08:13:21 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	delim_strlen(const char *str, char delimiter)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != delimiter)
		i++;
	return (i);
}

char	*delim_strdup(const char *str, char delimiter)
{
	char	*dup;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != delimiter)
		len++;
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (perror("minishell"), NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*begin_str(int cut, char *str)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	if (ft_strlen(str) < (size_t)cut)
		res = ft_strdup(str);
	else
		res = ft_calloc((cut + 1), sizeof(char));
	if (!res)
		return (perror("minishell"), NULL);
	i = 0;
	while (i < cut)
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
