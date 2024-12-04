/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:48:27 by gozon             #+#    #+#             */
/*   Updated: 2024/12/04 09:44:12 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	t_token	*token;
	char	input1[] = "<nsnsnxs";
	char	input2[] = "||sjacsj";
	char	input3[] = "<<densnsx";
	char	input4[] = "caca sacs askc";
	char	input5[] = "ca'ca ushsc saccs";
	char	input6[] = "bl\"bl sajsx sjxs";
	char	input7[] = "\"ty y6ytgh";
	char	input8[] = "\'ty y6ytgh";
	char	input9[] = "caca>sacs askc";
	char	input10[] = "\"dfdrtytrtrc\"qwjwqdjd";
	char	input11[] = "'dfdrtytrtrc'qwjwqdjd";

	printf("------ CREATE_NEXT_TOKEN ----\n");
	printf("------ operators ------\n");
	token = create_next_token(input1);
	if (token->type == LESS)
		printf("OK\n");
	else
		printf("KO\n");
	token = create_next_token(input2);
	if (token->type == PIPE)
		printf("OK\n");
	else
		printf("KO\n");
	token = create_next_token(input3);
	if (token->type == LESSLESS)
		printf("OK\n");
	else
		printf("KO\n");
	printf("------ words ------\n");
	token = create_next_token(input4);
	if (token->type == WORD)
		printf("input: %s result: %s\n", input4, token->literal);
	else
		printf("KO\n");
	token = create_next_token(input5);
	if (token->type == WORD)
		printf("input: %s result: %s\n", input5, token->literal);
	else
		printf("KO\n");
	token = create_next_token(input6);
	if (token->type == WORD)
		printf("input: %s result: %s\n", input6, token->literal);
	else
		printf("KO\n");
	token = create_next_token(input7);
	if (token->type == WORD)
		printf("input: %s result: %s\n", input7, token->literal);
	else
		printf("KO\n");
	token = create_next_token(input8);
	if (token->type == WORD)
		printf("input: %s result: %s\n", input8, token->literal);
	else
		printf("KO\n");
	token = create_next_token(input9);
	if (token->type == WORD)
		printf("input: %s result: %s\n", input9, token->literal);
	else
		printf("KO\n");
	printf("------ strings ------\n");
	token = create_next_token(input10);
	if (token->type == STRING)
		printf("input: %s result: %s\n", input10, token->literal);
	else
		printf("KO\n");
	token = create_next_token(input11);
	if (token->type == STRING)
		printf("input: %s result: %s\n", input11, token->literal);
	else
		printf("KO\n");
	return (0);
}
