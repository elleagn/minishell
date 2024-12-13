/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:10:54 by gozon             #+#    #+#             */
/*   Updated: 2024/12/11 10:15:21 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_export(t_command *command, t_data *data)
{
	int		i;
	int		error_global;
	int		error_local;

	if (!command->av[1])
		return (mini_env(command, data));
	error_global = 0;
	i = 1;
	while (command->av[i])
	{
		write(1, "HELLO\n", 7);
		error_local = handle_var(command->av[i], data);
		ft_printf("%i\n", error_local);
		if (error_local == -1)
			return (-1);
		if (error_local == 1)
			error_global = 1;
		i++;
	}
	return (error_global);
}

int	mini_unset(t_command *command, t_data *data)
{
	int	i;

	i = 1;
	while (command->av[i])
	{
		remove_var(command->av[i], data);
		i++;
	}
	return (0);
}
