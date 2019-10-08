/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:32:00 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/02 15:31:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_putstr_cord(char *str, t_cord *cord)
{
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		if (++cord->x_cur >= cord->ws_col)
		{
			ft_putchar_fd(NEW_LINE, STDIN_FILENO);
			cord->x_cur = 0;
			if (cord->y_cur >= cord->ws_row - 1)
				(cord->y_start)--;
			else
				(cord->y_cur)++;
		}
		str++;
		cord->pos++;
	}
	set_end_cord(cord);
}

void		ft_putstr_highlight(char *str, short start, short end, t_cord *cord)
{
	short	i;
	char	symb[2];
	short	pos;

	pos = cord->pos;
	go_left(cord->pos, cord);
	i = -1 + cord->pos;
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	if (start <= i)
		HIGHLIGHT(STDIN_FILENO);
	symb[1] = '\0';
	while (str[++i])
	{
		if (i == start)
			HIGHLIGHT(STDIN_FILENO);
		if (i == end)
			STANDART(STDIN_FILENO);
		symb[0] = str[i];
		ft_putstr_cord(symb, cord);
	}
	STANDART(STDIN_FILENO);
	go_left(cord->pos - pos, cord);
	g_line_flags |= HIGHLIGHT_TEXT;
}

void		disable_highlight(char *buffer, t_cord *cord)
{
	short	pos;

	g_line_flags &= ~HIGHLIGHT_TEXT;
	pos = cord->pos;
	ft_putstr_fd(SAVE_CUR, STDIN_FILENO);
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_cord(buffer + cord->pos, cord);
	go_left(cord->pos - pos, cord);
	ft_putstr_fd(RESTORE_CUR, STDIN_FILENO);
	cord->highlight_pos = 0;
}

void		disable_history(t_line *line)
{
	t_cord	*cord;
	short	pos;

	g_line_flags &= ~HISTORY_SEARCH;
	cord = line->cord;
	pos = cord->pos;
	ft_putstr_fd(SAVE_CUR, STDIN_FILENO);
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_cord(line->buffer.buffer + cord->pos, cord);
	go_left(cord->pos - pos, cord);
	ft_putstr_fd(RESTORE_CUR, STDIN_FILENO);
	ft_strclr(line->history_search.buffer);
}

void		find_history(t_line *line)
{
	t_cord	*cord;
	char	**history;

	cord = line->cord;
	go_left(cord->pos, cord);
	set_start_cord(cord);
	set_end_cord(cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	history = g_history.history_buff;
	while (*history)
	{
		if (ft_strstr(*history, line->history_search.buffer))
			break ;
		history++;
	}
	check_malloc_len_buffer(&line->buffer, *history);
	ft_strcpy(line->buffer.buffer + cord->pos, *history);
	ft_putstr_cord(line->buffer.buffer + cord->pos, cord);
	k_ctrl_r(line);
}