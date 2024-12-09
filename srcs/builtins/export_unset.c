/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:10:54 by gozon             #+#    #+#             */
/*   Updated: 2024/12/09 12:01:10 by gozon            ###   ########.fr       */
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
			if (add_var(command->av[i], data))
				return (1);
		}
		i++;
	}
	return (0);
}

int	mini_unset(t_command)
{

}
