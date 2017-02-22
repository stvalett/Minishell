#ifndef MINISHELL_H
# define MINISHELL_H

/*
*I must remove stdio.h
*
*/
#include <stdio.h>

#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>

int	ft_cmd_exec(char *line, char **env);
int	ft_get_env(char *line, char **env);
char	**ft_get_av(char *line, char **env);
int	ft_free(char **str, int flag);
int	ft_cmd_env(char **av, char **env);
#endif
