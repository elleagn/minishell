/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:51:26 by lcluzan           #+#    #+#             */
/*   Updated: 2025/01/09 15:57:21 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_space(char c)
{
	return (c == ' ');
}

int	is_ambiguous_redirect(char *expanded)
{
	int	i;

	if (!expanded || !expanded[0])
		return (1);
	i = 0;
	while (expanded[i])
	{
		if (ft_is_space(expanded[i]))
			return (1);
		i++;
	}
	return (0);
}

int	expand_redirections(t_redir *redir, t_data *data)
{
	char	*expanded;

	while (redir)
	{
		if (redir->type != HERE_DOC)
		{
			if (!redir->backup)
				redir->backup = ft_strdup(redir->filename);
			expanded = expand_string(redir->filename, data);
			if (!expanded)
				return (0);
			if (is_ambiguous_redirect(expanded))
			{
				free(expanded);
				ft_printf("minishell: %s: ambiguous redirect\n", redir->backup);
				return (0);
			}
			free(redir->filename);
			redir->filename = expanded;
		}
		redir = redir->next;
	}
	return (1);
}
