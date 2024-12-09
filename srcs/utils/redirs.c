/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:36:14 by gozon             #+#    #+#             */
/*   Updated: 2024/12/07 09:43:03 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->filename = NULL;
	redir->fd = -2;
	redir->next = NULL;
	redir->type = UNDEFINED;
	return (redir);
}

void	clear_redir(t_redir *redir)
{
	if (!redir)
		return ;
	free(redir->filename);
	free(redir);
}

void	clear_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	tmp = redir->next;
	while (tmp)
	{
		clear_redir(redir);
		redir = tmp;
		tmp = tmp->next;
	}
	clear_redir(redir);
}
