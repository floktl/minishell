/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:47:36 by fkeitel           #+#    #+#             */
/*   Updated: 2024/04/30 14:15:05 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_paths(void)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	path = getenv("PATH");
	if (path)
	{
		paths = ft_split(path, ':');
		if (!paths)
			return (0);
		while (paths[i])
		{
			path = paths[i];
			paths[i] = ft_strjoin(path, "/");
			free(path);
			if (!paths[i])
				return (NULL);
			i++;
		}
		return (paths);
	}
	else
		return (NULL);
}

char	*get_cmdpath(char *cmd)
{
	int		i;
	char	*cmd_path;
	char	**paths;

	i = 0;
	paths = get_paths();
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	exec_cmd(t_tree *tmp, char **envp)
{
	char	*cmdpath;

	cmdpath = get_cmdpath(tmp->arguments[0]);
	execve(cmdpath, tmp->arguments, envp);
	perror("execution failed");
	exit (0);
}

int	pipe_cmds(t_tree *tmp, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		close(fd[0]);
		if (tmp ->child_pipe)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_cmd(tmp, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (1);
}

void	execute_command(t_tree *tree, char **envp)
{
	t_tree	*tmp;
	int		stdina;

	tmp = tree;
	stdina = dup(STDIN_FILENO);
	while (tmp)
	{
		pipe_cmds(tmp, envp);
		tmp = tmp->child_pipe;
	}
	dup2(stdina, STDIN_FILENO);
	wait(NULL);
	return ;
}
