/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:30:07 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 21:32:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

double	check_hit_sp(t_sphere *sp, t_ray *ray, t_hit_record *rec, double *root)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	sqrtd;

	oc = vminus(ray->orig, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	*root = half_b * half_b - a * c;
	if (*root < 0)
		return (FALSE);
	sqrtd = sqrt(*root);
	*root = (-half_b - sqrtd) / a;
	if (*root < rec->tmin || rec->tmax < *root)
	{
		*root = (-half_b + sqrtd) / a;
		if (*root < rec->tmin || rec->tmax < *root)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	double		root;

	sp = sp_obj->element;
	if (check_hit_sp(sp, ray, rec, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	if (sp_obj->bump.img.id)
		rec->normal = bump_mapping(rec, sp, sp_obj->bump);
	if (sp_obj->is_checker)
		rec->albedo = texture_checkerboard(rec->p, sp);
	else if (sp_obj->texture.img.id)
		rec->albedo = texture(rec->p, sp, sp_obj->texture);
	else
		rec->albedo = sp_obj->albedo;
	return (TRUE);
}
