/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:49:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/06/14 16:31:33 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_data	data;
	int		fd[2];

	if (argc != 1)
		return (-1);
	(void)argv;
	ft_handler_signal();
	ft_init_struct(&data, envp);
	while (1)
	{
		printf("%s", BOLDYELLOW);
		str = readline(ft_path_and_username(&data));
		printf("%s", RESET);
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
