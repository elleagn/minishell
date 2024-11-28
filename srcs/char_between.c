/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_between.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:47:30 by gozon             #+#    #+#             */
/*   Updated: 2024/11/28 13:50:10 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*begin_str(int cut, char *str)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	if (ft_strlen(str) < cut)
		return (ft_strdup(str));
	res = ft_calloc((cut + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < cut)
	{
		res[i] = str[i];
		i++;
	}
	return (res[i]);
}
