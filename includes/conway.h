/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conway.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:51:44 by ldick             #+#    #+#             */
/*   Updated: 2025/09/16 14:17:44 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONWAY_H
# define CONWAY_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF
#define WIDTH 1920
#define HEIGHT 1080

typedef struct conway
{
	mlx_t *mlx;
	mlx_image_t *img;
	bool	edit;
	bool	cell[WIDTH][HEIGHT];
	int		to_change_x[WIDTH * HEIGHT];
	int		to_change_y[HEIGHT * HEIGHT];
	int		change_amount;

} conway;

#endif