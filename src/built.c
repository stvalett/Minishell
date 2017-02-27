#include "../include/minishell.h"

char	*ft_no_metachr(char *av)
{
  char		*str;
  char const	*start;
  char const	*end;

  start = NULL;
  if (!av)
    return (av);
  while (*av)
  {
    if (!(*av == '"'))
    {
      start = (start == NULL) ? av : start;
      end = av;
    }
    av++;
  }
  if (start == NULL)
    return (ft_strnew(1));
  if ((str = (char *)malloc(sizeof(*str) * (end - start) + 2)) == NULL)
    return (NULL);
  av = (char *)start;
  while (av <= end)
    *str++ = *av++;
  *str = '\0';
  return (str - (end - start + 1));

}
