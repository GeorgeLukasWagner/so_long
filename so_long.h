/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:24:34 by gwagner           #+#    #+#             */
/*   Updated: 2024/08/10 17:46:42 by gwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <math.h>
# include <stdlib.h>
# include <stddef.h>
# include <mlx.h>
# include <fcntl.h>
# include <stdbool.h>
# include "get_next_line.h"
# include "./printf/ft_printf.h"
# include <stdio.h>
# include <string.h>

# define SPRITE_WIDTH 120
# define SPRITE_HEIGHT 120

typedef struct s_map
{
	int		x;
	int		y;
	char	type;
}		t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*textures[5];
	t_map		*map;
	int			tcol;
	int			ccol;
	int			fccol;
	bool		exit;
	int			movc;
}		t_data;

typedef struct s_list
{
	char			*line;
	struct s_list	*next;
}		t_list;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

t_map	*mapping(int fd, t_data *data);
t_map	*make_map(t_list **map);
void	tilecheck(int fd, t_list **map, int exit, int start);
void	enclosure_check(int fd, t_list **map);
void	ft_free(char **str);
void	ft_error2(char *msg, int fd, t_list **to_free);
t_list	*ft_lstnew(char *line);
void	ft_lstadd_front(t_list **stack, t_list *new);
t_list	*ft_lstlast(t_list *head);
void	ft_lstadd_back(t_list **stack, t_list *new);
int		ft_lstsize(t_list *head);
void	free_stack(t_list **stack);
void	ft_printlst(t_list *head);
int		movetest(int keysym, t_data *data);
int		on_destroy(t_data *data);
int		mov_p(t_data *data, int keysym, int pos);
int		get_pos(t_data *data);
void	finish(t_data *data);
void	checkcol(int pos, t_data *data);
void	checkwrong(t_list **map, int fd);
void	verification(t_list **lmap, t_data *data);
void	checkmapname(char *mapname);
void	check_textures(t_data *data);

#endif