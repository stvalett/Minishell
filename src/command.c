/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:23:52 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/08 17:24:33 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmd_echo(char **av, char **env_bis)
{
    int 	i;
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
            {
                i = 0;
                while (av[++i])
                {
                    ft_putstr(av[i]);
                    ft_putchar(' ');
                }
                ft_putchar('\n');
            }
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
        ft_putendl_fd("Error too few argument", 2);
    return (1);
}

int	ft_cmd_setenv(char **av, char ***env)
{
    if (av[1] != NULL)
    {
        if (av[2] != NULL)
            *env = ft_setenv(av[1], av[2], *env);
        else
            *env = ft_setenv(av[1], "", *env);
    }
    else
        ft_putendl_fd("Error too few argument", 2);
    return (1);
}

static char	*ft_getpwd(char ***env_bis)
{
	int 	i;
	int		j;
	int		index;
	char	*tmp;

	index = ft_get_env("PWD", *env_bis);
	if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(env_bis[0][index] + 1)))) == NULL)
		return (NULL);
	i = 0;
	while (env_bis[0][index][i] && env_bis[0][index][i] != '=')
		i++;
	i++;
	j = 0;
	while (env_bis[0][index][i])
	{
		tmp[j] = env_bis[0][index][i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	ft_cmd_cd(char **av, char ***env_bis)
{
    char		*path;
	char		*tmp;
	char		tmp2[1024];
	static char	*test;
	static int count;

	tmp = ft_getpwd(env_bis);
	getcwd(tmp2, sizeof(tmp2));
	test = tmp2;
	ft_putendl(test);
    if (av[1] != NULL)
    {
        path = av[1];
		ft_putnbr(count);
		ft_putchar('\n');
		if ((ft_strncmp(path, "-", 1)) == 0 && count % 2 == 1)
		{
			ft_putendl("HELLO");
			if(chdir(tmp) < 0)
				ft_print_error(av[1]);
		}
		else if ((ft_strncmp(path, "-", 1)) == 0 && count % 2 == 0)
		{
			ft_putendl("BONJOUR");
			if(chdir(test) < 0)
				ft_print_error(av[1]);
		}
		else 
		{
			if (chdir(path) < 0)
				ft_print_error(av[1]);
		}
        if ((ft_strncmp(av[1], "..", ft_strlen(av[1]))) == 0)
            ft_print_pwd_n_oldpwd(env_bis);
        else
            ft_printadd_pwd_n_oldpwd(env_bis, av[1]);
    }
    else
		if ((path = ft_get_home(*env_bis)) != NULL && chdir(path) < 0)
			ft_print_error(av[1]);
	count++;
	free(tmp);
    return (1);
}

int	ft_cmd_env(char **av, char ***env_bis)
{
    if (av[1] != NULL)
        ft_putendl_fd("Error env", 2);
    else
        ft_print_env(*env_bis);
    return (1);
}
