/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:46 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/29 14:52:46 by stvalett         ###   ########.fr       */
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
#include <pwd.h>
#include <fcntl.h>

/********************************************
 *              ENV                         *
 *******************************************/
char	**ft_cpy_env(char **env, int len, char *path);
char	**ft_setenv(const char *line, const char *value, char **env);
char	**ft_unsetenv(char *line, char *value, char **env_bis);
int		ft_getenv(char *line, char **env_bis);

/********************************************/

/********************************************
 *              ENV_TOOLS                   *
 *******************************************/
char	*ft_getpath(const char *line, const char *value);
void	ft_env_without(char **av, char **env_bis);
char    *ft_env_without_bis(char **env_bis, int index, char c);

/*******************************************/

/********************************************
 *              COMMANDS                    *
 *******************************************/
int		ft_cmd_echo(char **av, char **env_bis);
int		ft_cmd_unsetenv(char **av, char ***env);
int		ft_cmd_setenv(char **av, char ***env_bis);
int		ft_cmd_cd(char **av, char ***env_bis);
int		ft_cmd_env(char **av, char **env, char *line);

/*******************************************/

/********************************************
 *              PARSE_BUILT                 *
 *******************************************/
int     ft_check_setenv(char **av, char ***env_bis);
int		ft_parse_cd(char ***env_bis, char *av);
int     ft_check_env(char **av, char **env_bis, char *line);

/*******************************************/

/********************************************
 *              TOOLS_BUILT                 *
 *******************************************/
char	*ft_oldpwd_or_home(char ***env_bis, int flag);
int		ft_add_pwd_n_oldpwd(char ***env_bis, char *av, int flag);
char    *ft_pwd(char ***env_bis);
int		ft_pwd_n_oldpwd(char ***env_bis, char *path, int flag);

/*******************************************/

/********************************************
 *              UTILS                       *
 *******************************************/
char	*ft_get_home(char ***env_bis);
void	ft_check_dollar_n_acco(char **av, int *flag);
char    **ft_parse_av(char *line, char **av, char **env_bisi, int *ret);

/*******************************************/

/********************************************
 *              TOOLS                       *
 *******************************************/
int		ft_is_here(char *av, char c, int flag);
int		ft_no_digit(char *av);
int		ft_free(char **str, int flag);
int     ft_free_str(char *s1, char *s2, int flag);
char	*ft_strcpy_cara(char *av);
char    *ft_strcpy_acco(char *line);
char 	*ft_parse_acco(char *line, char **av, int flag);
int		ft_is_acco(char *line, int *flag);
int		ft_is_dollar_n_acco(char **av);
char	*ft_no_metachr(char *str);

/*******************************************/

/********************************************
 *              ERROR                       *
 ********************************************/
void	ft_error_dollar(char **av, char **env_bis);
void    ft_error_setenv(char *str, int flag);
void    ft_error_env(char *av, int flag);
int		ft_error_env_2(char **tab, int index, int ret);
int     ft_error_bracket(int count, char **av);


/*******************************************/

/********************************************
 *              PRINTS                      *
 *******************************************/
void	ft_print_env(char **env_bis, int flag);
int		ft_print_acco(char **av, int flag);
void	ft_print_dollar_n_acco(char **av, char **env_bis, int flag);
void	ft_print_dollar(char **av, char **env_bis);

/*******************************************/

int		ft_start_exec(char *line, char ***env_bis);
int     ft_cmd_execve(char **av, char **env_bis, char *line, int index);
int     ft_env_execve(char **av, char **env_bis);

#endif
