/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:33:02 by gwagner           #+#    #+#             */
/*   Updated: 2024/08/10 17:46:33 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	checklen(t_list **map, int fd)
{
	size_t	len;
	int		i;
	t_list	*tmp;

	tmp = *map;
	i = 0;
	len = ft_strlen((*map)->line);
	while (tmp)
	{
		if (ft_strlen(tmp->line) != len && tmp->next)
			ft_error2("Error\nMap isnt rectangular!", fd, map);
		else if (ft_strlen(tmp->line) + 1 != len && !tmp->next)
			ft_error2("Error\nMap isnt rectangular!", fd, map);
		tmp = tmp->next;
	}
}

void	parsemap(t_list **map, int fd)
{
	t_list	*new;
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	if (!line)
		ft_error2("Error\nFailed to read map!", fd, map);
	while (line)
	{
		if (ft_strlen(line) < 4)
			ft_error2("Error\nMap is too small!", fd, map);
		new = ft_lstnew(line);
		ft_lstadd_back(map, new);
		line = get_next_line(fd);
		i++;
	}
	if (i < 3)
		ft_error2("Error\nMap is too small!", fd, map);
	checklen(map, fd);
}

void	count_c(t_data *data, t_list **map)
{
	int		i;
	t_list	*tmp;

	tmp = *map;
	i = 0;
	data->tcol = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] == 'C')
				data->tcol++;
			i++;
		}
		tmp = tmp->next;
	}
}

t_map	*mapping(int fd, t_data *data)
{
	t_list	**map;
	t_map	*arr;

	map = malloc(sizeof(t_list *));
	*map = NULL;
	parsemap(map, fd);
	enclosure_check(fd, map);
	checkwrong(map, fd);
	tilecheck(fd, map, 0, 0);
	count_c(data, map);
	arr = make_map(map);
	verification(map, data);
	if (data->exit == false || data->tcol != data->fccol)
	{
		free(arr);
		ft_error2("Error\nExit unreachable!", fd, map);
	}
	free_stack(map);
	data->ccol = 0;
	data->movc = 0;
	return (arr);
}
