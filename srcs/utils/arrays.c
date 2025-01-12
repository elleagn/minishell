/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:14:39 by gozon             #+#    #+#             */
/*   Updated: 2025/01/12 14:10:47 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	array_size(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

char	**dup_env_array(char **envp, t_data *data)
{
	char	**new_env;
	int		i;
	int		len;

	len = array_size(envp);
	while (data->env_size < len)
		data->env_size += ENV_SIZE;
	new_env = ft_calloc(data->env_size + 1, sizeof(char *));
	if (!new_env)
		return (perror("minishell"), NULL);
	i = 0;
	while (envp && envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env)
			return (perror("minishell"), free_char_array(new_env), NULL);
		i++;
	}
	data->env = new_env;
	return (new_env);
}

void	replace_string(char **str1, char *str2)
{
	if (*str1 != str2)
	{
		free(*str1);
		*str1 = str2;
	}
}
