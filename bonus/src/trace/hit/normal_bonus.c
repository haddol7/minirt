/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:46 by daeha             #+#    #+#             */
/*   Updated: 2024/09/07 18:51:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_bonus.h"

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	if (rec->front_face == FALSE)
		rec->normal = vmult(rec->normal, -1);
}
