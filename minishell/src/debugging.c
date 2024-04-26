/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:36:56 by fkeitel           #+#    #+#             */
/*   Updated: 2024/04/26 19:36:22 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	function to print the tree struct, only for debugging
void	print_parse_tree(const t_tree *tree)
{
	char	**flag;
	char	**arg;

	printf("\n");
	if (tree == NULL)
	{
		printf("t_parse_tree struct is NULL\n");
		return ;
	}
	printf("pipes_num: %d\n", tree->pipes_num);
	printf("Adress: %p\n", tree);
	if (tree->child_pipe)
		printf("childadress: %p\n", tree->child_pipe);
	if (tree->parent_pipe)
		printf("parentadress: %p\n", tree->parent_pipe);
	if (tree->type && tree->command)
	{
		printf("type: %d\n", tree->type);
		printf("command: %d\n", tree->command);
	}
	printf("flags: ");
	if (tree->flags != NULL)
	{
		flag = tree->flags;
		while (*flag != NULL)
		{
			printf("%s ", *flag);
			flag++;
		}
	}
	printf("\n");
	printf("arguments: ");
	if (tree->arguments != NULL)
	{
		arg = tree->arguments;
		while (*arg != NULL)
		{
			printf("%s ", *arg);
			arg++;
		}
	}
	printf("\nargv: %d", tree->args_num);
	printf("\ncmd_brch: ");
	if (tree->cmd_brch)
	{
		printf(":%s:", tree->cmd_brch);
	}
	printf("\n");
	printf("output: %d\n", tree->output);
	printf("\n");
	if (tree->child_pipe != NULL)
	{
		print_parse_tree(tree->child_pipe);
	}
}

//	print two dimensional array
void printCharArray2D(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        for (int j = 0; array[i][j] != '\0'; j++) {
            printf("%c ", array[i][j]);
        }
        printf("\n");
    }
}