#include <stdio.h>
#include <mlx.h>
#include "structures.h"
#include "print.h"
#include "utils.h"

#include "scene.h"
#include "trace.h"

t_scene *scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka;

    if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
        return (NULL);
    scene->canvas = canvas(400, 300);
    scene->camera = camera(&scene->canvas, point3(0, 0, 0));

    world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0));
    oadd(&world, object(SP, sphere(point3(0, -1000, 0), 995), color3(1, 1, 1)));
    oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
    scene->world = world;
    lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
    scene->light = lights;
    ka = 0.1;
    scene->ambient = vmult(color3(1,1,1), ka);
    return (scene);
}

int     main(void)
{
    int         i;
    int         j;
    double      u;
    double      v;
    t_color3    pixel_color;
    t_scene     *scene;

    scene = scene_init();
    printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
    j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {	
			pixel_color = vec3(0, 0, 0);
			for (int sample = 0; sample < scene->camera.samples_per_pixel; sample++)
			{	
            	u = ((double)i + random_double_(-1, 1)) / (scene->canvas.width - 1);
            	v = ((double)j + random_double_(-1, 1)) / (scene->canvas.height - 1);
            	scene->ray = ray_primary(&scene->camera, u, v);
            	pixel_color = ray_color(scene, pixel_color);
			}
            write_color(pixel_color);
            ++i;
        }
        --j;
    }
    return (0);
}