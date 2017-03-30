/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:59:27 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/30 15:17:21 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	char	*ft_error_dollar_bis(char *av, char **env_bis, int *index)
{
	char	*tmp;
	int		i;
	int		k;

	if ((tmp = (char *)malloc(sizeof(char ) * ft_strlen(av) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (av[i] == '$' && av[i])
		i++;
	k = 0;
	if (av[i] == '"')
	{
		free(tmp);
		return (NULL);
	}
	while (av[i] != ' ' && av[i])
	{
		tmp[k] = av[i];
		k++;
		i++;
	}
	tmp[k] = '\0';
	*index = ft_getenv(tmp, env_bis);
	return (tmp);
}

void			ft_error_dollar(char **av, char **env_bis)
{
	char	*tmp;
	int		i;
	int		index;

	i = 0;
	index = 0;
	while (av[++i])
		if ((ft_strchr(av[i], '$')) != NULL
				&& ft_no_digit(av[i]) == 0 && ft_strlen(av[i]) > 1)
		{
			tmp = ft_error_dollar_bis(av[i], env_bis, &index);
			if (tmp == NULL)
			{
				ft_putendl_fd("Illegal variable name.", 2);
				break ;
			}
			if (index < 0)
			{
				ft_error_setenv(tmp, 3);
				break ;
			}
			free(tmp);
		}
}

int				ft_error_bracket(int count, char **av, int flag)
{
	if (count % 2 == 1 && ft_is_dollar_n_acco(av) == 0)
	{
		ft_putstr_fd("Unmatched ", 2);
		if (flag == 1)
			ft_putchar_fd('"', 2);
		else
			ft_putchar_fd('\'', 2);
		ft_putchar_fd('.', 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	else if (ft_is_dollar_n_acco(av) == 1)
	{
		ft_putendl_fd("Illegal variable name.", 2);
		return (0);
	}
	return (1);
}

void			ft_error_setenv(char *str, int flag)
{
	if (flag == 1)
		ft_putendl_fd("setenv: Variable name must begin with a letter", 2);
	else if (flag == 2)
	{
		ft_putstr_fd("setenv: Variable name must contain", 2);
		ft_putendl_fd(" alphanumeric characters", 2);
	}
	else if (flag == 3)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Undefined variable", 2);
		free(str);
	}
}

int		ft_error_env_2(char	**tab, int index, int ret)
{
	int i;

	i = -1;
	if (index >= 1)
		ft_putstr_fd("env: ", 2);
	while (tab[++i])
	{
		ft_putstr_fd(tab[i], 2);
		ft_putchar_fd(' ', 2);
		if ((i == 0 || i == 1) && ret == 1)
			break;
	}
	if (index >= 1)
		ft_putendl_fd(": No such file or directory", 2);
	else
		ft_putendl_fd(": Command not found", 2);
	return (ft_free(tab, 0));
}

void    ft_error_env(char *av, int flag)
{
	struct stat info;

	stat(av, &info);
	if (flag == 0)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(av, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		if (S_IXUSR && S_ISDIR(info.st_mode))
		{
			ft_putstr_fd(av, 2);
			ft_putendl_fd(": Permission denied", 2);
		}
		else
		{
			ft_putstr_fd("cd: No such file or directory: ", 2);
			ft_putendl_fd(av, 2);
		}
	}
}
