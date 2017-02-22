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
