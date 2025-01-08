/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:55:39 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/08 13:54:00 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *expand_string(char *str, t_data *data)
{
    char    *result;
    char    *var_name;
    char    *var_value;
    int     i;
    int     in_quotes;

    if (!str)
        return (NULL);

    result = ft_strdup("");
    i = 0;
    in_quotes = 0;

    while (str[i])
    {
        if (str[i] == '"' && !in_quotes)
            in_quotes = 1;
        else if (str[i] == '"' && in_quotes)
            in_quotes = 0;

        if (str[i] == '$')
        {
            i++;
            if (str[i] == '?')
            {
                char *exit_str = ft_itoa(data->exit_code);
                result = ft_strjoin_free(result, exit_str);
                free(exit_str);
                i++;
                continue;
            }

            var_name = extract_var_name(str + i, &i);
            if (!var_name)
                continue;

            // Use our modified get_env_value
            var_value = get_env_value(var_name, data);
            if (var_value)
                result = ft_strjoin_free(result, var_value);
            free(var_name);
        }
        else
        {
            char tmp[2] = {str[i], '\0'};
            result = ft_strjoin_free(result, tmp);
            i++;
        }
    }
    return (result);
}

int expander(t_command *cmd, t_data *data)
{
    t_command   *current;
    char        *resolved_path;

    current = cmd;
    while (current)
    {
        // if (!expand_redirections(current->redirs, data))
        //     return (0);
        if (!expand_command_args(current, data))
            return (0);
        if (current->builtin < 0 && current->av && current->av[0])
        {
            resolved_path = find_in_path(current->av[0], data);
            if (!resolved_path)
            {
                ft_printf("minishell: %s: command not found\n", current->av[0]);
                return (0);
            }
            free(current->av[0]);
            current->av[0] = resolved_path;
        }
        current = current->next;
    }
	print_command(cmd);
    return (1);
}
