/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:48:27 by gozon             #+#    #+#             */
/*   Updated: 2025/01/08 14:19:38 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// create_new_token

// int	main(void)
// {
// 	t_token	*token;
// 	char	input1[] = "<nsnsnxs";
// 	char	input2[] = "||sjacsj";
// 	char	input3[] = "<<densnsx";
// 	char	input4[] = "caca sacs askc";
// 	char	input5[] = "ca'ca ushsc saccs";
// 	char	input6[] = "bl\"bl sajsx sjxs";
// 	char	input7[] = "\"ty y6ytgh";
// 	char	input8[] = "\'ty y6ytgh";
// 	char	input9[] = "caca>sacs askc";
// 	char	input10[] = "\"dfdrtytrtrc\"qwjwqdjd";
// 	char	input11[] = "'dfdrtytrtrc'qwjwqdjd";
// 	char	input12[] = "dfdrtyt'rtrc'qwjwqdjd";

// 	printf("------ CREATE_NEXT_TOKEN ----\n");
// 	printf("------ operators ------\n");
// 	token = create_next_token(input1);
// 	if (token->type == INFILE)
// 		printf("OK\n");
// 	else
// 		printf("KO\n");
// 	token = create_next_token(input2);
// 	if (token->type == PIPE)
// 		printf("OK\n");
// 	else
// 		printf("KO\n");
// 	token = create_next_token(input3);
// 	if (token->type == HERE_DOC)
// 		printf("OK\n");
// 	else
// 		printf("KO\n");
// 	printf("------ words ------\n");
// 	token = create_next_token(input4);
// 	if (token->type == WORD)
// 		printf("input: %s result: %s\n", input4, token->literal);
// 	else
// 		printf("KO\n");
// 	token = create_next_token(input5);
// 	if (token->type == WORD)
// 		printf("input: %s result: %s\n", input5, token->literal);
// 	else
// 		printf("KO\n");
// 	token = create_next_token(input6);
// 	if (token->type == WORD)
// 		printf("input: %s result: %s\n", input6, token->literal);
// 	else
// 		printf("KO\n");
// 	token = create_next_token(input7);
// 	if (token->type == WORD)
// 		printf("input: %s result: %s\n", input7, token->literal);
// 	else
// 		printf("KO\n");
// 	token = create_next_token(input8);
// 	if (token->type == WORD)
// 		printf("input: %s result: %s\n", input8, token->literal);
// 	else
// 		printf("KO\n");
// 	token = create_next_token(input9);
// 	if (token->type == WORD)
// 		printf("input: %s result: %s\n", input9, token->literal);
// 	else
// 		printf("KO\n");
// 	printf("------ strings ------\n");
// 	token = create_next_token(input10);
// 	if (token->type == STRING)
// 		printf("input: %s result: %s\n", input10, token->literal);
// 	else
// 		printf("KO\n");
// 	token = create_next_token(input11);
// 	if (token->type == STRING)
// 		printf("input: %s result: %s\n", input11, token->literal);
// 	else
// 		printf("KO\n");
// 	token = create_next_token(input12);
// 	if (token->type == STRING)
// 		printf("input: %s result: %s\n", input12, token->literal);
// 	else
// 		printf("KO\n");
// 	return (0);
// }

// check_unclosed_quotes

int	check_unclosed_quotes(char *input);

int main(void)
{
	char	input1[] = "sajnsncnsncsjn | < sxnjnx";
	char	input2[] = "nsjnxjnxnj\"jsxns'xn\"";
	char	input3[] = "jsnjsnjcn'sn\"xknkxs'";
	char	input4[] = "cksmcsmkm'skmscmckm";
	char	input5[] = "snxxsnxsnjnx\"jnxsnxsjasxsansannsxn";

	if (!check_unclosed_quotes(input1))
		printf("OK\n");
	else
		printf("KO\n");
	if (!check_unclosed_quotes(input2))
		printf("OK\n");
	else
		printf("KO\n");
	if (!check_unclosed_quotes(input3))
		printf("OK\n");
	else
		printf("KO\n");
	if (check_unclosed_quotes(input4))
		printf("OK\n");
	else
		printf("KO\n");
	if (check_unclosed_quotes(input5))
		printf("OK\n");
	else
		printf("KO\n");
	return (0);
}
