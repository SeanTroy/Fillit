/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plehtika <plehtika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 20:31:05 by plehtika          #+#    #+#             */
/*   Updated: 2022/01/25 19:37:31 by plehtika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_square(t_tetris *lst, char **sqr)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < lst->sqrsize)
	{
		while (k < lst->sqrsize)
			ft_putchar(sqr[j][k++]);
		ft_putchar('\n');
		k = 0;
		j++;
	}
}

void	erase_tetr(t_tetris *lst, char **sqr, int row, int col)
{
	sqr[row][col] = '.';
	sqr[row + lst->tetrxy[lst->i][0]][col + lst->tetrxy[lst->i][1]] = '.';
	sqr[row + lst->tetrxy[lst->i][2]][col + lst->tetrxy[lst->i][3]] = '.';
	sqr[row + lst->tetrxy[lst->i][4]][col + lst->tetrxy[lst->i][5]] = '.';
}

void	initialize(t_tetris *lst)
{
	int	i;

	i = 0;
	lst->row = 0;
	lst->col = 0;
	lst->amount = 0;
	lst->i = 0;
	lst->block = 0;
	lst->sqrsize = 0;
	lst->charnum = 0;
	lst->linenum = 1;
	while (i < 26)
	{
		lst->startrow[i] = 0;
		lst->startcol[i] = 0;
		lst->height[i] = 0;
		lst->width[i] = 0;
		i++;
	}
}

void	null_sqr(t_tetris *lst, char **sqr)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < lst->sqrsize)
	{
		while (k < lst->sqrsize)
			sqr[j][k++] = '.';
		k = 0;
		j++;
	}
}

void	error_exit(int fd)
{
	if (fd != -1)
		close(fd);
	ft_putstr("error\n");
	exit(0);
}
