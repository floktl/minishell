/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:03:04 by fkeitel           #+#    #+#             */
/*   Updated: 2024/04/19 11:10:32 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*g_history[MAX_HISTORY];
int		g_history_count = 0;

int	main(void)
{
	char	command[MAX_COMMAND_LENGTH];
	char	*args[MAX_ARGS];
	int		i;

	i = 0;
	signal(SIGINT, handle_signal);
	while (1)
	{
		printf("$ ");
		fflush(stdout);
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break ;
		}
		command[strcspn(command, "\n")] = '\0';
		g_history[g_history_count++] = strdup(command);
		parse_command(command, args);
		if (args[0] == NULL)
		{
			continue ;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			break ;
		}
		if (strcmp(args[0], "history") == 0)
		{
			while (i < g_history_count)
			{
				printf("%d: %s\n", i + 1, g_history[i]);
				i++;
			}
			continue ;
		}
		execute_command(args);
	}
	i = 0;
	while (i < g_history_count)
	{
		free(g_history[i]);
		i++;
	}
	return (0);
}
