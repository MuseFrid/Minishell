/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:38:11 by aabda             #+#    #+#             */
/*   Updated: 2023/08/01 13:34:56 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		if (data->hidden_env->pwd)
		{
			printf("%s\n", data->hidden_env->pwd);
			return (0);
		}
		perror("pwd: error retrieving current directory: \
getcwd: cannot access parent directories");
		return (1);
	}
	else
	{
		printf("%s\n", path);
		ft_free((void **)&path);
	}
	return (0);
}
