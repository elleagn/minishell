#include <minishell.h>

// Extracts variable name from string after $
char *extract_var_name(const char *str, int *i)
{
    int start;
    int len;

    start = 0;  // Now start at 0 since we're working with str directly

    // First character must be alphabetic or underscore
    if (!ft_isalpha(str[start]) && str[start] != '_')
        return (NULL);

    // Continue while character is alphanumeric or underscore
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;

    len = *i;  // Length is now just the final position of i
    (*i)++;
    return (ft_substr(str, start, len));
}

// Gets environment variable value
char *get_env_value(const char *name, t_data *data)
{
    int     i;
    size_t  len;

    len = ft_strlen(name);
    i = 0;
    while (data->env[i])
    {
        if (!ft_strncmp(data->env[i], name, len) && data->env[i][len] == '=')
            return (data->env[i] + len + 1);
        i++;
    }
    return (NULL);
}
