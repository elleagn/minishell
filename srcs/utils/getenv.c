/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:45:00 by gozon             #+#    #+#             */
/*   Updated: 2024/11/26 14:05:24 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_value(char *env_var)
{
	char	*first_occurence;

	if (!env_var)
		return (NULL);
	first_occurence = ft_strchr(env_var, '=');
	if (*first_occurence)
		return (&first_occurence[1]);
	return (NULL);
}

char	*mini_getenv(char *name, char **env)
{
	int	i;
	int	len;

	i = 0;
	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], len))
			return (get_value(env[i]));
		i++;
	}
	return (NULL);
}
