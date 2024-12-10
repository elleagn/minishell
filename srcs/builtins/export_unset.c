/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:10:54 by gozon             #+#    #+#             */
/*   Updated: 2024/12/10 08:21:20 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (var[i + 1]);
	}
	return (0);
}

int	mini_export(t_command *command, t_data *data)
{
	char	*var;
	int		i;

	if (!command->av[1])
		return (mini_env(command, data));
	i = 1;
	while (command->av[i])
	{
		if (is_valid(command->av[i]))
		{
			var = ft_strdup(command->av[i]);
			if (!var)
				return (perror("minishell"), 1);
			if (add_var(var, data))
				return (1);
		}
		i++;
	}
	return (0);
}

int	mini_unset(t_command *command, t_data *data)
{
	int	i;

	i = 0;
	while (command->av[i])
	{
		remove_var(command->av[i], data);
		i++;
	}
	return (0);
}
