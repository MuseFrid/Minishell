/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:49:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/06/14 16:56:27 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char 	*str;
	t_data	data;
	int	fd[2];

	if (argc != 1)
		return (-1);
	(void)argv;
	ft_init_struct(&data, envp);
	while (1)
	{
		ret_val = 0;
		str = readline("\033[1m\033[33mminishell$\033[0m ");
		errno = 0;
		data.cmds = parser(lexer(NULL, str), &data);
		if (data.cmds)
		{
			add_history(str);
			ft_check_builtins(&data);
			ft_env_underscore(&data);
			redirection_hub(data.cmds->redirections, &data, fd);
			if (data.cmds->builtin)
				data.cmds->builtin(&data);
			else
				printf("Not a builtin !\n");
		}
		ft_free((void **)&str);
	}
	ft_free((void **)&str);
	exit(0);
}
