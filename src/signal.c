/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 11:14:42 by stvalett          #+#    #+#             */
/*   Updated: 2017/04/04 16:13:07 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void			ft_handle_signal(int signum)
{
	if (signum)
	{
		ft_putchar('\n');
		ft_print_prompt(0);
	}
}

void			ft_handle_signal2(int signum)
{
	if (signum)
	{
		signal(SIGINT, SIG_IGN);
		ft_putchar('\n');
		return ;
	}
}

void			ft_handle_signal3(int signum)
{
	if (signum)
	{
		signal(SIGTERM, SIG_IGN);
		return ;
	}
}

static	void	ft_print_hour(void)
{
	time_t		time_sec;
	struct tm	now;

	time(&time_sec);
	now = *localtime(&time_sec);
	ft_putstr(" [");
	ft_putnbr(now.tm_hour);
	ft_putchar(':');
	ft_putnbr(now.tm_min);
	ft_putchar(':');
	ft_putnbr(now.tm_sec);
	ft_putstr("] ");
}

void			ft_print_prompt(int flag)
{
	char		host[256];

	gethostname(host, sizeof(host));
	ft_putstr(YELLOW);
	if (flag)
		ft_putstr("😃");
	else
		ft_putstr("😡");
	ft_print_hour();
	ft_putstr(RESET);
	ft_putstr(PINK);
	ft_putstr(host);
	ft_putstr(RESET);
	ft_putstr(RESET);
	if (flag)
		ft_putstr(BLUE);
	else
		ft_putstr(RED);
	ft_putstr("  Minishell $> ");
	ft_putstr(RESET);

}
