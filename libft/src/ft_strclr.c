/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 03:00:56 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 15:36:27 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_strclr(char *str)
{
	size_t i;

	if (!str)
		return ;
	i = ft_strlen(str);
	ft_memset((char *)str, '\0', i);
}
