#include "../include/minishell.h"

int    ft_print_pwd_n_oldpwd(char ***env_bis)
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

int    ft_printadd_pwd_n_oldpwd(char ***env_bis, char *av)
{
    char    *tmp;

	if ((ft_strncmp(av, "-", 1)) == 0)
		return (0);
    tmp = ft_add_pwd(env_bis, av);
    *env_bis = ft_setenv("PWD", tmp, *env_bis);
    free(tmp);
    return (0);
}
