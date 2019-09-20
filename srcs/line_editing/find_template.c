/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_template.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:20:30 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/20 17:38:44 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	find_templ(char *str, t_line *line)
{
	t_temp	*temp;

	temp = line->templates;
	while (temp)
	{
		if (match_str_templ(str, temp->template))
			if ((temp->handler(line)))
				break ;
		temp = temp->next;
	}
}

int		match_str_templ(char *str, char *templ)
{
	if (str && templ)
	{
		if (!(*str) && !(*templ))
			return (1);
		if (*str == *templ)
			return (match_str_teml(str + 1, templ + 1));
	}
	return (0);
}
