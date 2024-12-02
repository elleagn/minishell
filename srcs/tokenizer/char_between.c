/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_between.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:47:30 by gozon             #+#    #+#             */
/*   Updated: 2024/11/29 10:12:25 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*begin_str(int cut, char *str)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	if (ft_strlen(str) < (size_t)cut)
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
	return (res);
}

// int	main(void)
// {
// 	char	str[] = "Bonjour j'aime les pates !";
// 	char	*str_beginning;

// 	str_beginning = begin_str(7, str);
// 	printf("%s\n", str_beginning);
// 	free(str_beginning);
// 	return (0);
// }
