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

void free_map(char **map)
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
				data->Px = j;
				data->Py = i;
			}
			j++;
		}
		i++;
	}
}

void playermove(int keycode, t_data *data)
{
	int	newPx;
	int	newPy;

	newPx = data->Px;
	newPy = data->Py;
	if (keycode == XK_w)
		newPy = data->Py - 1;
	else if (keycode == XK_a)
		newPx = data->Px - 1;
	else if (keycode == XK_s)
		newPy = data->Py + 1;
	else if (keycode == XK_d)
		newPx = data->Px + 1;
	if(data->map[newPy][newPx] == '1')
		return ;
	if(data->map[newPy][newPx] == 'C')
		data->map[newPy][newPx] = '0';
	if(data->map[newPy][newPx] == 'E' && !(cntletter(data->map,'C')))
		on_destroy(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_player, newPx * data->width, newPy * data->height);
	if(data->map[data->Py][data->Px] == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_exit, data->Px * data->width, data->Py * data->height);		
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_back, data->Px * data->width, data->Py * data->height);
	data->Px = newPx;
	data->Py = newPy;
}


int	on_key_press(int keycode, void *data)
{
	if (keycode == XK_Escape)
	{
		on_destroy(data);
	}
	else if (keycode == XK_w || keycode == XK_s || keycode == XK_a || keycode == XK_d)
	{
		playermove(keycode, data);
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

void init_assets(t_data *data)
{
	data->exit_found = 0;
	data->collectables = cntletter(data->map,'C');
	data->reachable = 0;
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
	if (!data->img_exit || !data->img_back || !data->img_wall || !data->img_consumable || !data->img_player)
		on_destroy(data);
	initial_draw(data);
}

int is_ber(char *s)
{
	int len;

	len = ft_strlen(s);
	if (len < 5)
		return (0);
	if (s[len - 4] != '.' || s[len - 3] != 'b' || s[len - 2] != 'e' || s[len - 1] != 'r')
		return (0);
	return (1);
}

void print_double_char_array(char **array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {       // Loop through each row
        for (int j = 0; j < cols; j++) {   // Loop through each column
            putchar(array[i][j]);           // Print each character
        }
        putchar('\n');                      // Print a newline after each row
    }
	putchar('\n');
}

void	is_reachable(t_data *data, int x, int y)
{
	print_double_char_array(data->flood_map, data->rows, data->cols);
    if (data->flood_map[x][y] == '1' || data->flood_map[x][y] == 'V' || x <= 0 || y <= 0 || x >= data->rows || y >= data->cols)
        return;
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
        return;
	}
    is_reachable(data, x + 1, y);
    is_reachable(data, x, y + 1);
    is_reachable(data, x - 1, y);
    is_reachable(data, x, y - 1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.mlx_ptr = NULL;
	if(!(is_ber(argv[1]) || argc != 2))
		return (1);
	get_map(argv, &data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.cols * 36, data.rows * 36, "so long");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	find_player(&data);
	init_assets(&data);
	is_reachable(&data, data.Py, data.Px);
	if (data.reachable == 0)
	{	
		write(2, "C or E not reachable\n", 21);
		on_destroy(&data);
		exit(EXIT_FAILURE);
	}
	mlx_hook(data.win_ptr, ClientMessage, NoEventMask, &on_destroy, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &on_key_press, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
