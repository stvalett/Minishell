/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:46 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/24 11:14:44 by stvalett         ###   ########.fr       */
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
int		ft_cmd_exec(char *line, char ***env_bis);
int		ft_cmd_cd(char **av, char ***env_bis);
int		ft_cmd_setenv(char **av, char ***env_bis);
int		ft_cmd_unsetenv(char **av, char ***env);
int		ft_cmd_echo(char **av, char **env_bis);
int		ft_get_env(char *line, char **env_bis);
int		ft_free(char **str, int flag);
int		ft_count_env(char **env);
int		ft_no_digit(char *av);
int		ft_print_one_dollar(char *av);
int		ft_count_av(char **av);
int		ft_is_acco(char *line, int *flag);
int		ft_is_dollar_n_acco(char **av);
int     ft_check_setenv(char **av, char ***env_bis);
int     ft_parse_setenv(char *av);
int     ft_parse_setenv2(char **av, char ***env_bis);
int     ft_error_bracket(int count, char **av);
void	ft_switch_pwd(char ***env_bis);
char    *ft_env_without_bis(char **env_bis, int index);
char	*ft_getpath(const char *line, const char *value);
char    *ft_oldpwd_or_add(char ***env_bis);
char	*ft_oldpwd_or_home(char ***env_bis, int flag);
char    *ft_pwd(char ***env_bis);
char	*ft_no_metachr(char *str);
char	*ft_strcpy_cara(char *av);
char	**ft_cpy_env(char **env, int len, char *path);
char	**ft_setenv(const char *line, const char *value, char **env);
char	**ft_unsetenv(char *line, char *value, char **env_bis);
char	**ft_get_av(char *line, char **env);
char	*ft_get_home(char ***env_bis);
char    *ft_strcpy_acco(char *line);
int		ft_add_pwd_n_oldpwd(char ***env_bis, char *av, int flag);
int		ft_pwd_n_oldpwd(char ***env_bis);
int		ft_pwd_n_oldpwd_bis(char ***env_bis, char *path);
int		ft_print_acco(char **av, int flag);
void	ft_print_error(char *av);
void	ft_print_env(char **env_bis, int flag);
void	ft_check_dollar_n_acco(char **av, int *flag);
void	ft_print_dollar(char **av, char **env_bis);
void	ft_print_dollar_n_acco(char **av, char **env_bis, int flag);
void	ft_env_without(char **av, char **env_bis);
void	ft_error_dollar(char **av, char **env_bis);
void    ft_error_setenv(char *str, int flag);
char 	*ft_parse_acco(char *line, char **av, int flag);

#endif
