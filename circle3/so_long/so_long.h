/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:25:25 by marsenij          #+#    #+#             */
/*   Updated: 2024/08/25 14:28:28 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	char		**flood_map;
	int			rows;
	int			cols;
	int			reachable;
	int			collectables;
	int			exit_found;
//	Assets
	char		*back_path;
	char		*wall_path;
	char		*player_path;
	char		*exit_path;
	int			width;
	int			height;
	void		*img_exit;
	void		*img_back;
	void		*img_wall;
	void		*img_consumable;
	void		*img_player;
// Player location
	int			Px;
	int			Py;
}	t_data;

char *get_next_line(int fd);
int	ft_strlen(const char *s);
void free_map(char **map);
int	cntletter(char **map, char ltr);
void get_map(char **argv, t_data *data);

#endif