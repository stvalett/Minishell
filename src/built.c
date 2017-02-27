/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 10:45:17 by stvalett          #+#    #+#             */
/*   Updated: 2017/02/27 17:22:35 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_dollar_n_acco(char **av, int *flag)
{
	int count;
	int	count2;
	int i;

	i = -1;
	count = 0;
	count2 = 0;
	while (av[++i])
	{
		if ((ft_strchr(av[i], '$')) != NULL)
			count++;
		if ((ft_strchr(av[i], '"')) != NULL)
			count2++;
	}
	if (count >= 1 && count2 >= 1)
		*flag = 2;
	else if(count >= 1 && !count2)
		*flag = 1;
	else if (count2 >= 1 && !count)
		*flag = 3;
	else
		*flag = 0;
}

/*int		ft_is_dollar(char **av, char **env_bis)
  {
  int 	i;
  int		count;
//char	*tmp;

i = 0;
count = 0;
env_bis = (char **)env_bis;
count = ft_check_acco(av);
while (av[++i])
{
if (count % 2 == 1)
{
ft_putendl("Unmatched \".");
return (1);
}
if (count % 2 != 1)
{
ft_putendl("HEY");
tmp = ft_print_acco(av[i]);
ft_putstr(tmp);
ft_putchar(' ');
free(tmp);
}
if (av[i][0] == '$' && ft_isalnum(av[i][1]) == 1)
write(1, "\n", 1);
}
return (0);
}*/

/*int	ft_is_dollar(char **av, char **env_bis)
  {
  int 	i;
  int		k;
  int		j;
  char	*tmp;

  i = 0;
  while (av[++i])
  if (av[i][0] == '$' && av[i][1] != '\0')
  {
  if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(av[i]))) == NULL)
  return (-1);
  k = -1;
  j = 0;
  while (av[i][++k])
  if (av[i][k] != '$')
  {
  tmp[j] = av[i][k];
  j++;
  }
  j = -1;
  while (env_bis[++j])
  if ((ft_strncmp(tmp, env_bis[j], ft_strlen(tmp))) == 0)
  {
  ft_putendl(env_bis[j]);
  free(tmp);
  return (1);
  }
  }
  else
  ft_print_no_dollar(av[i]);
  return (0);
  }*/

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
