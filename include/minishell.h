/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:46 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/22 11:24:48 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
*I must remove stdio.h
*
*/
#include <stdio.h>

#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>

int	ft_cmd_exec(char *line, char **env);
int	ft_get_env(char *line, char **env);
char	**ft_get_av(char *line, char **env);
int	ft_free(char **str, int flag);
int	ft_cmd_env(char **av, char **env);
#endif
