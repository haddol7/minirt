/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:37:12 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 19:08:15 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

double	drandom(void)
{
	return ((float)rand() / (RAND_MAX));
}

double	drandom_(double min, double max)
{
	return (min + (max - min) * drandom());
}
