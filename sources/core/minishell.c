/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:49:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/13 11:19:46 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_if_cmds(t_data *data, char *str, int fd[2])
{
	add_history(str);
	ft_check_builtins(data);
	ft_env_underscore(data);
	redirection_hub(data->cmds->redirections, data, fd);
	if (data->cmds->builtin)
		data->cmds->builtin(data);
	else
		printf("Not a builtin !\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_data	data;
	int		fd[2];

	if (argc != 1)
		exit(EXIT_FAILURE);
	(void)argv;
	ft_handler_signal();
	ft_init_struct(&data, envp);
	while (1)
	{
		str = ft_prompt(&data);
		data.cmds = parser(lexer(NULL, str), &data);
		if (data.cmds)
			ft_if_cmds(&data, str, fd);
		ft_free((void **)&str);
	}
	exit(EXIT_SUCCESS);
}
