/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:30:59 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/31 13:27:43 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "structs.h"
# include "camera.h"
# include "minimap.h"

// Define la anchura y altura de la imagen que se va a mostrar
#define texWidth 64
#define texHeight 64

#define mapWidth 24
#define mapHeight 24

// Define la anchura y altura de la ventana de visualización
#define W_WIDTH 800 //W_WIDTH
#define W_HEIGH 600 //W_HEIGH

//Definitions to xml hook
# define PLAYER_SPEED		0.05
# define ROTATION_SPEED		0.05
# define KEY_PRESS_MASK		(1L<<0)
# define KEY_RELEASE_MASK	(1L<<1)

// Directions
# define KEY_ESC			65307
# define KEY_UP				65362
# define KEY_DOWN			65364
# define KEY_RIGHT			65363
# define KEY_LEFT			65361
# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17

// Define la sensibilidad del ratón
# define MOUSE_SENSITIVITY	0.005

// Define la velocidad de movimiento de la cámara
# define MOVE_SPEED		0.02
# define ROT_SPEED		0.02
# define FOV_ANGLE 		60.0

/* INIT */
bool	initialize(t_game *game, char **argv);

/* ERROR */
void	error(char * msg);
void	exit_error(char * msg);

/* INPUT */
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
void	process_ws_position(t_game *game, t_player *player);
void	process_ad_position(t_game *game, t_player *player);
void	process_angle(t_game *game, t_player *player);

/* MAP GENERATE */
int		mapgenerate(t_game *game, char *file);

/* MAP CHECK */
int		mapcheck(char **map);

/* DRAW */
void	draw_floor_ceiling(t_game *game);
void 	draw_wall(t_game *game);

/* UTILS */
bool	arg_check(int argc, char **argv);
void	init_zbuffer(t_game *game);
void	init_vars(t_game *game);
int		is_allowed(char c);
int		file_exists(char *s);

/* PARSE MAP */
void	parse_file(char *argv, t_game *game);

/* INPUT CHECKS */
int		validate_content(char *map_file, t_parse *data, t_game *game);
int		input_check(char *argv, t_parse *data, t_game *game);

/* OBJECT VALIDATING */
int		invalid_attribute(char *line);
int		check_duplicate(char *line, t_parse *data);
int		validate_no_so(char *line, t_parse *data);
int		validate_we_ea(char *line, t_parse *data);
int		validate_texture(char *line, t_parse *data);
int		contains_valid_objects(char *line, t_parse *data);

/* COLOR VALIDATING */
int		valid_rgb(char **rgb);
int		commacounter(char *line);
int		has_duplicate_rgb(char *line);
int		rgb_contains_letters(char *line);
char	**split_rgb(char *line, char *trim_with);
int		validate_color(char *line, t_parse *data);

/* SAVE DATA */
void	save_color_to_data(char **rgb, t_parse *data, char option);
void	save_texture_to_data(char *file, t_parse *data, char option);

/* IMAGES */
bool	init_images(t_game *game, t_parse *data);

/* MAP VALIDATING */
char	*get_line(int fd, char *line);
bool	check_line(char *line, int i, t_parse *data);
int		line_has_invalid_chars(char *line);
int		map_checks(t_parse *data, int i, t_game *game);
int		line_cotains_only_spaces(char *line);
void	get_player_pos(char **map, t_game *game);
int		map_has_multiple_players_or_none(char c, char option);
int		map_validathor(char *map_file, t_parse *data, int fd, t_game *game);
void	get_map_length(int fd, char *map_file, t_parse *data);
char	*copy_map_line(char *content);
void	free_char_array(char **array);
int		it_can_be_opened(char *file);

/* UTILS */
char	*copy_map_line_fixed(char *content, t_parse *data);
void	ft_print_2d_char_array(char **array_2d);
#endif