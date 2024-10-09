/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playermove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:39:20 by marsenij          #+#    #+#             */
/*   Updated: 2024/09/26 08:48:22 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j] != '\n' && data->map[i][j] != '\0')
		{
			if (data->map[i][j] == 'P')
			{
				data->px = j;
				data->py = i;
			}
			j++;
		}
		i++;
	}
}

void	eval_keycode(int keycode, t_data *data, int *new_px, int *new_py)
{
	if (keycode == XK_w)
		*new_py = data->py - 1;
	else if (keycode == XK_a)
		*new_px = data->px - 1;
	else if (keycode == XK_s)
		*new_py = data->py + 1;
	else if (keycode == XK_d)
		*new_px = data->px + 1;
}

void	playermove(int keycode, t_data *data)
{
	int	new_px;
	int	new_py;

	new_px = data->px;
	new_py = data->py;
	eval_keycode(keycode, data, &new_px, &new_py);
	if (data->map[new_py][new_px] == '1')
		return ;
	if (data->map[new_py][new_px] == 'C')
		data->map[new_py][new_px] = '0';
	if (data->map[new_py][new_px] == 'E' && !(cntletter(data->map, 'C')))
		on_destroy(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_player,
		new_px * data->width, new_py * data->height);
	if (data->map[data->py][data->px] == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_exit,
			data->px * data->width, data->py * data->height);
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_back,
			data->px * data->width, data->py * data->height);
	data->px = new_px;
	data->py = new_py;
	data->movecnt++;
}
