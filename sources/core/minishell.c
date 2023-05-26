/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:49:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/26 15:26:00 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void sig_handler(int signo)
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGKILL)
        printf("received SIGKILL\n");
    else if (signo == SIGSTOP)
        printf("received SIGSTOP\n");
}*/

int	main(int argc, char **argv, char **envp)
{
	char 	*str;
	t_data	data;

	if (argc != 1)
		return (-1);
	(void) argv;
	ret_val = 0;
	ft_init_struct(&data, envp);
	while (1)
	{
		str = readline("\033[1m\033[33mminishell$\033[0m ");
		printf("%d\n", errno);
		errno = 0;
		data.cmds = parser(lexer(NULL, str), &data);
		ft_check_builtins(&data);
		//if (data.cmds->builtin)
		//	data.cmds->builtin(&data);
		//else
		//	printf("Not a builtin !\n");
		free(str);
	}
	free(str);
	exit(ret_val);
}
