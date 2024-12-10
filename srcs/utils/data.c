/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:04:48 by gozon             #+#    #+#             */
/*   Updated: 2024/12/10 11:21:01 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (perror("minishell"), NULL);
	data->env = NULL;
	data->env_size = 0;
	data->path = 0;
	data->lexer_list = NULL;
	data->exit_code = 0;
}

void	clear_data(t_data *data)
{
	free_char_array(data->env);
	free_char_array(data->path);
	clear_token_list(&(data->lexer_list));
}
