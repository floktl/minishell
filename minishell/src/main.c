/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:03:04 by fkeitel           #+#    #+#             */
/*   Updated: 2024/04/26 20:01:33 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	global varibale for the history later
//char	*g_history[MAX_HISTORY];
//int		g_history_count = 0;

//	@Soeren: Du kannst das programm mit make und ./minishell starten, ist sollte im parsing funktionieren und ist leakfrei
//	echo und pipes funktioniert, zum beispiel: e"ch"o abcdef | echo "test pipe skip | test" | echo next pipe
//	print_parse_tree druckt alle werte aus dem tree struct, kannst du auch auskommentieren
//	"exit" als command oder ctr+C beendet die shell, zum testen hilfreich
//	execute_command bekommt als input den vollen struct, die funktion muss noch auf den struct angepasst werden
//	die main und execution kannst du veraendern wie du willst, alles in der parsing function besser nicht :)
//	einfach return tippen in der shell funktioniert noch nicht, immer nur mit einem command bisher, vieelicht faellt dir was schnelles ein
//	waere gut, wenn du die struktur in der header datei einbehaeltst
//	executer fuktion ist in execution_functions ordner

//	main loop start with  make and ./minishell
int	main(void)
{
	char	*command;
	t_tree	*parse_tree;

	signal(SIGINT, handle_signal);	// function to catch the signals
	while (1)
	{
		printf("$ ");
		fflush(stdout); //	verboten, muss nachher entfernt/ersetzt werden!
		command = ft_fgets();	// custum fgets function
		if (command == NULL)
		{
			printf("\n");
			break ;
		}
		if (command[0] && command[0] == '\n')
			continue ;
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			break ;
		}
		parse_tree = parse_command(command); //	parsing function
		free(command);
		if (parse_tree == NULL)
			continue ;
		command = NULL;
		print_parse_tree(parse_tree);	// function to print tree struct values
		//execute_command(parse_tree->cmd_brch);	//	execution function
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
