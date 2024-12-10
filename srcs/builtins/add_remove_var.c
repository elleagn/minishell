/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_remove_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 08:36:33 by gozon             #+#    #+#             */
/*   Updated: 2024/12/10 11:25:26 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**expand_env(t_data *data)
{
	int		i;
	char	**new_env;
	int		new_size;

	new_size = data->env_size + ENV_SIZE;
	new_env = ft_calloc(new_size + 1, sizeof(char *));
	if (!new_env)
		return (perror("minishell"), NULL);
	data->env_size = new_size;
	i = 0;
	while (data->env[i])
	{
		new_env[i] = data->env[i];
		i++;
	}
	free(data->env);
	data->env = new_env;
	return (new_env);
}

int	add_var(char *var, t_data *data)
{
	int	oldvar;
	int	env_index;

	oldvar = find_env_var(var, data->env, 0);
	if (oldvar >= 0)
	{
		free(data->env[oldvar]);
		data->env[oldvar] = var;
		return (0);
	}
	else
	{
		env_index = array_size(data->env);
		if (!(env_index < data->env_size))
		{
			if (!expand_env(data))
				return (1);
		}
		data->env[env_index] = var;
		return (0);
	}
}

void	remove_var(char *var, t_data *data)
{
	int	var_index;
	int	i;

	var_index = find_env_var(var, data->env, 1);
	if (var_index < 0)
		return ;
	free(data->env[var_index]);
	i = var_index;
	while (data->env[i])
	{
		data->env[i] = data->env[i + 1];
		i++;
	}
}
