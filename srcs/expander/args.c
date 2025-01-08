#include <minishell.h>

int expand_command_args(t_command *cmd, t_data *data)
{
    int     i;
    char    *expanded;

    if (!cmd->av)
        return (1);

    i = 0;
    while (cmd->av[i])
    {
        expanded = expand_string(cmd->av[i], data);
        if (!expanded)
            return (0);
        free(cmd->av[i]);
        cmd->av[i] = expanded;
        i++;
    }
    return (1);
}
