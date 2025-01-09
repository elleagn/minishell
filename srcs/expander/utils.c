/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:05:17 by lcluzan           #+#    #+#             */
/*   Updated: 2025/01/09 16:05:39 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*handle_exit_code(t_data *data, int *i)
{
	char	*exit_str;

	(*i)++;
	exit_str = ft_itoa(data->exit_code);
	return (exit_str);
}

int8_t	handle_quotes(char current_char, char *current_quote, int *i)
{
	if (current_char == '"' || current_char == '\'')
	{
		if (*current_quote == 0)
			*current_quote = current_char;
		else if (*current_quote == current_char)
			*current_quote = 0;
		else
			return (0);
		(*i)++;
		return (1);
	}
	else
	{
		return (0);
	}
}

char	*handle_variable(char *str, t_data *data, int *i)
{
	char	*var_name;
	char	*var_value;
	size_t	var_len;

	(*i)++;
	if (str[*i] == '?')
		return (handle_exit_code(data, i));
	var_len = extract_var_name(str + *i, &var_name);
	if (!var_len)
		return (NULL);
	var_value = get_env_value(var_name, data);
	free(var_name);
	*i += var_len;
	if (var_value)
		return (ft_strdup(var_value));
	return (NULL);
}

char	*append_char(char c)
{
	char	*tmp;

	tmp = malloc(2);
	if (!tmp)
		return (NULL);
	tmp[0] = c;
	tmp[1] = '\0';
	return (tmp);
}

char	*expand_string(char *str, t_data *data)
{
	char	*result;
	char	*tmp;
	int		i;
	char	current_quote;

	result = ft_strdup("");
	i = 0;
	current_quote = 0;
	while (str[i])
	{
		if (handle_quotes(str[i], &current_quote, &i))
			continue ;
		if (str[i] == '$')
			tmp = handle_variable(str, data, &i);
		else
			tmp = append_char(str[i++]);
		if (tmp)
		{
			result = ft_strjoin_free(result, tmp);
			free(tmp);
		}
	}
	return (result);
}
