/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:46 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/01 14:54:23 by stvalett         ###   ########.fr       */
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

int		ft_cmd_env(char **av, char ***env);
int		ft_cmd_exec(char *line, char ***env);
int		ft_cmd_cd(char **av, char **env);
int		ft_cmd_setenv(char **av, char ***env);
int		ft_cmd_unsetenv(char **av, char ***env);
int		ft_cmd_echo(char **av, char **env_bis);
int		ft_get_env(char *line, char **env_bis);
int		ft_free(char **str, int flag);
int		ft_count_env(char **env);
int		ft_no_digit(char *av);
int		ft_print_one_dollar(char *av);
int		ft_count_av(char **av);
char	*ft_no_metachr(char *str);
char	*ft_strcpy_cara(char *av);
char	**ft_cpy_env(char **env, int len, char *path);
char	**ft_add_env(const char *line, const char *value, char **env);
char	**ft_setenv(const char *line, const char *value, char **env);
char	**ft_unsetenv(const char *line, const char *value, char **env);
char	**ft_get_av(char *line, char **env);
char	*ft_get_home(char **env);
char	*ft_nosplit(char **str);
void	ft_print_env(char **env_bis);
void	ft_check_dollar_n_acco(char **av, int *flag);
void	ft_print_acco(char **av, char **env_bis);
void	ft_print_dollar(char **av, char **env_bis);
void	ft_print_dollar_bis(char **av, char **env_bis);
void	ft_env_without(char **av, char **env_bis, int *flag);
void	ft_error_dollar(char **av, char **env_bis);
void	ft_error_acco(char **av);

#endif
