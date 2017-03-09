#include "../include/minishell.h"


int		ft_pwd_n_oldpwd_bis(char ***env_bis, char *path)
{
	char	*tmp;
	
	tmp = ft_oldpwd(env_bis);
	*env_bis = ft_setenv("OLDPWD", tmp, *env_bis);
	free(tmp);
	*env_bis = ft_setenv("PWD", path, *env_bis);
	return (0);
}

int    ft_pwd_n_oldpwd(char ***env_bis)
{
    char    *tmp;

    tmp = ft_oldpwd(env_bis);
    *env_bis = ft_setenv("OLDPWD", tmp, *env_bis);
    free(tmp);
    tmp = ft_pwd(env_bis);
    *env_bis = ft_setenv("PWD", tmp, *env_bis);
    free(tmp);
    return (0);
}

int    ft_add_pwd_n_oldpwd(char ***env_bis, char *av, int flag)
{
    char    *tmp;

	if ((ft_strncmp(av, "-", 1)) == 0)
	{
		ft_switch_pwd(env_bis);
		return (0);
	}
	else if (flag == 1)
		return (0);
	tmp = ft_oldpwd(env_bis);
	*env_bis = ft_setenv("OLDPWD", tmp, *env_bis);
	free(tmp);
    tmp = ft_add_pwd(env_bis, av);
    *env_bis = ft_setenv("PWD", tmp, *env_bis);
    free(tmp);
    return (0);
}
