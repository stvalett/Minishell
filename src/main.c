/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:31 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/02 17:41:17 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_get_prompt(char **env)
{
//  pid_t 	pid;
  int	ret;
  char	*line;
  char	**env_bis;

  env_bis = ft_cpy_env(env, 0, NULL);
  ft_putstr("Minishell $> ");
  get_next_line(0, &line);
  ret = ft_cmd_exec(line, &env_bis);
  ft_free(env_bis, 0);
  free(line);
  //waitpid(pid, NULL, 0);
  return (ret);
}

int	main(int ac, char **av, char **env)
{
  int	ret;

  ret = 0;
  if (ac > 0 && av != NULL)
    while ((ret = ft_get_prompt(env)) > 0)
		;
  return (0);
}
