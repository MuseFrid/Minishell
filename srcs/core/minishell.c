/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:47:01 by aabda             #+#    #+#             */
/*   Updated: 2023/04/19 01:56:26 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_struct(t_data *data, char **envp)
{
	data->env = NULL;
	ft_getenv(data, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_env	*env;

	ft_init_struct(&data, envp);
	env = data.env;
	while (env)
	{
		printf("[%p] <- [%p] -> [%p] | %s\n", env->prev, env, env->next, env->value);
		env = env->next;
	}
	printf("\n========================\n\n");
	char *str = "COLORTERM";
	ft_ensure(&data, str);
	env = data.env;
	while (env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
