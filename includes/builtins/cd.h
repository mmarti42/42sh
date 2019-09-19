/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:55:40 by filip             #+#    #+#             */
/*   Updated: 2019/09/19 21:38:29 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include <dirent.h>
# include <unistd.h>
# include "libft.h"
# define MAXDIR 4097

void			cd(int argc, char **argv, char **env_cp);
void			check_ch_dir(int argc, char **argv);
char			*check_request(char **argv, char *path);
char			*check_cdpath(char *path);
#endif
