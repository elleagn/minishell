/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:20:46 by gozon             #+#    #+#             */
/*   Updated: 2024/11/28 10:20:58 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_operator_type(t_token *token, char *input)
{
	if (ft_strncmp(input, "<<", 2))
		token->type = LESSLESS;
	else if (ft_strncmp(input, "<", 1))
		token->type = LESS;
	else if (ft_strncmp(input, ">>", 2))
		token->type = GREATERGREATER;
	else if (ft_strncmp(input, ">", 1))
		token->type = GREATER;
	else if (ft_strncmp(input, "|", 1))
		token->type = PIPE;
}
