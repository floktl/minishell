/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:33:14 by stopp             #+#    #+#             */
/*   Updated: 2024/10/10 15:32:03 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	file_error(char *str, char *error, t_tree *tree)
{
	dup2(2, 1);
	ft_printf("%s: %s\n", str, error);
	dup2(tree->stdoutput, 1);
	tree->out_fd = -1;
	tree->exit_status = 1;
}

int	check_dir_out(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (!dir)
		return (0);
	else
	{
		closedir(dir);
		return (1);
	}
}

int	if_path(char *outfile, t_tree *tree)
{
	char	*tmp;
	int		i;

	i = ft_strlen(outfile) - 1;
	while (outfile[i] != '/')
		i--;
	tmp = malloc(i + 1);
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, outfile, i + 1);
	if (check_dir_out(tmp) == 1)
		return (free(tmp), 1);
	else
	{
		file_error(outfile, "no such file or directory", tree);
		return (free(tmp), 0);
	}
}

int	exit_handler(t_tree *tree)
{
	if (tree->pipes_num == 1)
		ft_printf("exit\n");
	if (tree->args[1])
		chk_exarg(tree, tree->args);
	return (tree->exit_status);
}
