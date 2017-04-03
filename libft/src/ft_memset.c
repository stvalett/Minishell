/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:32:10 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 15:47:43 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;
	int				i;

	tmp = (unsigned char *)b;
	i = 0;
	while (i < (int)len)
	{
		tmp[i] = c;
		i++;
	}
	return (b);
}
