/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:31 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/24 17:07:08 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_get_prompt(char ***env_bis)
{
//  pid_t 	pid;
  int	ret;
  char	*line;

  ft_putstr("Minishell $> ");
  get_next_line(0, &line);
  ret = ft_cmd_exec(line, env_bis);
  free(line);
  //waitpid(pid, NULL, 0);
  return (ret);
}

int	main(int ac, char **av, char **env)
{
  int	ret;
  char	**env_bis;

  ret = 0;
  env_bis = ft_cpy_env(env, 0, NULL);
  if (ac > 0 && av != NULL)
    while ((ret = ft_get_prompt(&env_bis)) > 0)
		;
  return (0);
}
