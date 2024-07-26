#include <stdio.h>
#include "structures.h"
#include "print.h"
#include "utils.h"

#include "scene.h"
#include "trace.h"

int main(void)
{
	int	i;
	int	j;
	double	u;
	double	v;
	t_color3 pixel_color;
	t_canvas canv;
	t_camera cam;
	t_ray	 ray;
	t_sphere sp;

	canv = canvas(400, 300);
	cam = camera(&canv, point3(0,0,0));
	sp = sphere(point3(0, 0, -5), 2);
	printf("P3\n%d %d\n255\n", canv.width, canv.height);
	j = canv.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			dprintf(2, "%d %d | ", i, j);
			ray = ray_primary(&cam, u, v);
			pixel_color = ray_color(&ray, &sp);
			write_color(pixel_color);
			i++;
		}
		dprintf(2, "=======\n");
		j--;
	}
	return (0);
}
