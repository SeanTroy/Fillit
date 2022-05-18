/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plehtika <plehtika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:14:52 by plehtika          #+#    #+#             */
/*   Updated: 2022/01/25 19:39:59 by plehtika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define TETR_SIZE 21
# define MAX_FILESIZE 550

typedef struct s_tetris
{
	char	tetr[26][4][4];
	int		startrow[26];
	int		startcol[26];
	int		tetrxy[26][6];
	int		height[26];
	int		width[26];
	int		i;
	int		block;
	int		row;
	int		col;
	int		sqrsize;
	int		amount;
	int		linenum;
	int		charnum;
}	t_tetris;

/*
Struct variables:
tetr[26][4][4]; 3D character array to store max 26 tetriminos of 4 x 4 size
startrow[26]; The row coordinates of the first block of tetrimino
startcol[26]; The column coordinates of the first block of tetrimino
tetrxy[26][6]; The coordinates of blocks 2 to 4, in relation to the first block
	(index 0 and 1: row and column difference of the second block,
	index 2 and 3: row and column difference of the third block,
	index 4 and 5: row and column difference of the fourth block)
height[26]; The tetrimino height, i.e. maximum row difference of the blocks
width[26]; The tetrimino width, i.e. maximum column difference of the blocks
i; Index referring to a single tetrimino
block; Index referring to individual blocks in a single tetrimino
row; Index referring to the row values
col; Index referring to the column values
sqrsize; The size of the square we are trying to fit the tetriminos in
amount; The actual amount of tetrimino blocks in the provided file
linenum; The number of lines in the file
charnum; The number of characters in a single line in the file
*/

int		main(int argc, char **argv);
void	validate_map(t_tetris *lst, char *argv);
void	check_mapsize(t_tetris *lst, int fd);
int		check_linesize(int linenum, int charnum);
void	check_mapchars(char *argv);
int		check_tetrform(char *buf, int i, int block, int check);
int		fill_sqr(t_tetris *lst, char **sqr);
void	print_tetrs(t_tetris *lst);
void	print_square(t_tetris *lst, char **sqr);
void	initialize(t_tetris *lst);
void	null_sqr(t_tetris *lst, char **sqr);
void	erase_tetr(t_tetris *lst, char **sqr, int row, int col);
int		make_sqr(t_tetris *lst);
void	error_exit(int fd);

#endif
