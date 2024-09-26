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
# include "./srcsGNL/get_next_line.h"
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	int			rows;
	int			cols;
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

void get_map(int argc, char **argv, t_data *data);
void print_string_array(char **array);

#endif