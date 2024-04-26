/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:47:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/04/26 19:41:24 by fkeitel          ###   ########.fr       */
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
		//if (execvp(args[0], args) == -1)
		//{
		//	perror("Error");
		//}
		exit(EXIT_FAILURE);
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
