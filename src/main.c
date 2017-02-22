#include "../include/minishell.h"

static int	ft_get_prompt(char **env)
{
  int	ret;
  char	*line;

  ret = 0;
  ft_putstr("Minishell $> ");
  get_next_line(0, &line);
  ret = ft_cmd_exec(line, env);
  free(line);
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
