/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_at_strcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:04:52 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 15:19:00 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_at_strcpy(char *dest, const char *src, int index)
{
	int	j;

	j = 0;
	while (src[index])
	{
		dest[j] = src[index];
		j++;
		index++;
	}
	dest[j] = '\0';
	return (dest);
}
