/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arg_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:47:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/04/26 19:52:59 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//	function to read the user input from the terminal command
char	*ft_fgets(void)
{
	struct termios	old_termios;
	struct termios	new_termios;
	char			*line;
	size_t			len;
	int				c;

	line = NULL;
	len = 0;
	tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios;
	new_termios.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	c = getchar();
	while (c != '\n' && c != EOF)
	{
		line = realloc(line, sizeof(char) * (len + 2));
		if (line == NULL)
		{
			free(line);
			tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
			return (perror("realloc"), NULL);
		}
		line[len++] = (char)c;
		line[len] = '\0';
		c = getchar();
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	return (line);
}

//	count_arguments and remove quotes
int	adapt_and_count_arguments(t_tree *tree, char *command_str)
{
	int	i;

	i = 0;
	while (command_str[i] && command_str[i] == ' ')
		i++;
	while (command_str[i])
	{
		if (command_str[i - 1] && command_str[i - 1] == ' ')
		{
			tree->args_num++;
			if (command_str[i] == '\'')
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//	function to split the commands into the components
int	split_command(t_tree *tree, char *command_str)
{
	if (det_and_rem_quotes_first_word(command_str) == EXIT_FAILURE)
	{
		printf("undisclosed quotes in first word\n");
		return (EXIT_FAILURE);
	}
	//if (adapt_and_count_arguments(tree, command_str) == EXIT_FAILURE)
	//{
	//	printf("Error removing whitespaces\n");
	//	return (EXIT_FAILURE);
	//}
	if (is_substr_first_word(command_str, "echo"))
	{
		tree->type = EXEC;
		tree->command = ECHO;
	}
	return (EXIT_SUCCESS);
}

int seperate_pipes(t_tree **tree, char *command_str)
{
	int		i;
	int		pipe_num;
	char	**pipes;
	t_tree	*temp;
	t_tree	*prev;

	prev = NULL;
	i = 0;
	pipe_num = 1;
	pipes = split_pipes(command_str, '|', &pipe_num);
	if (pipes)
	{
		while (pipes[i])
		{
			temp = (t_tree *)malloc(sizeof(t_tree));
			if (!temp)
			{
				free_tree(temp);
				perror("malloc");
				return (EXIT_FAILURE);
			}
			initiliaze_command_tree(temp);
			temp->pipes_num = i + 1;
			if (split_command(temp, pipes[i]) == EXIT_FAILURE)
			{
				printf("split_command\n");
				free_tree(temp);
				return (EXIT_FAILURE);
			}
			temp->cmd_brch = ft_strdup(pipes[i]);
			if (!temp->cmd_brch)
			{
				perror("strdup");
				free_tree(temp);
				return (EXIT_FAILURE);
			}
			temp->parent_pipe = prev;
			prev = temp;
			ft_treeadd_back(tree, temp);
			i++;
		}
		free_two_dimensional_array(pipes);
	}
	else
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

