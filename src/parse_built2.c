#include "../include/minishell.h"

int ft_parse_env2(char **av, char **cpy_env, int flag)
{
    int     index;
    char    *s1;
    char    *s2;

    s1 = ft_strcpy_to(av[1], '=', 0);
    if (ft_is_here(av[1], '$', 1) == 1)
        s2 = ft_env_without_bis(av, 1, '$');
    else
        s2 = ft_env_without_bis(av, 1, '=');
    if ((index = ft_getenv(s2, cpy_env)) >= 0)
    {
        free(s2);
        s2 = ft_env_without_bis(cpy_env, index, '=');
    }
    cpy_env = ft_setenv(s1, s2, cpy_env);
    ft_print_env(cpy_env, 0);
    ft_free_str(s1, s2, 1);
    if (flag == 1)
        return (ft_free(av, 1), ft_free(cpy_env, 1));
    return (ft_free(cpy_env, 1));
}

int ft_parse_env1(char **av, char **cpy_env, int flag)
{
    int     index;
    char    *tmp;
    char    *s1;
    char    *s2;

    s1 = NULL;
    if ((tmp = (char *)malloc(sizeof(char) * (ft_strlen(av[1]) + 1))) == NULL)
        return (0);
    ft_at_strcpy(tmp, av[1], 1);
    if ((index = ft_getenv(tmp, cpy_env)) >= 0)
    {
        free(tmp);
        s1 = ft_env_without_bis(cpy_env, index, '=');
    }
    s2 = ft_env_without_bis(av, 1, '=');
    cpy_env = ft_setenv(s1, s2, cpy_env);
    ft_print_env(cpy_env, 0);
    ft_free_str(s1, s2, 1);
    if (flag == 1)
        return (ft_free(av, 1), ft_free(cpy_env, 1));
    return (ft_free(cpy_env, 1));
}

static void  ft_check_env_bis(char **av, char **env_bis, char *line)
{
    if (ft_strncmp(av[1], "-i", 2) == 0)
    {
        if (av[1] != NULL && (ft_strncmp(av[2], "echo", 4) == 0
                    || ft_strcmp(av[2], "\"echo\"") == 0
                    || ft_strcmp(av[2], "\'echo\'") == 0))
        {
            ft_cmd_echo(av + 2, env_bis);
            exit(0);
        }
        if ((ft_cmd_execve(av, env_bis, line, 2)) == 0)
            exit(1);
        exit(0);
    }
    else
    {
        if ((ft_cmd_execve(av, env_bis, line, 1)) == 0)
            exit(1);
        exit(0);
    }
}

static int         ft_parse_env(char **av, char **env_bis)
{
    char    **cpy_env;
    int     flag;

    flag = 0;
    cpy_env = ft_cpy_env(env_bis, 0, NULL);
    if (av[1] && av[2] != NULL)
        return (ft_free(cpy_env, 0));
    if (av[1] && av[2] == NULL)
    {
        if (ft_is_here(av[1], '"', 1) == 1 || ft_is_here(av[1], '\'', 1) == 1)
        {
            flag = 1;
            return (ft_tool_parse_env(av, cpy_env));
        }
        else
        {
            if (ft_is_here(av[1], '=', 1) == 1 && av[1][0] == '$')
                return (ft_parse_env1(av, cpy_env, flag));
            else if (ft_is_here(av[1], '=', 1) == 1)
                    return (ft_parse_env2(av, cpy_env, flag));
        }
    }
    return (ft_free(cpy_env, 0));
}

int         ft_check_env(char **av, char **env_bis, char *line)
{
    pid_t   pid;

    if (ft_parse_env(av, env_bis) == 1)
        return (1);
    if (av[1] && (ft_strncmp(av[1], "echo", 4) == 0
                || ft_strcmp(av[0], "\"echo\"") == 0
                || ft_strcmp(av[0], "\'echo\'") == 0))
        return (ft_cmd_echo(av + 1, env_bis));
    if (av[1])
    {
        pid = fork();
        if (pid > 0)
            waitpid(pid, NULL, 0);
        if (pid == 0)
            ft_check_env_bis(av, env_bis, line);
    }
    return (1);
}
