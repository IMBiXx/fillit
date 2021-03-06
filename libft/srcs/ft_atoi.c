/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 00:32:16 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/04 01:01:41 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	i;
	int	n;

	i = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	n = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_isdigit(*str))
		i = i * 10 + (*(str++) - '0');
	return (i * n);
}
