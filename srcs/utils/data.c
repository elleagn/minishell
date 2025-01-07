/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:04:48 by gozon             #+#    #+#             */
/*   Updated: 2025/01/07 14:28:13 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_builtin_array(int (*builtins[8])(t_command *, t_data *))
{
	builtins[0] = mini_echo;
	builtins[1] = mini_env;
	builtins[2] = mini_export;
	builtins[3] = mini_unset;
	builtins[4] = mini_cd;
	builtins[5] = mini_pwd;
	builtins[6] = mini_exit;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (perror("minishell"), NULL);
	data->env = NULL;
	data->env_size = 0;
	create_builtin_array(data->builtin);
	data->path = 0;
	data->lexer_list = NULL;
	data->exit_code = 0;
	return (data);
}

void	clear_data(t_data *data)
{
	free_char_array(data->env);
	free_char_array(data->path);
	clear_token_list(&(data->lexer_list));
	free(data);
}
