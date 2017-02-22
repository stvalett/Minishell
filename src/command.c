/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:23:52 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/22 11:23:54 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmd_env(char **av, char **env)
{
	int i;

	i = 0;
	if (av[1] != NULL)
		ft_putendl_fd("Error env", 2);
	else
	{
		while (env[i])
		{
			ft_putendl(env[i]);
			i++;
		}
	}
	return (1);
}
