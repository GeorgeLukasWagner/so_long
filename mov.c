/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:42:50 by gwagner           #+#    #+#             */
/*   Updated: 2024/08/10 13:03:40 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_pos(t_data *data)
{
	int		i;
	t_map	*map;

	i = 0;
	map = data->map;
	while (map[i].type != 'P')
		i++;
	return (i);
}

int	get_width(t_map *map)
{
	int	i;

	i = 0;
	while (map[i].type != '\n')
		i++;
	return (i);
}

int	change_pos(int keysym, int pos, int i)
{
	if (keysym == 119)
		pos -= i;
	else if (keysym == 115)
		pos += i;
	else if (keysym == 97)
		pos -= 1;
	else if (keysym == 100)
		pos += 1;
	return (pos);
}

int	mov_p(t_data *data, int keysym, int pos)
{
	int		i;
	int		ret;
	int		b;

	b = 120;
	data->map[pos].type = '0';
	ret = pos;
	i = get_width(data->map) + 1;
	pos = change_pos(keysym, pos, i);
	checkcol(pos, data);
	if (data->map[pos].type == 'E' && data->ccol == data->tcol)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->textures[3],
			data->map[pos].x * 120, data->map[pos].y * 120);
		finish(data);
	}
	else if (data->map[pos].type != '1' && data->map[pos].type != 'E')
		data->map[pos].type = 'P';
	else
	{
		b = 0;
		data->map[ret].type = 'P';
	}
	return (b);
}

int	movetest(int keysym, t_data *data)
{
	int			pos;
	int			x;
	int			y;

	pos = get_pos(data);
	x = data->map[pos].x * 120;
	y = data->map[pos].y * 120;
	mlx_put_image_to_window(data->mlx, data->win, data->textures[0], x, y);
	if (keysym == 119)
		y -= mov_p(data, keysym, pos);
	else if (keysym == 115)
		y += mov_p(data, keysym, pos);
	else if (keysym == 97)
		x -= mov_p(data, keysym, pos);
	else if (keysym == 100)
		x += mov_p(data, keysym, pos);
	else if (keysym == 65307)
		on_destroy(data);
	ft_printf("%d\n", data->movc);
	mlx_put_image_to_window(data->mlx, data->win, data->textures[3], x, y);
	return (0);
}
