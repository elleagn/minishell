#include <minishell.h>

// Extracts variable name from string after $
size_t extract_var_name(const char *str, char **var_name)
{
size_t  len;

len = 0;
*var_name = NULL;

// Empty string or not a valid variable start character
if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
	return (0);

// Count length of variable name (alphanumeric or underscore)
while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
	len++;

// If we found a valid name, extract it
if (len > 0)
	*var_name = ft_substr(str, 0, len);

return (len);
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
