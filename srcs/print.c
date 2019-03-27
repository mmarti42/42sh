/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:53:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/27 18:31:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_message(void)
{
	ft_putstr(get_var("PWD"));
	ft_putchar(':');
}

void	print_environ(void)
{
	short	i;

	i = -1;
	while (env_cp[++i])
	{
		ft_putstr(env_cp[i]);
		ft_putchar('\n');
	}
}

void	print_error(char *name, char *str, char *command, int p)
{	
	errno_f = p;
	ft_putstr(name);
	if (str)
	{
		ft_putstr(": ");
		ft_perror(str);
	}
	if (command)
	{
		ft_putstr(": ");
		ft_putstr(command);
	}
	ft_putchar('\n');
	exit(0);
}