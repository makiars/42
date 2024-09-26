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

void	free_images(t_data *data)
{
	if (data->img_exit)
		mlx_destroy_image(data->mlx_ptr, data->img_exit);
	if (data->img_back)
		mlx_destroy_image(data->mlx_ptr, data->img_back);
	if (data->img_wall)
		mlx_destroy_image(data->mlx_ptr, data->img_wall);
	if (data->img_consumable)
		mlx_destroy_image(data->mlx_ptr, data->img_consumable);
	if (data->img_player)
		mlx_destroy_image(data->mlx_ptr, data->img_player);
}

void free_map(t_data *data)
{
	int	i;

	if (!(data->map))
		return ;
	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

int	on_destroy(t_data *data)
{
	free_map(data);
	free_images(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	on_key_press(int keycode, void *param)
{
	if (keycode == XK_Escape)
	{
		on_destroy(param);
	}
	else if (keycode == XK_W)
	{
		//move up
	}
	return (0);
}

void initial_draw(t_data *data)
{
	int i = 0;
	int j = 0;
	while(j < data->rows)
	{
		while(i < data->cols)
		{
			if (data->map[j][i] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_back, i * data->width, j * data->height);
			else if (data->map[j][i] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_player, i * data->width, j * data->height);
			else if (data->map[j][i] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_consumable, i * data->width, j * data->height);
			else if (data->map[j][i] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_wall, i * data->width, j * data->height);
			else if (data->map[j][i] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_exit, i * data->width, j * data->height);
			i++;
		}
		i = 0;
		j++;
	}
}

/*void find_player_pos(t_data data)
{


}
*/
/*
void draw_player(t_data *data)
{
	data->Px = 1; //just for debugging
	data->Py = 1;
	find_pos(data,'P' );

}
*/


void init_assets(t_data *data)
{
	data->back_path = "./srcsAssets/background.xpm";
	data->exit_path = "./srcsAssets/exit.xpm";
	data->wall_path = "./srcsAssets/wall.xpm";
	data->player_path = "./srcsAssets/player.xpm";
	data->height = 36;
	data->width = 36;
	data->img_exit = mlx_xpm_file_to_image(data->mlx_ptr, data->exit_path, &data->width, &data->height);
	data->img_back = mlx_xpm_file_to_image(data->mlx_ptr, data->back_path, &data->width, &data->height);
	data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr, data->wall_path, &data->width, &data->height);
	data->img_consumable = mlx_xpm_file_to_image(data->mlx_ptr, data->player_path, &data->width, &data->height);
	data->img_player = mlx_xpm_file_to_image(data->mlx_ptr, data->player_path, &data->width, &data->height);
	initial_draw(data);
//	draw_player(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	get_map(argc, argv, &data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.cols * 36, data.rows * 36, "so long");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	init_assets(&data);
	mlx_hook(data.win_ptr, ClientMessage, NoEventMask, &on_destroy, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &on_key_press, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
