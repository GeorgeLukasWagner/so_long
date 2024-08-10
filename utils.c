/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:32:02 by gwagner           #+#    #+#             */
/*   Updated: 2024/08/10 16:16:56 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	free(str);
}

void	ft_error2(char *msg, int fd, t_list **to_free)
{
	perror(msg);
	free_stack(to_free);
	close(fd);
	exit(EXIT_FAILURE);
}

void	finish(t_data *data)
{
	ft_printf("Well done! It took you %d moves!\n", data->movc + 1);
	on_destroy(data);
}

void	checkcol(int pos, t_data *data)
{
	if (data->map[pos].type == 'C')
		data->ccol++;
	if (data->map[pos].type == '0' || data->map[pos].type == 'C')
		data->movc++;
}

void	checkmapname(char *mapname)
{
	int	i;

	i = 0;
	while (mapname[i])
		i++;
	i--;
	if (mapname[i] != 'r' || mapname[i - 1] != 'e'
		|| mapname[i - 2] != 'b' || mapname[i - 3] != '.')
	{
		perror("Error\nMapname is false!");
		exit(EXIT_FAILURE);
	}
}
