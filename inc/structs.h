/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:29:28 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/28 18:35:13 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

// Map data
typedef struct s_map
{
	char	**map;
	int		map_width;
	int		map_height;
	int		floor_color;
	int		ceil_color;
	void	*n_wall;
	void	*s_wall;
	void	*e_wall;
	t_img	w_wall;
}  			 t_map;

/*
typedef struct s_player
{
    double x;
    double y;
    double angle;
}	t_player;
*/
typedef struct	s_player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
}			t_player;

//Imput keys
typedef struct	s_keys
{
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
	
}			t_keys;
// Define la estructura de datos para el juego
typedef struct	s_game
{
	
	void		*mlx;
	void		*win;
	t_keys		keys;
	t_img		img;
	t_player	player;
	t_map		map;
	int			**zbuffer;//[600][800];
	int			**texture;
	char		**texture_path;
}				t_game;

//struct for draw map
typedef struct s_draw_vars
{
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	int		pos;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		tx;
	int		ty;
}		t_draw_vars;

//raycasting struct
typedef struct s_w_vars
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int 	drawEnd;
	int		drawStart;
	int		texNum;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
}		t_w_vars;

typedef struct	s_parse
{
	int		reading_pos;
	int		error;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f_color[3];
	int		c_color[3];
	int		map_length;
	char	**raw_map;
}				t_parse;

#endif