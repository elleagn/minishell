/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:13:53 by lcluzan           #+#    #+#             */
/*   Updated: 2024/12/13 01:15:20 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_heredoc(t_data *data, t_token *token)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*next;
	t_token	*heredoc;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == LESSLESS)
		{
			prev = tmp->prev;
			next = tmp->next;
			tmp->prev->next = NULL;
			tmp->next->prev = NULL;
			tmp->prev = NULL;
			tmp->next = NULL;
			heredoc = tmp->next;
			while (heredoc && heredoc->type != LESSLESS)
				heredoc = heredoc->next;
			if (heredoc)
				heredoc->prev = NULL;
			parse_heredoc(data, tmp);
			tmp->prev = prev;
			tmp->next = next;
		}
		tmp = tmp->next;
	}
}

void	parse_heredoc(t_data *data)
{
	t_token	*tmp;

	tmp = data->lexer_list;
	while (tmp)
	{
		if (tmp->type == LESSLESS)
			parse_heredoc(data, tmp);
		tmp = tmp->next;
	}
}