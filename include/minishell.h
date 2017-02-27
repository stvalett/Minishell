/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:46 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/24 17:08:45 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 *I must remove stdio.h
 */
#include <stdio.h>

#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>

int	ft_cmd_env(char **av, char ***env);
int	ft_cmd_exec(char *line, char ***env);
int	ft_cmd_cd(char **av, char **env);
int	ft_cmd_setenv(char **av, char ***env);
int	ft_cmd_unsetenv(char **av, char ***env);
int	ft_cmd_echo(char **av, char **env_bis);
int	ft_get_env(char *line, char **env);
char	*ft_no_metachr(char *str);
char	**ft_cpy_env(char **env, int len, char *path);
char	**ft_add_env(const char *line, const char *value, char **env);
char	**ft_setenv(const char *line, const char *value, char **env);
char	**ft_unsetenv(const char *line, const char *value, char **env);
char	**ft_get_av(char *line, char **env);
char	*ft_get_home(char **env);
int	ft_free(char **str, int flag);
int	ft_count_env(char **env);
void	ft_print_env(char **env_bis);
int	ft_check_dollar(char **av);
int	ft_is_dollar(char **av, char **env_bis);

#endif
