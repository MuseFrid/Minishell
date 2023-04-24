/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:49:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/24 15:32:27 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parsing(char *str, char **envp)
{
	int	i;

	(void) envp;
	i = 0;
	while (str[i])
	{	
		if (str[i] == '\'' && str[i + 1] == '\'')
		{
			printf("ui\n");
			i += 2;
		}
		else if (str[i] == ' ' && ++i)
			while (str[i] == ' ')
				i++;
		else
			i++;
	}
	printf("%d\n", chdir(str));
	//printf("%s\n", parse(envp, str));
	char *buf;
	buf = (char *)malloc(sizeof(char) * 1000);
	printf("%s\n", getcwd(buf, 100));
}

int build_exit(char *str)
{
	if (ft_strncmp(str, "exit", 5))
		return (0);
	return (printf("exit\n"));
}

void sig_handler(int signo)
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGKILL)
        printf("received SIGKILL\n");
    else if (signo == SIGSTOP)
        printf("received SIGSTOP\n");
}

int	main(int argc, char **argv, char **envp)
{
	char *str;
	//char *test;
	
	(void) argc;
	(void) argv;
	(void) envp;
	 /*if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        printf("Error\ncan't catch SIGUSR1\n");
    if (signal(SIGKILL, sig_handler) == SIG_ERR)
        printf("Error\ncan't catch SIGKILL\n");
    if (signal(SIGSTOP, sig_handler) == SIG_ERR)
        printf("Error\ncan't catch SIGSTOP\n");*/
	//init_mini();
	//init global_variable + everything we need.
	while (1)
	{
		str = readline("microshell$ ");
		if (build_exit(str))
			break ;
		//parsing(str, envp);
		lexer(NULL, str);
		free(str);
	}// if we are out free everything.
	free(str);
	return (0);
}
		

//errno = 10;
//write(2, strerror(errno), strlen(strerror(errno)));
//perror("Error in while");
