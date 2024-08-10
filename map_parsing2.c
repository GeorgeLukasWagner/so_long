/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:31:09 by gwagner           #+#    #+#             */
/*   Updated: 2024/08/10 18:08:43 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	enclosure_check(int fd, t_list **map)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	tmp = *map;
	while (tmp)
	{
		i = 0;
		if (tmp == *map || tmp->next == NULL)
		{
			while (tmp->line[i])
			{
				if (tmp->line[i] != '1' && tmp->line[i] != '\n')
					ft_error2("Error\nMap is not enclosed!", fd, map);
				i++;
			}
		}
		else
		{
			if (tmp->line[0] != '1'
				|| tmp->line[ft_strlen(tmp->line) - 2] != '1')
				ft_error2("Error\nMap is not enclosed!", fd, map);
		}
		tmp = tmp->next;
	}
}

void	tilecheck(int fd, t_list **map, int exit, int start)
{
	bool	collectable;
	int		i;
	t_list	*tmp;

	tmp = *map;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (tmp->line[i] == 'E')
				exit++;
			else if (tmp->line[i] == 'P')
				start++;
			else if (tmp->line[i] == 'C')
				collectable = true;
			i++;
		}
		tmp = tmp->next;
	}
	if (exit != 1 || start != 1 || !collectable)
		ft_error2("Error\nFollow map rules!", fd, map);
}

t_map	*make_map(t_list **map)
{
	t_map	*arr;
	int		x;
	int		y;
	int		i;
	t_list	*tmp;

	y = 0;
	tmp = *map;
	arr = malloc(sizeof(t_map) * (ft_lstsize(tmp) * ft_strlen(tmp->line)));
	i = 0;
	while (tmp)
	{
		x = 0;
		while (tmp->line[x])
		{
			arr[i].x = x;
			arr[i].y = y;
			arr[i++].type = tmp->line[x++];
		}
		y++;
		tmp = tmp->next;
	}
	arr[i].type = '\0';
	return (arr);
}
