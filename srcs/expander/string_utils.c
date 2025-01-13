/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:45:49 by gozon             #+#    #+#             */
/*   Updated: 2025/01/13 13:27:17 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*delims_strdup(const char *str, char *delimiters)
{
	char	*dup;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	len = 0;
	while (str[len] && !ft_strchr(delimiters, str[len]))
		len++;
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (perror("minishell"), NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

int	join_var(char **expanded, char *str, t_data *data)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;
	int		len;

	var_name = delims_strdup(&str[1], " $\"'");
	if (!var_name)
	{
		data->exit_code = -1;
		return (-1);
	}
	len = ft_strlen(var_name) + 1;
	var_value = expand_var(var_name, data);
	free(var_name);
	if (data->exit_code == -1)
		return (-1);
	if (!var_value)
		return (len);
	tmp = ft_strjoin(*expanded, var_value);
	if (!tmp)
		data->exit_code = -1;
	free(var_value);
	replace_string(expanded, tmp);
	return (len);
}
