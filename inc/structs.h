/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:29:28 by imurugar          #+#    #+#             */
/*   Updated: 2023/06/01 20:32:34 by imurugar         ###   ########.fr       */
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
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
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
	float	ray_dir_x;
	float	ray_dir_y;
	float	ray_dir_x1;
	float	ray_dir_y1;
	int		pos;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		tx;
	int		ty;
}		t_draw_vars;

//raycasting struct
typedef struct s_w_vars
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int 	draw_end;
	int		draw_start;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
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
	size_t	line_size;
	char	**raw_map;
}				t_parse;

#endif