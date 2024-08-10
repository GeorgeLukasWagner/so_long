/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:18:27 by gwagner           #+#    #+#             */
/*   Updated: 2024/08/10 17:34:42 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	checkwrong(t_list **map, int fd)
{
	t_list	*tmp;
	int		i;

	fd--;
	tmp = *map;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] != '0' && tmp->line[i] != '1'
				&& tmp->line[i] != '\n' && tmp->line[i] != 'P'
				&& tmp->line[i] != 'C' && tmp->line[i] != 'E'
				&& tmp->line[i] != '\0')
			{
				ft_error2("Error\nInvalid map element!", fd, map);
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	find_cur(char **map, t_point *cur)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				break ;
			x++;
		}
		if (map[y][x] == 'P')
			break ;
		y++;
	}
	cur->y = y;
	cur->x = x;
}

void	fill(char **map, t_point size, t_point cur, t_data *data)
{
	if (map[cur.y][cur.x] == 'E')
		data->exit = true;
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| (map[cur.y][cur.x] != 'C' && map[cur.y][cur.x] != '0'
		&& map[cur.y][cur.x] != 'P'))
	{
		return ;
	}
	if (map[cur.y][cur.x] == 'C')
		data->fccol++;
	map[cur.y][cur.x] = '1';
	fill(map, size, (t_point){cur.x - 1, cur.y}, data);
	fill(map, size, (t_point){cur.x + 1, cur.y}, data);
	fill(map, size, (t_point){cur.x, cur.y - 1}, data);
	fill(map, size, (t_point){cur.x, cur.y + 1}, data);
}

void	verification(t_list **lmap, t_data *data)
{
	char	**map;
	t_list	*tmp;
	t_point	size;
	t_point	cur;
	int		i;

	data->fccol = 0;
	tmp = *lmap;
	size.x = ft_strlen(tmp->line);
	size.y = ft_lstsize(tmp);
	map = malloc(sizeof(char *) * ft_lstsize(tmp) + 1);
	i = 0;
	while (tmp)
	{
		map[i] = tmp->line;
		tmp = tmp->next;
		i++;
	}
	cur.x = 0;
	cur.y = 0;
	find_cur(map, &cur);
	fill(map, size, cur, data);
	free(map);
}

void	check_textures(t_data *data)
{
	if (data->textures[0] == NULL || data->textures[1] == NULL
		|| data->textures[2] == NULL || data->textures[3] == NULL
		|| data->textures[4] == NULL)
	{
		perror("Error\nDidn't find picture!");
		on_destroy(data);
	}
}
