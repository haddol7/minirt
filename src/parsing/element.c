#include "../../inc/map.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
}

int	count_split_words(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

t_point3	check_coordinate(char *coor)
{
	double	x;
	double	y;
	double	z;
	char	**split;

	split = ft_split(coor, ',');
	if (count_split_words(split) != 3)
		error_exit("not a complete coordinate\n");
	x = ft_atof(split[0]);
	y = ft_atof(split[1]);
	z = ft_atof(split[2]);
	// if (split[3] != NULL)
	// 	error_exit("check_coordinate\n");
	free_split(split);
	return (point3(x, y, z));
}

int	is_in_valid_normalize_range(double x, double y, double z)
{
	if (!(-1.0 <= x && x <= 1.0))
		return (0);
	if (!(-1.0 <= y && y <= 1.0))
		return (0);
	if (!(-1.0 <= z && z <= 1.0))
		return (0);
	return (1);
}

t_vec3	check_normalize_vector(char *coor)
{
	double	x;
	double	y;
	double	z;
	char	**split;

	split = ft_split(coor, ',');
	if (count_split_words(split) != 3)
		error_exit("not a complete vector\n");
	x = ft_atof(split[0]);
	y = ft_atof(split[1]);
	z = ft_atof(split[2]);
	if (is_in_valid_normalize_range(x, y, z) == 0)
		error_exit("not_valid_normalize_vector\n");
	// if (split[3] != NULL)
	// 	error_exit("check_normalize vector\n");
	free_split(split);
	return (vec3(x, y, z));
}

int	is_color_in_valid_range(double r, double g, double b)
{
	if (!(0.0 <= r && r <= 255.0))
		return (0);
	if (!(0.0 <= g && g <= 255.0))
		return (0);
	if (!(0.0 <= b && b <= 255.0))
		return (0);
	return (1);
}

int	is_valid_ratio_range(double ratio)
{
	if (!(0.0 <= ratio && ratio <= 1.0))
		return (0);
	return (1);
}

t_color3	check_color(char *color)
{
	double	r;
	double	g;
	double	b;
	char	**split;

	split = ft_split(color, ',');
	if (count_split_words(split) != 3)
		error_exit("not complete rgb\n");
	r = ft_atof(split[0]);
	g = ft_atof(split[1]);
	b = ft_atof(split[2]);
	if (is_color_in_valid_range(r, g, b) == 0)
		error_exit("not valid RGB range\n");
	// if (split[3] != NULL)
	// 	error_exit("check_color\n");
	free_split(split);
	return (color3(r, g, b));
}

t_object	*is_valid_sp(char **split, t_mlx engine)
{
	t_object	*sp;
	char		*texture;
	t_point3	center;
	t_color3	color;

	sp = NULL;
	center = check_coordinate(split[1]);
	color = check_color(split[3]);
	if (split[4] != NULL && split[4][0] != '\n')
	{
		texture = ft_strtrim(split[4], "\n");
		sp = object_texture(SP, sphere(center, ft_atof(split[2])), texture, engine.mlx);
		free(texture);
	}
	else if (split[4] == NULL || (split[4][0] == '\n' && split[5] == NULL))
		sp = object_default(SP, sphere(center, ft_atof(split[2])), color);
	else
		error_exit("check_is_valid_sp\n");
		//TODO 이미지 파일 검증 추가
	return (sp);
}

t_object	*is_valid_cy(char **split, t_mlx engine)
{
	t_object	*cy;
	char 		*texture;
	t_point3	center;
	t_vec3		normalize;
	t_color3	color;

	cy = NULL;
	center = check_coordinate(split[1]);
	normalize = check_normalize_vector(split[2]);
	color = check_color(split[5]);
	if (split[6] != NULL && split[6][0] != '\n')
	{
		texture = ft_strtrim(split[6], "\n");
		cy = object_texture(CY, cylinder(center, normalize, \
				ft_atof(split[3]), ft_atof(split[4])), texture, engine.mlx);
		free(texture);
	}
	else if (split[6] == NULL || (split[6][0] == '\n' && split[7] == NULL))
		cy = object_default(CY, cylinder(center, normalize, ft_atof(split[3]), ft_atof(split[4])), color);
	else
		error_exit("check_is_valid_sp\n");
	return (cy);
}

t_object	*is_valid_pl(char **split, t_mlx engine)
{
	t_object	*pl;
	char		*texture;
	t_point3	center;
	t_vec3		normalize;
	t_color3	color;

	pl = NULL;
	center = check_coordinate(split[1]);
	normalize = check_normalize_vector(split[2]);
	color = check_color(split[3]);
	if (split[4] != NULL &&  split[4][0] != '\n')
	{
		texture = ft_strtrim(split[4], "\n");
		pl = object_texture(PL, plane(center, normalize), texture, engine.mlx);
		free(texture);
	}
	else if (split[4] == NULL || (split[4][0] == '\n' && split[5] == NULL))
		pl = object_default(PL, plane(center, normalize), color);
	else
		error_exit("is_valid_pl\n");
				//TODO 이미지 파일 검증 추가
	return (pl);
}

t_object	*is_valid_A(char **split, t_scene *scene)
{
	static int	count = 0;
	
	scene->ka = ft_atof(split[1]);
	scene->ambient = vmult(check_color(split[2]), scene->ka);
	if (is_valid_ratio_range(scene->ka) == 0)
		error_exit("not_valid_ratio : ka");
	if (split[3] != NULL || count != 0)
		error_exit("is_valid_A\n");
	count++;
	return (0);
}

t_object	*is_valid_C(char **split, t_scene *scene)
{
	static int	count = 0;
	double		theta;
	double      viewport_height;

	scene->camera.lookat = point3(0, 0, -1);
	scene->camera.lookfrom = check_coordinate(split[1]);
	scene->camera.w = check_normalize_vector(split[2]);
	scene->camera.vfov = ft_atof(split[3]);
	scene->camera.vup = vec3(0, 1, 0);
    scene->camera.focal_len = 1;

	theta = scene->camera.vfov * (M_PI) / 180;
    viewport_height = tan(theta / 2) * 2 * scene->camera.focal_len;
    
	scene->camera.viewport_w = viewport_height * scene->canvas.aspect_ratio;
    scene->camera.viewport_h = viewport_height;
	
	scene->camera.u = vunit(vcross(scene->camera.vup, scene->camera.w));
	dprintf(2, "1\n");
	scene->camera.v = vcross(scene->camera.w, scene->camera.u);
    scene->camera.orig = scene->camera.lookfrom;
    scene->camera.horizontal = vmult(scene->camera.u, scene->camera.viewport_w);
    scene->camera.vertical = vmult(scene->camera.v, scene->camera.viewport_h);
	scene->camera.left_bottom = vminus(vminus(scene->camera.orig, vmult(scene->camera.w, scene->camera.focal_len)), vplus(vdivide(scene->camera.vertical, 2), vdivide(scene->camera.horizontal, 2)));
	scene->camera.samples_per_pixel = ANTI_SAMPLE;
	
	if (split[4] != NULL || count != 0)
		error_exit("is_valild_c\n");
	count++;
	return (0);
}

t_object	*is_valid_L(char **split, t_scene *scene)
{
	static int	count = 0;
	t_point3	point;
	t_color3	color;
	double		ratio;
	t_object	*light;

	point = check_coordinate(split[1]);
	ratio = ft_atof(split[2]);
	color = check_color(split[3]);
	if (is_valid_ratio_range(ratio) == 0)
		error_exit("not_valid_ratio_range : light ratio");
	if (split[4] != NULL || count != 0)
		error_exit("is_valid_L\n");//TODO 흠.. 라이트는 하나??
	light = object_default(LIGHT_POINT, light_point(point, color, ratio), color);
	scene->light = light;
	return (0);
}