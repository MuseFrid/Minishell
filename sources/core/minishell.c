/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:49:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/08/01 09:07:32 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_if_cmds(t_data *data, char *str)
{
	t_simple_cmds	*cmds;
	
	cmds = data->cmds;
	add_history(str);
	while (cmds)
	{
		ft_check_builtins(cmds);
		cmds = cmds->next;
	}
	ft_run_all_cmds(data, data->cmds);
	if (data->cmds)
		wait_child(data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_data	data;

	(void) argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	g_ret_val = 0;
	ft_init_struct(&data, envp);
	while (19)
	{
		ft_handler_signal(0);
		str = ft_prompt(&data);
		data.cmds = parser(lexer(NULL, str, 0), &data, NULL, NULL);
		if (data.cmds)
			ft_if_cmds(&data, str);
		free_before_new_cmds(&data, str);
	}
	exit(EXIT_SUCCESS);
}
