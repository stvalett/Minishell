#include "../include/minishell.h"

static void	ft_get_replace(char **av, char **env)
{
  int	i;
  int	len;
  int	size_total;
  char	*str;

  len = ft_strlen((*av) + 1);
  if ((i = ft_get_env((*av) + 1, env)) > 0)
  {
    size_total = ft_strlen(env[i] + len);
    if ((str = (char *)malloc(sizeof(*str) * size_total + 1)) == NULL)
      exit(1);
    ft_strcpy(str, env[i] + len);
    free(*av);
    *av = str;
  }
}

char	**ft_get_av(char *line, char **env)
{
  char	**av;
  int	i;

  av = ft_strsplit(line, ' ');
  if (av == NULL)
    ft_putendl_fd("av == NULL", 2);
  else
  {
    i = 0;
    while (av[i])
    {
      if (av[i][0] == '$')
	ft_get_replace(&av[i], env);
      i++;
    }
  }
  return (av);
}
