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

int	on_key_press(int keycode, void *data)
{
	if (keycode == XK_Escape)
	{
		on_destroy(data);
	}
	else if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
	{
		playermove(keycode, data);
	}
	return (0);
}

int	is_ber(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 5)
	{
		write(2, "Error\n", 6);
		write(2, "wrong file name\n", 16);
		return (0);
	}
	if (s[len - 4] != '.' || s[len - 3] != 'b'
		|| s[len - 2] != 'e' || s[len - 1] != 'r')
	{
		write(2, "Error\n", 6);
		write(2, "wrong file name\n", 16);
		return (0);
	}
	return (1);
}

void	is_reachable(t_data *data, int x, int y)
{
	if (data->flood_map[x][y] == '1' || data->flood_map[x][y] == 'V'
		|| x <= 0 || y <= 0 || x >= data->rows || y >= data->cols)
		return ;
	if (data->flood_map[x][y] == 'C')
	{
		data->collectables--;
		data->flood_map[x][y] = 'V';
	}
	else if (data->flood_map[x][y] == 'E')
	{
		data->exit_found = 1;
		data->flood_map[x][y] = 'V';
	}
	else if (data->flood_map[x][y] == 'P' || data->flood_map[x][y] == '0')
		data->flood_map[x][y] = 'V';
	if (data->collectables == 0 && data->exit_found == 1)
	{
		data->reachable = 1;
		return ;
	}
	is_reachable(data, x + 1, y);
	is_reachable(data, x, y + 1);
	is_reachable(data, x - 1, y);
	is_reachable(data, x, y - 1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!(is_ber(argv[1]) || argc != 2))
		return (1);
	get_map(argv, &data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			data.cols * 36, data.rows * 36, "Kill your doppelganger");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	find_player(&data);
	init_assets(&data);
	is_reachable(&data, data.py, data.px);
	if (data.reachable == 0)
	{
		write(2, "Error\nC or E not reachable\n", 27);
		on_destroy(&data);
		exit(EXIT_FAILURE);
	}
	mlx_hook(data.win_ptr, ClientMessage, NoEventMask, &on_destroy, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &on_key_press, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
