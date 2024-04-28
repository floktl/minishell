/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:47:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/04/28 21:22:01 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//	function to execute the command
void	execute_command(t_tree *tree)
{
	pid_t	pid;
	int		status;

	(void)tree;
	pid = fork();
	if (pid == 0)
	{
		if (execvp(tree->arguments[0], tree->arguments) == -1)
		{
			perror("Error");
		}
		return ;
	}
	else if (pid < 0)
	{
		perror("Fork failed");
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			waitpid(pid, &status, WUNTRACED);
		}
	}
}
