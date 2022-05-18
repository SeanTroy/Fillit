/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plehtika <plehtika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:46:43 by plehtika          #+#    #+#             */
/*   Updated: 2022/03/04 17:46:28 by plehtika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	check_tetrform(char buf[TETR_SIZE], int i, int block, int check)
{
	while (i < TETR_SIZE - 1)
	{
		if (buf[i] != '.' && buf[i] != '#' && buf[i] != '\n')
			return (-1);
		if (buf[i] == '#')
		{
			block++;
			if ((i < 18 && buf[i + 1] != '#') && (i < 14 && buf[i + 5] != '#')
				&& (i > 0 && buf[i - 1] != '#') && (i > 4 && buf[i - 5] != '#'))
				return (-1);
			if (i > 0 && buf[i - 1] == '#')
				check++;
			if (i > 4 && buf[i - 5] == '#')
				check++;
			if (i < 14 && buf[i + 5] == '#')
				check++;
			if (i < 18 && buf[i + 1] == '#')
				check++;
			if (block == 4 && check < 6)
				return (-1);
		}
		i++;
	}
	return (block);
}

void	check_mapchars(char *argv)
{
	char	buf[TETR_SIZE];
	int		read_ret;
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error_exit(fd);
	read_ret = read(fd, buf, TETR_SIZE);
	while (read_ret > 0)
	{
		if (check_tetrform(buf, 0, 0, 0) != 4)
			error_exit(fd);
		read_ret = read(fd, buf, TETR_SIZE);
	}
	if (read_ret == -1)
		error_exit(fd);
	close(fd);
	return ;
}

int	check_linesize(int linenum, int charnum)
{
	if (linenum % 5 != 0 && charnum != 4)
		return (-1);
	if (linenum % 5 == 0 && charnum != 0)
		return (-1);
	return (0);
}

void	check_mapsize(t_tetris *lst, int fd)
{
	char	buf[MAX_FILESIZE];
	int		read_ret;

	read_ret = read(fd, buf, MAX_FILESIZE);
	if (read_ret == -1)
		error_exit(fd);
	while (lst->i < read_ret)
	{
		while (buf[lst->i] != '\n' && lst->i++ < read_ret)
			lst->charnum++;
		if (check_linesize(lst->linenum, lst->charnum) == -1)
			error_exit(fd);
		if ((lst->linenum + 1) % 5 == 0 && lst->charnum == 4)
			lst->amount++;
		if (lst->i++ < read_ret)
			lst->linenum++;
		lst->charnum = 0;
	}
	lst->i = 0;
	if (lst->linenum % 5 != 0)
		error_exit(fd);
	close(fd);
	return ;
}

void	validate_map(t_tetris *lst, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error_exit(fd);
	check_mapsize(lst, fd);
	if (lst->amount < 1 || lst->amount > 26)
		error_exit(fd);
	check_mapchars(argv);
	return ;
}
