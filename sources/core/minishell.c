/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:49:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/12 22:20:39 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	parsing(char *str, char **envp)
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
}*/

int build_exit(char *str)
{
	if (ft_strncmp(str, "exit", 5))
		return (0);
	return (printf("%sexit%s\n", BOLDRED, RESET));
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
	char 	*str;
	t_data	data;

	if (argc != 1)
		return (-1);
	(void) argv;
	ft_init_struct(&data, envp);
	while (1)
	{
		printf("%s", BOLDYELLOW);
		str = readline("minishell$ ");
		printf("%s", RESET);
		// if (build_exit(str))
		// 	break ;
		data.cmds = parser(lexer(NULL, str), &data);
		// print_parser(data.cmds);
		// print_tab(data.cmds);
		ft_check_builtins(&data);
		if (data.cmds->builtin)
			data.cmds->builtin(&data);
		else
			printf("Not a builtin !\n");
		free(str);
	}
	free(str);
	exit(0);
}
