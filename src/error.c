/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:59:27 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/01 16:33:23 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ft_error_acco(char **av)
{
	char	*tmp;
	//int		i;
	//int		count;

	tmp = ft_nosplit(av);
	ft_putendl(tmp);
	free(tmp);
	/*while (av[++i])
	{
		tmp = ft_no_metachr(av[i]);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": command not found.", 2);
		free(tmp);
	}
	ft_putchar('\n');*/
}

static char	*ft_error_dollar_bis(char *av, char **env_bis, int *index)
{
	char	*tmp;
	int		i;
	int		k;

	if ((tmp = (char *)malloc(sizeof(char ) * ft_strlen(av) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (av[i] == '$')
		i++;
	k = 0;
	while (av[i] != ' ' && av[i])
	{
		tmp[k] = av[i];
		k++;
		i++;
	}
	tmp[k] = '\0';
	*index = ft_get_env(tmp, env_bis);
	return (tmp);
}

void	ft_error_dollar(char **av, char **env_bis)
{
	char	*tmp;
	int 	i;
	int		index;

	i = 0;
	index = 0;
	while (av[++i])
		if ((ft_strchr(av[i], '$')) != NULL && ft_no_digit(av[i]) == 0 && ft_strlen(av[i]) > 1)
		{
			tmp = ft_error_dollar_bis(av[i], env_bis, &index);
			if (index < 0)
			{
				ft_putstr_fd(tmp, 2);
				ft_putchar_fd(':', 2);
				ft_putendl_fd(" Undefined variable.", 2);
				free(tmp);
				break;
			}
			free(tmp);
		}
}
