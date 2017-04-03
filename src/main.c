/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:24:31 by stvalett          #+#    #+#             */
/*   Updated: 2017/03/31 11:17:14 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	ft_shlv_bis(char ***env_bis, int *add)
{
	int		i;
	int		index;
	char	*tmp;
	char	*tmp2;

	index = ft_getenv("SHLVL", *env_bis);
	if ((tmp = (char *)malloc(sizeof(char)
					* (ft_strlen(env_bis[0][index] + 1)))) == NULL)
		return ;
	ft_strcpy(tmp, env_bis[0][index]);
	i = ft_strlen(tmp) - 1;
	if ((tmp2 = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1))) == NULL)
		return ;
	while (tmp[i] != '=' && i >= 0 && tmp[i])
		i--;
	i++;
	ft_at_strcpy(tmp2, tmp, i);
	*add = ft_atoi(tmp2);
	free(tmp);
	free(tmp2);
}

static	void	ft_shlv(char ***env_bis)
{
	int			add;
	static int	count;
	char		*ret;

	add = 0;
	ret = NULL;
	if (count == 0)
	{
		ft_shlv_bis(env_bis, &add);
		ret = ft_itoa(count + add + 1);
		*env_bis = ft_setenv("SHLVL", ret, *env_bis);
		free(ret);
	}
	else
	{
		ret = ft_itoa(count + add);
		*env_bis = ft_setenv("SHLVL", ret, *env_bis);
		free(ret);
	}
	count++;
}

static	int		ft_get_prompt(char ***env_bis)
{
	int			ret;
	char		*line;

	line = NULL;
	ret = 0;
	signal(SIGINT, ft_handle_signal);
	ft_putstr("Minishell $> ");
	get_next_line(0, &line);
	if (line != NULL)
	{
		ret = ft_start_exec(line, env_bis);
		free(line);
	}
	return (ret);
}

static void		ft_basic_env(char ***env_bis)
{
	uid_t			uid;
	struct passwd	*user;
	char			str[1024];

	uid = getuid();
	user = getpwuid(uid);
	getcwd(str, sizeof(str));
	*env_bis = ft_setenv("HOME", user->pw_dir, *env_bis);
	*env_bis = ft_setenv("PWD", str, *env_bis);
	*env_bis = ft_setenv("SHLVL", "0", *env_bis);
}

int				main(int ac, char **av, char **env)
{
	int			ret;
	char		**env_bis;

	ret = 0;
	env_bis = ft_cpy_env(env, 0, NULL);
	if (*env_bis == NULL)
		ft_basic_env(&env_bis);
	ft_shlv(&env_bis);
	if (ac > 0 && av != NULL)
		while ((ret = ft_get_prompt(&env_bis)) > 0)
			;
	return (0);
}
