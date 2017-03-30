/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 13:00:29 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/30 13:02:52 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int     ft_tool_parse_env(char **av, char **cpy_env)
{
    char    *str;
    char    **tab_tmp;
    int     flag;

    flag = 0;
    str = ft_no_metachr(av[1]);
    if ((tab_tmp = (char **)malloc(sizeof(char *) * 3)) == NULL)
        exit (1);
    tab_tmp[0] = ft_strdup("");
    tab_tmp[1] = ft_strdup(str);
    tab_tmp[2] = NULL;
    free(str);
    flag = 1;
    if (ft_is_here(av[1], '=', 1) == 1 && av[1][1] == '$')
        return (ft_parse_env1(tab_tmp, cpy_env, flag));
    else 
    {
        if (ft_is_here(av[1], '=', 1) == 1)
            return (ft_parse_env2(tab_tmp, cpy_env, flag));
    }
    return (ft_free(cpy_env, 0));
}
