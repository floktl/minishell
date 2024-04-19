/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:41:13 by fkeitel           #+#    #+#             */
/*   Updated: 2024/04/19 11:10:28 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
-------------------------------- INITIAL SETUP ---------------------------------
 */

//	header file
#ifndef MINISHELL_H
# define MINISHELL_H

/* ------------------------------- DEFINITIONS ------------------------------ */

# define MAX_COMMAND_LENGTH 1024
# define MAX_ARGS 64
# define MAX_HISTORY 100

/* -------------------------------- LIBRARIES ------------------------------- */

//	public libraries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
//	private	libraries
# include "libft/libft.h"

/* -------------------------------- VARIABLES ------------------------------- */


/* -------------------------------- STRUCTS --------------------------------- */

/*
---------------------------------- FUNCTIONS -----------------------------------
*/

//---------------------------- command functions -------------------------------

//	command.c

//----------------------------- error functions --------------------------------

//	error.c

//--------------------------- execution functions ------------------------------

//	execute.c
void	execute_command(char **args);

//---------------------------- parsing functions -------------------------------

//	parsing.c
void	parse_command(char *command, char **args);

//---------------------------- signal functions -------------------------------

//	signal.c
void	handle_signal(int signo);

#endif
