/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:01:15 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 21:58:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_press_hook(int keycode, int x, int y, void *data_addr)
{
	t_data		*data;
	t_scene		*scene;
	t_object	*selected_obj;

	data = data_addr;
	data->engine->mouse.x = x;
	data->engine->mouse.y = y;
	data->engine->mouse.z = keycode;
	data->engine->press_count++;
	if (keycode == MOUSE_LEFT)
	{
		scene = data->scene;
		scene->rec = record_init();
		scene->ray = ray_primary(&scene->camera, ((double)x) / (scene->canvas.w - 1), ((double)y) / (scene->canvas.h - 1));
		selected_obj = hit(scene->world, &scene->ray, &scene->rec);
		if (selected_obj)
		{
			dprintf(2, "%f %f OK!\n", ((double)x) / (scene->canvas.w - 1), ((double)y) / (scene->canvas.h - 1));
		}
		else
			dprintf(2, "%f %f NO!\n", ((double)x) / (scene->canvas.w - 1), ((double)y) / (scene->canvas.h - 1));
		scene->selected_obj = selected_obj;
	}
	return (0);
}

int	mouse_drag_hook(int x, int y, void *data_addr)
{
	t_data		*data;
	t_camera	*cam;

	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	if (data->engine->mouse.z == MOUSE_RIGHT)
	{
		data->engine->mouse_delta.x = ((double)x - data->engine->mouse.x);
		data->engine->mouse_delta.y = -((double)y - data->engine->mouse.y);
	}
	else
		return (0);
	*cam = camera(data->scene, *data->engine);
	draw_ray_chunk(data->scene, data->engine);
	return (0);
}

int	mouse_release_hook(int keycode, int x, int y, void *data_addr)
{	
	t_data		*data;
	t_camera	*cam;

	data = (t_data *)data_addr;
	cam = &data->scene->camera;
	if (keycode != data->engine->mouse.z)
		return (0);
	if (keycode == MOUSE_RIGHT)
	{
		data->engine->rotate.x += -((double)y - data->engine->mouse.y);
		data->engine->rotate.y += ((double)x - data->engine->mouse.x);
		data->engine->mouse.z = 0;
		data->engine->mouse_delta.x = 0;
		data->engine->mouse_delta.y = 0;
	}
	*cam = camera(data->scene, *data->engine);
	if (--data->engine->press_count > 0)
		draw_ray_chunk(data->scene, data->engine);
	else
		draw_ray_orig(data->scene, data->engine);
	if (data->engine->press_count < 0)
		data->engine->press_count = 0;
	return (0);
}