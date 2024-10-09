/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:39:20 by marsenij          #+#    #+#             */
/*   Updated: 2024/09/26 08:48:22 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_all(t_data *data, int *i, int *j)
{
	if (data->map[*j][*i] == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_back, *i * data->width, *j * data->height);
	else if (data->map[*j][*i] == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_player, *i * data->width, *j * data->height);
	else if (data->map[*j][*i] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_consumable, *i * data->width, *j * data->height);
	else if (data->map[*j][*i] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_wall, *i * data->width, *j * data->height);
	else if (data->map[*j][*i] == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_exit, *i * data->width, *j * data->height);
}

void	initial_draw(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < data->rows)
	{
		while (i < data->cols)
		{
			draw_all(data, &i, &j);
			i++;
		}
		i = 0;
		j++;
	}
}

void	init_assets(t_data *data)
{
	data->exit_found = 0;
	data->collectables = cntletter(data->map, 'C');
	data->reachable = 0;
	data->back_path = "./srcsAssets/background.xpm";
	data->exit_path = "./srcsAssets/exit.xpm";
	data->wall_path = "./srcsAssets/wall.xpm";
	data->player_path = "./srcsAssets/player.xpm";
	data->height = 36;
	data->width = 36;
	data->img_exit = mlx_xpm_file_to_image(data->mlx_ptr,
			data->exit_path, &data->width, &data->height);
	data->img_back = mlx_xpm_file_to_image(data->mlx_ptr,
			data->back_path, &data->width, &data->height);
	data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr,
			data->wall_path, &data->width, &data->height);
	data->img_consumable = mlx_xpm_file_to_image(data->mlx_ptr,
			data->player_path, &data->width, &data->height);
	data->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
			data->player_path, &data->width, &data->height);
	if (!data->img_exit || !data->img_back || !data->img_wall
		|| !data->img_consumable || !data->img_player)
		on_destroy(data);
	initial_draw(data);
	data->movecnt = 0;
}
