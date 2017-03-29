/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 11:05:29 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/24 18:14:26 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static  int ft_parse_cd_bis(char *av, char ***env_bis, int flag)
{
    if ((ft_strncmp(av, "..", ft_strlen(av))) == 0)
        ft_pwd_n_oldpwd(env_bis, NULL, 0);
    else
        ft_add_pwd_n_oldpwd(env_bis, av, flag);
    return (1);

}

int			ft_parse_cd(char ***env_bis, char *av)
{
    char	*tmp;
    int		flag;

    flag = 0;
    if ((ft_strncmp(av, "-", 1)) == 0)
    {
        tmp = ft_oldpwd_or_home(env_bis, 0);
        if (tmp == NULL)
        {
            ft_error_env(av, 1);
            return (1);
        }
        if (chdir(tmp) < 0)
            ft_error_env(av, 1);
        free(tmp);
    }
    else
        if (chdir(av) < 0)
        {
            flag = 1;
            ft_error_env(av, 1);
        }
    return (ft_parse_cd_bis(av, env_bis, flag));
}

static  int ft_parse_setenv2(char **av, char ***env_bis)
{
    int		index;
    int     i;
    char	*str;

    i = -1;
    while (ft_strchr(av[++i], '$') == NULL)
        ;
    str = ft_env_without_bis(av, i, '$');
    if ((index = ft_getenv(str, *env_bis)) >= 0)
    {
        free(str);
        str = ft_env_without_bis(*env_bis, index, '=');
        *env_bis = ft_setenv(av[1], str, *env_bis);
        free(str);
        return (1);
    }
    else
    {
        ft_error_setenv(str, 3);
        return (1);
    }
    return (0);
}

static  int ft_parse_setenv(char *av)
{
    int	i;
    int	flag;

    i = -1;
    flag = 0;
    while (av[++i])
    {
        if (ft_isdigit(av[i]) == 1 && i == 0
                && ft_strncmp(av, "_", 1) != 0 && (flag = 1))
            break ;
        else if (ft_isalpha(av[i]) == 0 && i == 0
                && ft_strncmp(av, "_", 1) != 0 && (flag = 1))
            break ;
        else if (ft_isalnum(av[i]) == 0 && i > 0 && (flag = 2))
            break ;
    }
    if (flag == 1 || flag == 2)
    {
        ft_error_setenv(NULL, flag);
        return (1);
    }
    return (0);
}

int			ft_check_setenv(char **av, char ***env_bis)
{
    int	count;

    count = ft_count_av(av);
    if (count >= 4)
    {
        ft_putendl_fd("Error too few argument", 2);
        return (1);
    }
    else if (count == 1)
    {
        ft_print_env(*env_bis, 0);
        return (1);
    }
    else if (av[1] != NULL || av[2] != NULL)
    {
        if (ft_parse_setenv(av[1]) == 1)
            return (1);
        else if (av[2] != NULL && av[2][0] == '$')
        {
            if ((ft_parse_setenv2(av, env_bis)) == 1)
                return (1);
        }
    }
    return (0);
}
