/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:58:11 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/13 19:38:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETATOR_H
# define INTERPRETATOR_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define LRED_OPEN O_RDWR
# define RRED_OPEN O_RDWR | O_CREAT | O_TRUNC
# define DRRED_OPEN O_RDWR | O_CREAT | O_APPEND
# define PERM_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define FD_LIMIT 8192
# define HEREDOC_FILE "/tmp/fucking_heredoc"

/*
**	interpretator.c
*/
void	interpret_ast(t_node *ast, t_term *term);
/*
**	pipes.c
*/
void	pipe_op(t_node *ast, t_term *term);
void	left_child(int *pid, int *pipes, t_node *expr, t_term *term);
void	right_child(int *pid, int *pipes, t_node *expr, t_term *term);
/*
**	redir.c
*/
void	redir_op(t_node *ast, t_term *term);
t_node	*exec_redir_command(t_node *ast, t_term *term);
int		get_expr_fd(t_node *ast);
int		open_red_file(char *name, token_type red_type, int acc, int mode);
/*
**	dup_fd.c
*/
int		copy_fd(int fd, int new_fd);
void	restore_fd(int back_fd, int new_fd);
/*
**	amp_redir.c
*/
void	amp_red(t_node *ast, t_term *term);
void	amprred_op(t_node *ast, t_term *term);
/*
**	closing_fd.c
*/
void	closing_fd(t_node *ast, t_term *term);
void	get_close_fd(char *str, int *left_fd, int *right_fd);
/*
**	exec.c
*/
void	make_command(char *buff, t_term *term);
void	find_command(char **args, t_term *term);
char	*check_command(char **args);
char	*check_bin(char **args, t_hash **hash_table, short hash_table_size);
/*
**	spec_symb.c
*/
char	*spec_symbols(char *args);
char	*tilda_expr(char *args);
char	*dollar_expr(char *args);
/*
**	parse_quotes.c
*/
char	**parse_quotes(char *buff);
char	*fill_quotes_buff(char **buff);
char	*remove_quotes(char **buff);
char	*remove_dquotes(char **buff);
#endif
