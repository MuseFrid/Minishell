/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:23:37 by aabda             #+#    #+#             */
/*   Updated: 2023/05/19 02:01:33 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmp_str_strict(const char *s1, const char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 == len_s2 && ft_strncmp(s1, s2, len_s1) == 0)
		return (0);
	return (1);
}

void	ft_free(void *value)
{
	free(value);
	value = NULL;
}
