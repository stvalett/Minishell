#include "../include/minishell.h"

int	ft_cmd_env(char **av, char **env)
{
  int i;

  i = 0;
  if (av[2] == NULL)
  {
    while (env[i])
    {
      ft_putendl(env[i]);
      i++;
    }
  }
  return (1);
}
