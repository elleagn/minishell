/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:36:14 by gozon             #+#    #+#             */
/*   Updated: 2025/01/07 10:47:32 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (perror("minishell"), NULL);
	redir->filename = NULL;
	redir->backup = NULL;
	redir->fd = -2;
	redir->next = NULL;
	redir->backup = NULL;
	redir->type = UNDEFINED;
	return (redir);
}

void	clear_redir(t_redir *redir)
{
	if (!redir)
		return ;
	free(redir->filename);
	free(redir->backup);
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
