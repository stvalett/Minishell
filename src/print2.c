#include "../include/minishell.h"

void    ft_print_pwd_n_oldpwd(char ***env_bis)
{
    char    *tmp;

    tmp = ft_oldpwd(env_bis);
    *env_bis = ft_setenv("OLDPWD", tmp, *env_bis);
    free(tmp);
    tmp = ft_pwd(env_bis);
    *env_bis = ft_setenv("PWD", tmp, *env_bis);
    free(tmp);
}

void    ft_printadd_pwd_n_oldpwd(char ***env_bis, char *av)
{
    char    *tmp;

    tmp = ft_add_pwd(env_bis, av);
    *env_bis = ft_setenv("PWD", tmp, *env_bis);
    free(tmp);
}
