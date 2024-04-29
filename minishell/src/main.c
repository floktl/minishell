/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:03:04 by fkeitel           #+#    #+#             */
/*   Updated: 2024/04/29 14:07:12 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	global varibale for the history later
//char	*g_history[MAX_HISTORY];
//int		g_history_count = 0;

//	main loop start with  make and ./minishell
int	main(void)
{
	char	*command;
	t_tree	*parse_tree;

	command = NULL;
	signal(SIGINT, handle_signal);
	while (1)
	{
		printf("\033[32mminishell>\033[0m");
		fflush(stdout);
		command = ft_fgets();
		if (command == NULL)
		{
			continue ;
		}
		//printf("%s", command);
		if (command[0] && command[0] == '\n')
		{
			free(command);
			continue ;
		}
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			break ;
		}
		parse_tree = parse_command(command);
		free(command);
		if (parse_tree == NULL)
			continue ;
		command = NULL;
		print_parse_tree(parse_tree);
		execute_command(parse_tree);
		free_tree(parse_tree);
	}
	return (0);
}

//char	*args[MAX_ARGS];

	//command[strcspn(command, "\n")] = '\0';
	//g_history[g_history_count++] = strdup(command);
	//if (args[0] == NULL)
	//{
	//	continue ;
	//}
	//if (strcmp(args[0], "exit") == 0)
	//{
	//	break ;
	//}
	//if (strcmp(args[0], "history") == 0)
	//{
	//	while (i < g_history_count)
	//	{
	//		printf("%d: %s\n", i + 1, g_history[i]);
	//		i++;
	//	}
	//	continue ;
	//}
	//execute_command(args);

//while (i < g_history_count)
//{
//	free(g_history[i]);
//	i++;
//}
