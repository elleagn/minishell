/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:00:46 by lcluzan           #+#    #+#             */
/*   Updated: 2024/12/17 15:19:15 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redir(t_token *token)
{
	t_redir	*new_redir;

	new_redir = init_redir();
	if (!new_redir)
		return (NULL);
	new_redir->type = token->type;
	return (new_redir);
}

int	add_arg_to_command(t_command *command, char *literal)
{
	int		ac;
	char	**new_av;

	ac = array_size(command->av);
	new_av = malloc(sizeof(char *) * (ac + 2));
	if (!new_av)
		return (0);
	if (command->av)
	{
		ft_memcpy(new_av, command->av, sizeof(char *) * ac);
		free(command->av);
	}
	new_av[ac] = ft_strdup(literal);
	if (!new_av[ac])
	{
		free(new_av);
		return (0);
	}
	new_av[ac + 1] = NULL;
	command->av = new_av;
	return (1);
}
