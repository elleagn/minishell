/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:49:50 by gozon             #+#    #+#             */
/*   Updated: 2025/01/12 14:53:15 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*join_var_name(char *expanded, char *var_name, t_data *data)
{
	char	*var;

	var = mini_getenv(var_name, data->env);
	if (!var)
		return (expanded);
	expanded = ft_strjoin(expanded, var);
	if (!expanded)
		data->exit_code = -1;
	return (expanded);
}

char	*expand_var(char *word, t_data *data)
{
	char	*expanded;
	char	**var_names;
	int		i;

	i = 0;
	expanded = NULL;
	var_names = ft_split(word, '$');
	if (!var_names)
	{
		data->exit_code = -1;
		return (NULL);
	}
	while (var_names[i])
	{
		replace_string(&expanded, join_var_name(expanded, var_names[i], data));
		if (data->exit_code == -1)
			return (free_char_array(var_names), NULL);
		i++;
	}
	free_char_array(var_names);
	return (expanded);
}

int	insert_word(char *literal, t_token *tlst)
{
	t_token	*token;

	token = init_token();
	if (!token)
		return (1);
	token->type = WORD;
	token->literal = literal;
	token->next = tlst->next;
	token->prev = tlst;
	tlst->next = token;
	token->next->prev = token;
	token->position = tlst->position;
	return (0);
}

void	split_words(t_token *token, t_data *data)
{
	char	**split;
	int		i;

	split = ft_split(token->literal, ' ');
	if (!split)
	{
		data->exit_code = -1;
		return ;
	}
	replace_string(&token->literal, split[0]);
	i = 1;
	while (split[i])
	{
		if (insert_word(split[i], token))
		{
			data->exit_code = -1;
			break ;
		}
		i++;
		token = token->next;
	}
	while (split[i++])
		free(split[i]);
	free(split);
}
