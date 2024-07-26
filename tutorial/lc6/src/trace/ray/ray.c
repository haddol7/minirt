#include "trace.h"

t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

t_point3 ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray ray;

	ray.orig = cam->orig;
	// left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

t_color3    ray_color(t_ray *ray, t_sphere *sphere)
{
    double			t;
	// t_vec3			n;
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = INFINITY;
	if (hit_sphere(sphere, ray, &rec))
		return (vmult(vplus(rec.normal, color3(1,1,1)), 0.5));
    else {
        //ray의 방향벡터의 y 값을 기준으로 그라데이션을 주기 위한 계수.
        t = 0.5 * (ray->dir.y + 1.0);
        // (1-t) * 흰색 + t * 하늘색
        return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
    }
    // t = hit_sphere(sphere, ray);
    // if (t >= 0.0)
    // {
    //     //정규화 된 구 표면에서의 법선
    //     n = vunit(vminus(ray_at(ray, t), sphere->center));
	// 	dprintf(2, "%f %f %f\n", n.x, n.y, n.z);
    //     return (vmult(color3(n.x + 1, n.y + 1, n.z + 1), 0.5));
    // }
}
