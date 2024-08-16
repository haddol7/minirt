/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:35 by daeha             #+#    #+#             */
/*   Updated: 2024/08/16 16:42:19 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_object	*hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_hit_record	temp_rec;

	temp_rec = *rec;
	temp_rec.object = NULL;
	while (world)
	{
		if (hit_obj(world, ray, &temp_rec))
		{
			temp_rec.tmax = temp_rec.t;
			temp_rec.object = world;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (temp_rec.object);
}

t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec);
	return (hit_result);
}
