/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:47:01 by aabda             #+#    #+#             */
/*   Updated: 2023/04/29 20:26:14 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1)
		return (-1);
	(void)argv;
	ft_init_struct(&data, envp);
	while (1)
	{
		data.line = readline("Minishell$ ");
		if (ft_strncmp(data.line, "exit", 4) == 0)
			ft_exit(NULL);
		if (ft_strncmp(data.line, "env", 3) == 0)
			ft_env(&data);
		if (ft_strncmp(data.line, "$?", 2) == 0)
			printf("%d\n", data.err_return_val);
		if (ft_strncmp(data.line, "pwd", 3) == 0)
			ft_pwd(NULL);
		free(data.line);
	}
	free(data.line);
	return (data.err_return_val);
}
