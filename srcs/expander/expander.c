/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:55:39 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/14 09:27:39 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*expand_token(t_token **token, t_data *data)
{
	t_token	*next;
	char	*word;

	next = (*token)->next;
	word = (*token)->literal;
	if ((word && word[0] != '$') || ((*token)->prev
			&& (*token)->prev->type == HERE_DOC))
		return (next);
	(*token)->literal = expand_var(word, data);
	(*token)->backup = word;
	if (!(*token)->prev || (*token)->prev->type == WORD
		|| (*token)->prev->type == STRING || (*token)->prev->type == PIPE)
	{
		if (!(*token)->literal)
			del_token_from_list(token, *token);
		else
			split_words(*token, data);
	}
	return (next);
}

int	expander(t_token **tokens, t_data *data)
{
	t_token	*current;

	if ((*tokens)->type == WORD)
		current = expand_token(tokens, data);
	else
		current = *tokens;
	if (data->exit_code == -1)
		return (1);
	while (current)
	{
		if (current->type == WORD)
			current = expand_token(&current, data);
		else if (current->type == STRING)
			current = remove_quotes(current, data);
		else
			current = current->next;
		if (data->exit_code == -1)
			return (1);
	}
	return (0);
}
