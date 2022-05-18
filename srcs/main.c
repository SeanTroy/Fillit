/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plehtika <plehtika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:39:13 by plehtika          #+#    #+#             */
/*   Updated: 2022/01/26 15:35:28 by plehtika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	save_coordinates(t_tetris *lst, int c_index)
{
	if (lst->block++ == 0)
	{
		lst->startrow[lst->i] = lst->row;
		lst->startcol[lst->i] = lst->col;
	}
	else
	{
		lst->tetrxy[lst->i][c_index] = lst->row - lst->startrow[lst->i];
		if (lst->tetrxy[lst->i][c_index] > lst->height[lst->i])
			lst->height[lst->i] = lst->tetrxy[lst->i][c_index];
		lst->tetrxy[lst->i][c_index + 1] = lst->col - lst->startcol[lst->i];
		if (lst->tetrxy[lst->i][c_index + 1] > lst->width[lst->i])
			lst->width[lst->i] = lst->tetrxy[lst->i][c_index + 1];
	}
}

void	tetr_specs(t_tetris *lst)
{
	int	c_index;

	lst->i = 0;
	while (lst->i < lst->amount)
	{
		c_index = -2;
		lst->block = 0;
		while (lst->row < 4)
		{
			while (lst->col < 4)
			{
				if (lst->tetr[lst->i][lst->row][lst->col] == 'A' + lst->i)
				{
					save_coordinates(lst, c_index);
					c_index += 2;
				}
				lst->col++;
			}
			lst->col = 0;
			lst->row++;
		}
		lst->row = 0;
		lst->i++;
	}
}

void	copy_tetrs(t_tetris *lst, int fd, int i)
{
	char	buf[TETR_SIZE];
	int		read_ret;

	read_ret = read(fd, buf, TETR_SIZE);
	while (read_ret > 0)
	{
		while (lst->row < 4)
		{
			while (lst->col < 4)
			{
				if (buf[i] == '#')
					buf[i] = 'A' + lst->i;
				lst->tetr[lst->i][lst->row][lst->col++] = buf[i++];
			}
			lst->col = 0;
			i++;
			lst->row++;
		}
		lst->row = 0;
		lst->i++;
		i = 0;
		read_ret = read(fd, buf, TETR_SIZE);
	}
	if (read_ret == -1)
		error_exit(fd);
}

int	main(int argc, char **argv)
{
	t_tetris	lst;
	int			fd;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit filename\n");
		exit (0);
	}
	initialize(&lst);
	validate_map(&lst, argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_exit(fd);
	copy_tetrs(&lst, fd, 0);
	close(fd);
	tetr_specs(&lst);
	while ((lst.sqrsize * lst.sqrsize) < (lst.amount * 4))
		lst.sqrsize++;
	while (make_sqr(&lst) != 1)
		lst.sqrsize++;
	return (0);
}
