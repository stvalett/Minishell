/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:23:52 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/29 16:19:23 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmd_echo(char **av, char **env_bis)
{
    int	flag;

    flag = 0;
    if (av[0] != NULL)
    {
        if (av[1] != NULL)
        {
            ft_check_dollar_n_acco(av, &flag);
            if (flag == 1)
                ft_print_dollar(av, env_bis);
            else if (flag == 2)
                ft_print_dollar_n_acco(av, env_bis, flag);
            else if (flag == 3)
                ft_print_acco(av, flag);
            else
                ft_print_env(av, 1);
        }
    }
    return (1);
}

int	ft_cmd_unsetenv(char **av, char ***env)
{
    if (av[1] != NULL)
    {
        if (av[2] != NULL)
            *env = ft_unsetenv(av[1], av[2], *env);
        else
            *env = ft_unsetenv(av[1], "", *env);
    }
    else
        ft_putendl_fd("setenv: Too many arguments", 2);
    return (1);
}

int	ft_cmd_setenv(char **av, char ***env_bis)
{
    if (ft_check_setenv(av, env_bis) == 0)
    {
        if (av[1] != NULL)
        {
            if (av[2] != NULL)
                *env_bis = ft_setenv(av[1], av[2], *env_bis);
            else
                *env_bis = ft_setenv(av[1], "", *env_bis);
        }
    }
    return (1);
}

int	ft_cmd_cd(char **av, char ***env_bis)
{
    char		    *path;
    uid_t           uid;
    struct passwd   *user;

    uid = getuid();
    user = getpwuid(uid);
    if (av[1] != NULL)
        ft_parse_cd(env_bis, av[1]);
    else
    {
        if ((path = ft_get_home(env_bis)) != NULL && chdir(path) < 0)
            ft_error_env(av[1], 1);
        if (path != NULL)
        {
            ft_pwd_n_oldpwd(env_bis, path, 1);
            free(path);
        }
        else
        {
            chdir(user->pw_dir);
            ft_pwd_n_oldpwd(env_bis, user->pw_dir, 1);
        }
    }
    return (1);
}

int	ft_cmd_env(char **av, char **env_bis, char *line)
{
    if (av[1] != NULL)
	{
        if (ft_check_env(av, env_bis, line) == 1)
            return (1);
	}
    else
        ft_print_env(env_bis, 0);
    return (1);
}
