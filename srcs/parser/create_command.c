/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:11:51 by nouillebobb       #+#    #+#             */
/*   Updated: 2024/12/13 01:46:18 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void prep_no_args(t_command *command, t_data *data)
{
    command->av = ft_calloc(2, sizeof(char *));
    command->av[0] = ft_strdup(command->av[0]);
    command->av[1] = NULL;
    command->builtin = NULL;
    command->redirs = NULL;
    command->pipe[0] = -1;
    command->pipe[1] = -1;
    command->pid = 0;
    command->errornb = 0;
    command->next = NULL;
}

static void prep_args(t_command *command, t_data *data)
{
    t_token *token;
    int     i;

    i = 0;
    token = data->lexer_list;
    while (token && token->type != PIPE)
    {
        if (token->type == WORD)
            i++;
        token = token->next;
    }
    command->av = ft_calloc(i + 1, sizeof(char *));
    i = 0;
    token = data->lexer_list;
    while (token && token->type != PIPE)
    {
        if (token->type == WORD)
        {
            command->av[i] = ft_strdup(token->literal);
            i++;
        }
        token = token->next;
    }
    command->av[i] = NULL;
}

void    create_command(t_data *data)
{
    t_command   *command;
    t_token     *token;

    command = init_comand();
    token = data->lexer_list;
    while (token && token->type != PIPE)
        token = token->next;
    if (!token)
        prep_no_args(command, data);
    else
        prep_args(command, data);
    add_command_to_list(&data->command_list, command);
}