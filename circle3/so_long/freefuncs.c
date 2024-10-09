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

void	free_map(char **map)
{
	int	i;

	if (!(map))
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	on_destroy(t_data *data)
{
	free_map(data->map);
	free_map(data->flood_map);
	free_images(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}
