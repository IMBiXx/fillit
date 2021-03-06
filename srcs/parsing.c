/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valecart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:35:33 by valecart          #+#    #+#             */
/*   Updated: 2019/04/18 19:28:21 by valecart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		patch_piece2(t_piece *piece, int *first_x, int *first_y, int *count)
{
	int		i;
	int		j;
	int		total_conn;

	total_conn = 0;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (piece->content[j][i] == '#')
			{
				*first_y = j < *first_y ? j : *first_y;
				*first_x = i < *first_x ? i : *first_x;
				(*count)++;
				total_conn += is_in_one_piece(piece, i, j);
			}
			else if (piece->content[j][i] != '.')
				return (ERROR);
	}
	return (total_conn >= 6 ? SUCCESS : ERROR);
}

int		patch_piece(t_piece *piece)
{
	int		first_x;
	int		first_y;
	int		count;

	first_x = 3;
	first_y = 3;
	count = 0;
	if (patch_piece2(piece, &first_x, &first_y, &count) == ERROR)
		return (ERROR);
	move_to_top(piece, first_x, first_y);
	set_piece_size(piece);
	return (count == 4 ? SUCCESS : ERROR);
}

int		fill_piece(int fd, t_piece *piece)
{
	int		rd;
	int		j;
	char	tmp;

	j = 0;
	while (j < 4)
	{
		if ((rd = read(fd, piece->content[j], 5)) <= 0)
			return (ERROR);
		if (rd != 5 || piece->content[j][4] != '\n')
			return (ERROR);
		piece->content[j][4] = '\0';
		j++;
	}
	rd = read(fd, &tmp, 1);
	if (patch_piece(piece) == ERROR)
		return (ERROR);
	if (rd == 0)
		return (SUCCESS_END);
	if (rd < 0 || tmp != '\n')
		return (ERROR);
	return (SUCCESS);
}

int		fillit_input2(int fd, t_piece ***pieces)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (1)
	{
		if (i >= 26)
			return (ERROR);
		(*pieces)[i + 1] = NULL;
		(*pieces)[i] = piece_generator();
		if (!(*pieces)[i] || ((status = fill_piece(fd, (*pieces)[i])) == ERROR))
		{
			while (--i > 0)
				freepiece(&(*pieces)[i + 1]);
			close(fd);
			return (ERROR);
		}
		if (status == SUCCESS_END)
			break ;
		i++;
	}
	return (SUCCESS);
}

int		fillit_input(char *filename, t_piece ***pieces)
{
	size_t	rd;
	int		fd;

	rd = 1;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ERROR);
	if (!(*pieces = (t_piece**)malloc(sizeof(t_piece*) * (26 + 1))))
	{
		close(fd);
		return (ERROR);
	}
	if (fillit_input2(fd, pieces) == ERROR)
		return (ERROR);
	close(fd);
	return (SUCCESS);
}
