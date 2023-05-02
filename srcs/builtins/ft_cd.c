/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:31:37 by aabda             #+#    #+#             */
/*   Updated: 2023/05/02 15:13:19 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_data *data)
{
	(void)data;					// need to be delete in prod
	// char	*path;
	char	*path = "srcs/";	//	var for test (need to be delete in prod)

	// path = 					//	need to have the good value in the struct
	if (chdir(path) == -1)
		return (-1);			//	error
	return (0);
}
