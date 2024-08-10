/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:06:21 by gwagner           #+#    #+#             */
/*   Updated: 2024/08/10 18:00:25 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_destroy(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->textures[0])
		mlx_destroy_image(data->mlx, data->textures[0]);
	if (data->textures[1])
		mlx_destroy_image(data->mlx, data->textures[1]);
	if (data->textures[2])
		mlx_destroy_image(data->mlx, data->textures[2]);
	if (data->textures[3])
		mlx_destroy_image(data->mlx, data->textures[3]);
	if (data->textures[4])
		mlx_destroy_image(data->mlx, data->textures[4]);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data->map);
	exit(0);
	return (0);
}

void	init_textures(t_data *data)
{
	int	imgw;
	int	imgh;

	data->textures[0]
		= mlx_xpm_file_to_image(data->mlx,
			"./textures/ground.xpm", &imgw, &imgh);
	data->textures[1]
		= mlx_xpm_file_to_image(data->mlx, "./textures/wall.xpm", &imgw, &imgh);
	data->textures[2]
		= mlx_xpm_file_to_image(data->mlx,
			"./textures/collectable.xpm", &imgw, &imgh);
	data->textures[3]
		= mlx_xpm_file_to_image(data->mlx,
			"./textures/yoshi.xpm", &imgw, &imgh);
	data->textures[4]
		= mlx_xpm_file_to_image(data->mlx, "./textures/exit.xpm", &imgw, &imgh);
	check_textures(data);
}

void	put_map(t_data *data)
{
	int		i;
	int		t;
	t_map	*map;

	map = data->map;
	i = 0;
	while (map[i].type)
	{
		if (map[i].type == '0')
			t = 0;
		else if (map[i].type == '1')
			t = 1;
		else if (map[i].type == 'C')
			t = 2;
		else if (map[i].type == 'P')
			t = 3;
		else if (map[i].type == 'E')
			t = 4;
		if (map[i].type != '\n')
		{
			mlx_put_image_to_window(data->mlx, data->win,
				data->textures[t], map[i].x * 120, map[i].y * 120);
		}
		i++;
	}
}

void	put_win(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (data->map[i].type != '\n')
		i++;
	x = data->map[i].x;
	while (data->map[i].type != '\0')
		i++;
	y = data->map[i - 1].y + 1;
	data->win = mlx_new_window(data->mlx, 120 * x, 120 * y, "so_long");
	put_map(data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc == 2)
	{
		checkmapname(argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			perror("Error\nMake sure map exists!");
			exit(EXIT_FAILURE);
		}
		data.map = mapping(fd, &data);
		data.mlx = mlx_init();
		init_textures(&data);
		put_win(&data);
		mlx_hook(data.win, 2, 1L << 0, &movetest, &data);
		mlx_hook(data.win, 17, 1L << 17, &on_destroy, &data);
		mlx_loop(data.mlx);
	}
	else
	{
		perror("Error\nWrong Arguments!");
		exit(EXIT_FAILURE);
	}
}
