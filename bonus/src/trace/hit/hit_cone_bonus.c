/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:55:57 by jungslee          #+#    #+#             */
/*   Updated: 2024/09/09 20:22:48 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structures_bonus.h"
#include "utils_bonus.h"
#include "trace_bonus.h"

t_discriminant	cal_discriminant_cone(t_cone *co, t_ray *ray)
{
	t_discriminant	dis;
	double			cos2;

	ft_memset(&dis, 0, sizeof(t_discriminant));
	cos2 = pow(co->height, 2) / (pow(co->height, 2) + co->radius2);
	dis.a = pow(vdot(ray->dir, co->normalize), 2) - cos2;
	dis.half_b = vdot(ray->dir, co->normalize) * \
			vdot(vminus(ray->orig, co->center), co->normalize) \
			- vdot(vminus(ray->orig, co->center), ray->dir) * cos2;
	dis.c = pow(vdot(vminus(ray->orig, co->center), co->normalize), 2) - \
			vlength2(vminus(ray->orig, co->center)) * cos2;
	dis.discriminant = (dis.half_b * dis.half_b) - (dis.a * dis.c);
	if (dis.discriminant >= 0)
		dis.sqrtd = sqrt(dis.discriminant);
	return (dis);
}

t_bool	is_root_valid_cone(t_hit_record *rec, t_ray *ray, \
		t_object *co_obj, double root)
{
	double			proj;
	t_cone			*co;
	t_hit_record	rec_tmp;
	double			len_cp;
	double			cos_cp_n;

	co = co_obj->element;
	rec_tmp = *rec;
	rec_tmp.t = root;
	rec_tmp.p = ray_at(ray, root);
	proj = vdot(vminus(rec_tmp.p, co->center), co->normalize);
	if (proj < 0 || proj > co->height)
		return (FALSE);
	*rec = rec_tmp;
	len_cp = vlength(vminus(rec->p, co->center));
	cos_cp_n = proj / len_cp;
	rec->normal = vunit(vminus(rec->p, \
				vplus(vmult(co->normalize, len_cp / cos_cp_n), co->center)));
	set_face_normal(ray, rec);
	rec->albedo = co_obj->albedo;
	return (TRUE);
}

t_bool	hit_cone_side(t_object *co_obj, t_ray *ray, t_hit_record *rec)
{
	t_cone			*co;
	t_discriminant	dis;
	double			root[2];
	t_bool			cond;
	int				i;

	i = 0;
	co = co_obj->element;
	dis = cal_discriminant_cone(co, ray);
	cond = FALSE;
	if (dis.discriminant < 0)
		return (FALSE);
	root[0] = ((-dis.half_b) + dis.sqrtd) / dis.a;
	root[1] = ((-dis.half_b) - dis.sqrtd) / dis.a;
	while (i < 2)
	{
		if ((root[i] > rec->tmin && root[i] < rec->tmax) && \
			is_root_valid_cone(rec, ray, co_obj, root[i]))
		{
				rec->tmax = root[i];
				cond = TRUE;
		}
		i++;
	}
	return (cond);
}

t_bool	hit_cone_cap(t_object *co_obj, t_ray *ray, \
			t_hit_record *rec, t_point3 center)
{
	t_cone			*co;
	t_hit_record	rec_tmp;
	double			root;
	double			r;

	co = co_obj->element;
	if (vdot(co->normalize, ray->dir) == 0)
		return (FALSE);
	root = vdot(vminus(center, ray->orig), co->normalize) \
				/ vdot(co->normalize, ray->dir);
	rec_tmp = *rec;
	rec_tmp.t = root;
	rec_tmp.p = ray_at(ray, root);
	r = vlength2(vminus(rec_tmp.p, center));
	if (!(root < rec->tmin || root > rec->tmax || root < 0) \
			&& (0 <= r && r <= co->radius2))
	{
		*rec = rec_tmp;
		rec->normal = co->normalize;
		set_face_normal(ray, rec);
		rec->albedo = co_obj->albedo;
		rec->tmax = root;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	hit_cone(t_object *co_obj, t_ray *ray, t_hit_record *rec)
{
	t_cone	*co;
	int		hit;

	co = co_obj->element;
	hit = 0;
	if (hit_cone_side(co_obj, ray, rec))
		hit++;
	if (hit_cone_cap(co_obj, ray, rec, vplus(co->center, \
			vmult(co->normalize, co->height))))
		hit++;
	if (hit != 0)
	{
		if (co_obj->bump.img.id)
			rec->normal = bump(co_obj, &co_obj->bump, rec);
		if (co_obj->texture.img.id)
			rec->albedo = texture(co_obj, &co_obj->texture, rec);
		else if (co_obj->is_checker == TRUE)
			rec->albedo = checkerboard(co_obj, rec);
		return (TRUE);
	}
	return (FALSE);
}
