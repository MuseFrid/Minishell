/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:49:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/28 12:29:22 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_if_cmds(t_data *data, char *str)
{
	add_history(str);
	ft_check_builtins(data);
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
	ft_handler_signal(0);
	ft_init_struct(&data, envp);
	while (1)
	{
		data.heredoc->open_file = NULL;
		str = ft_prompt(&data);
		data.cmds = parser(lexer(NULL, str, 0), &data, NULL, NULL);
		if (data.cmds)
			ft_if_cmds(&data, str);
		lst_clear_cmds(data.cmds);
		if (data.heredoc->open_file)
		{
			unlink(data.heredoc->open_file);
			ft_free((void **)&data.heredoc->open_file);
		}
		ft_free((void **)&str);
	}
	exit(EXIT_SUCCESS);
}
