/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:53:06 by aabda             #+#    #+#             */
/*   Updated: 2023/04/28 23:32:52 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_struct(t_data *data, char **envp)
{
	data->err_return_val = 0;
	data->env = NULL;
	ft_getenv(data, envp);
}
