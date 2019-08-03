/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:35:55 by filip             #+#    #+#             */
/*   Updated: 2019/08/03 14:59:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		*get_folder(void)
{
	char	*path;

	path = NULL;
	if (ft_getenv("PWD") && ft_getenv("HOME"))
	{
		if (!(path = ft_strdup(ft_strrchr(ft_getenv("PWD"), '/') + 1)))
			print_error("42sh", "malloc() error", NULL, ENOMEM);
		if (!ft_strcmp(ft_getenv("PWD"), ft_getenv("HOME")))
		{
			ft_strclr(path);
			ft_strcat(path, "~");
		}
	}
	return (path);
}

char		*get_path(void)
{
	char	*path;

	path = NULL;
	if (ft_getenv("PWD") && ft_getenv("HOME"))
	{
		if (!ft_strncmp(ft_getenv("PWD"), ft_getenv("HOME"),
		ft_strlen(ft_getenv("HOME"))))
		{
			if (!(path = ft_strjoin("~", ft_getenv("PWD")
			+ ft_strlen(ft_getenv("HOME")))))
				print_error("42sh", "malloc() error", NULL, ENOMEM);
		}
		else
		{
				if (!(path = ft_strdup(ft_getenv("PWD"))))
			print_error("42sh", "malloc() error", NULL, ENOMEM);
		}
	}
	return (path);
}
