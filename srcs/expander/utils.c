/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:49:50 by gozon             #+#    #+#             */
/*   Updated: 2025/01/12 12:36:20 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*join_var_name(char *expanded, char *var_name, t_data *data)
{
	char	*var;

	var = mini_getenv(var_name, data->env);
	if (!var)
		return (NULL);
	expanded = ft_strjoin(expanded, var);
	if (!expanded)
		data->exit_code = -1;
	return (expanded);
}

char	*expand_var(char *word, t_data *data)
{
	char	*expanded;
	char	**var_names;
	int		i;

	i = 0;
	expanded = NULL;
	var_names = ft_split(word, '$');
	if (!var_names)
	{
		data->exit_code = -1;
		return (NULL);
	}
	while (var_names[i])
	{
		replace_string(&expanded, join_var_name(expanded, var_names[i], data));
		if (data->exit_code == -1)
			return (NULL);
		i++;
	}
	return (expanded);
}
