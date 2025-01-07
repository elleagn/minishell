/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:07:56 by gozon             #+#    #+#             */
/*   Updated: 2025/01/07 16:16:50 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_non_empty(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (var[i + 1]);
		i++;
	}
	return (0);
}

int	print_not_valid_identifier(char *var, int error)
{
	char	*str;

	if (error)
		return (1);
	str = strjoin_three("minishell: export: '", var,
			"': not a valid identifier\n");
	if (!str)
		return (-1);
	if (write(2, str, ft_strlen(str)) < 0)
		return (free(str), -1);
	free(str);
	return (1);
}

int	is_invalid(char *var, int error)
{
	int	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (print_not_valid_identifier(var, error));
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalpha(var[i]) && var[i] != '_' && !ft_isdigit(var[i]))
			return (print_not_valid_identifier(var, error));
		i++;
	}
	return (0);
}

int	handle_path(char *var, t_data *data)
{
	char	**new_path;

	if (ft_strncmp(var, "PATH=", 5))
		return (0);
	new_path = ft_split(&var[5], ':');
	if (!new_path)
		return (perror("minishell"), -1);
	free_char_array(data->path);
	data->path = new_path;
	return (0);
}

int	handle_var(char *var, t_data *data, int error)
{
	int	invalid;

	invalid = is_invalid(var, error);
	if (invalid == -1)
		return (-1);
	if (invalid)
		return (1);
	if (is_non_empty(var))
	{
		var = ft_strdup(var);
		if (!var)
			return (perror("minishell"), -1);
		if (add_var(var, data))
			return (free(var), -1);
		if (handle_path(var, data))
			return (free(var), -1);
	}
	return (0);
}
