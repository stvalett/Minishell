/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:24 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/22 11:24:27 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_free(char **str, int flag)
{
  int i;

  i = 0;
  while (str[i])
  {
    free(str[i]);
    i++;
  }
  free(str);
  if (flag == 1)
    return (1);
  else
    return (0);
}
