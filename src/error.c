/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:59:27 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/27 17:01:38 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(char *tmp)
{
	ft_putstr_fd(tmp, 2);
	ft_putchar_fd(':', 2);
	ft_putendl_fd(" Undefined variable.", 2);
}
