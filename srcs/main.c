/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:54:39 by ldick             #+#    #+#             */
/*   Updated: 2025/09/16 11:46:16 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conway.h"

void init(conway *con)
{
	con->mlx = mlx_init(WIDTH, HEIGHT, "conway", false);
	con->img = mlx_new_image(con->mlx, WIDTH, HEIGHT);
	con->edit = false;
	mlx_image_to_window(con->mlx, con->img, 0, 0);
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
		{
			mlx_put_pixel(con->img, x, y, BLACK);
			con->cell[x][y] = false;
		}
}

void mouse_hook(conway *con)
{
	int x, y;
	mlx_get_mouse_pos(con->mlx, &x, &y);
	if (mlx_is_mouse_down(con->mlx, MLX_MOUSE_BUTTON_LEFT))
		con->cell[x][y] = !con->cell[x][y];
}

void	draw(conway *con)
{
	int i = 0;
	int color;
	if (con->change_amount == 0)
	{
		for (int x = 0; x < WIDTH; x++)
			for (int y = 0; y < HEIGHT; y++)
				(con->cell[x][y] == true) ? mlx_put_pixel(con->img, x, y, WHITE) : mlx_put_pixel(con->img, x, y, BLACK);
	}
	else
		while(i < con->change_amount)
		{
			color = (con->cell[con->to_change_x[i]][con->to_change_y[i]] == true) ? BLACK : WHITE;
			mlx_put_pixel(con->img, con->to_change_x[i], con->to_change_y[i], color);
			i++;
		}
	con->change_amount = 0;
}

void	cell_check(conway *con)
{
	int alive = 0;
	int i = 0;
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
		{
			if (x > 0 && y > 0 && con->cell[x - 1][y - 1]) alive++;
			if (x > 0 && con->cell[x - 1][y]) alive++;
			if (x > 0 && y < HEIGHT - 1 && con->cell[x - 1][y + 1]) alive++;
			if (y > 0 && con->cell[x][y - 1]) alive++;
			if (y < HEIGHT - 1 && con->cell[x][y + 1]) alive++;
			if (x < WIDTH - 1 && y > 0 && con->cell[x + 1][y - 1]) alive++;
			if (x < WIDTH - 1 && con->cell[x + 1][y]) alive++;
			if (x < WIDTH - 1 && y < HEIGHT - 1 && con->cell[x + 1][y + 1]) alive++;
			if (con->cell[x][y] == true)
			{
				if (alive < 2 || alive > 3)
				{
					con->to_change_x[i] = x;
					con->to_change_y[i] = y;
					i++;
				}
			}
			else
				if (alive == 3)
				{
					con->to_change_x[i] = x;
					con->to_change_y[i] = y;
					i++;
				}
			alive = 0;
		}
	con->change_amount = i;
}

void	events(void *param)
{
	conway *con = (conway*)param;
	if (mlx_is_key_down(con->mlx, MLX_KEY_E))
		con->edit = !con->edit;
	printf("%d\n", con->edit);
	if (con->edit)
	{
		mouse_hook(con);
	}
	cell_check(con);
	draw(con);
}

int main(void)
{
	conway *con = malloc(sizeof(conway));
	init(con);
	mlx_loop_hook(con->mlx, events, con);
	mlx_loop(con->mlx);
}