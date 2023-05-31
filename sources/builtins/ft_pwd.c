/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:38:11 by aabda             #+#    #+#             */
/*   Updated: 2023/05/31 19:56:00 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	*path;

	(void)data;
	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	printf("%s\n", path);
	ft_free((void **)&path);
	return (0);
}
