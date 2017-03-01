/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:13:26 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/01 17:25:46 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_realloc(char *str, char *strbis)
{
	char		*tmp;
	static int	count;
	static int 	len_total;
	int			len;

	if (count == 0)
	{
		if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)) == NULL)
			return (NULL);
		ft_strcpy(tmp, str);
		len = ft_strlen(str);
		len_total += len;
	}
	else
	{
		if ((tmp = (char *)malloc(sizeof(char) * len_total + ft_strlen(strbis) + 1)) == NULL)
			return (NULL);
		ft_strncpy(tmp, strbis, len_total);
		ft_strncat(tmp, " ", 1);
		ft_strncat(tmp, str, ft_strlen(str));
		//ft_strncpy(tmp + len_total, str, ft_strlen(str));
		len = ft_strlen(strbis);
		len_total += len;
		tmp[len_total + ft_strlen(strbis) + 1] = '\0';
	}
	count++;
	return (tmp);
}

char	*ft_nosplit(char **str)
{
	int 	i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		tmp = ft_realloc(str[i], tmp);
		i++;
	}
	return (tmp);
}
