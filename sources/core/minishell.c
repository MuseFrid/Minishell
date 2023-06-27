/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:49:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/06/26 18:01:20 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_if_cmds(t_data *data, char *str)
{
	add_history(str);
	ft_check_builtins(data);
	ft_env_underscore(data);
	if (data->cmds->builtin && data->cmds->next == NULL)
		data->cmds->builtin(data);
	ft_run_all_cmds(data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_data	data;

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
			ft_if_cmds(&data, str);
		ft_free((void **)&str);
	}
	exit(EXIT_SUCCESS);
}
