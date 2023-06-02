/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:49:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/06/02 14:30:52 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		str = readline(ft_path_and_username(&data));
		printf("%s", RESET);
		data.cmds = parser(lexer(NULL, str), &data);
		if (data.cmds)
		{
			ft_check_builtins(&data);
			ft_env_underscore(&data);
			if (data.cmds->builtin)
				data.cmds->builtin(&data);
			else
				printf("Not a builtin !\n");
		}
		ft_free((void **)&str);
	}
	free(str);
	exit(0);
}
