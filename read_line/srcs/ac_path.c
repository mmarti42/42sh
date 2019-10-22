/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:50:48 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/22 22:43:01 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ac_path(char *word, t_line *line)
{
	char	*file;
	char	**content;
	char	*pwd;
	char	*full_path;

	file = NULL;
	ac_word_split(word, &file);
	if (!(pwd = ft_getenv("PWD")))
		err_exit(g_argv[0], "pwd error", NULL, NOERROR);
	if (!(full_path = ft_strnew(ft_strlen(pwd) + ft_strlen(word) + 1)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	full_path = ft_strcat(full_path, pwd);
	if (word && *word)
		full_path = ft_strcat(ft_strcat(full_path, "/"), word);
	if (!(content = ft_dir_content(full_path, 0)))
		err_exit(g_argv[0], "opendir() error", NULL, ENOMEM);
	ft_strdel(&full_path);
	ac_print_path(content, file, line);
	ft_strdel(&file);
	ft_free_dar(content);
}

void	ac_print_path(char **content, char *file, t_line *line)
{
	size_t	i;
	char	*paths[ft_darlen(content)];
	short	pos;

	i = 0;
	while ((paths[i] = ac_get_path(file, content)))
		++i;
	if (i == 1)
	{
		print_symb(paths[0] + ft_strlen(file), line);
		print_symb("/", line);
	}
	else if (i > 1)
	{
		pos = line->cord->pos;
		go_right(ft_strlen(line->buffer.buffer + pos), line->cord);
		ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
		ft_putchar_fd(NEW_LINE, STDIN_FILENO);
		ac_print_params(paths, line->cord->ws_col);
		g_line_flags |= AUTOCOM;
		line->cord->pos = pos;
		k_enter(line);
	}
}

char	*ac_get_path(char *file, char **content)
{
	static size_t	i;
	int				len;
	char			*data;

	len = ft_strlen(file);
	while (content[i])
	{
		data = content[i];
		if (!len || !ft_strncmp(data, file, len))
		{
			++i;
			return (data);
		}
		++i;
	}
	i = 0;
	return (NULL);
}

void	ac_word_split(char *word, char **file)
{
	int		i;
	int		j;

	if (!word)
		return ;
	i = ft_strlen(word);
	j = i;
	while (i >= 0 && word[i] != '/')
		--i;
	if (i < 0)
		++i;
	if (word[i] == '/')
		word[i++] = '\0';
	if (!(*file = ft_strdup(word + i)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	if (i == 0)
		ft_strclr(word);
}
