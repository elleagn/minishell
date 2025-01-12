/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:55:39 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/12 11:50:28 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*expand_token(t_token **token, t_data *data)
{
	t_token	*next;
	char	*word;

	next = (*token)->next;
	word = (*token)->literal;
	if (word && word[0] == '$' && (*token)->prev
		&& (*token)->prev->type == HERE_DOC)
		return (next);
	(*token)->literal = expand_var(word, data);
	free(word);
	if ((*token)->literal && (!(*token)->prev || (*token)->prev->type == WORD
			|| (*token)->prev->type == PIPE))
		split_words(token, data);
	return (next);
}

int	expander(t_token **tokens, t_data *data)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == WORD)
			current = expand_token(&current, data);
		if (current->type == STRING)
			current = remove_quotes(&current, data);
		if (data->exit_code == -1)
			return (1);
	}
	return (0);
}
