/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:10:54 by gozon             #+#    #+#             */
/*   Updated: 2024/12/09 11:36:03 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_export(t_command *command, t_data *data)
{
	char	*var;

	if (!command->av[1])
		return (mini_env(command, data));
}
