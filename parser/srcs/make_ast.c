/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 23:37:47 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/09 17:24:49 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			clean_tree(t_ast *ast)
{
	if (!ast)
		return ;
	clean_tree(ast->left);
	clean_tree(ast->right);
	free(ast);
}

static int		status_update(int rules[RULES_NUM][3],
int *status, t_lex_tkn **list)
{
	int i;

	i = 0;
	while (i < RULES_NUM)
	{
		if (rules[i][0] == (int)(*list)->class
		&& rules[i][1] == (int)(*(list + 1))->class)
		{
			*status = rules[i][2];
			return (0);
		}
		i++;
	}
	return (-1);
}

static t_ast	*new_node(t_lex_tkn **token)
{
	t_ast *new;

	if (!(new = (t_ast *)malloc(sizeof(t_ast))))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	new->token = token;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

static void		insert(t_ast *node, t_ast **root,
enum e_lex_tkn_class node_class)
{
	t_ast *tmp;
	t_ast *prev_node;

	if ((*(*root)->token)->class < node_class)
	{
		node->left = *root;
		*root = node;
		return ;
	}
	tmp = *root;
	while (tmp && node_class <= (*tmp->token)->class)
	{
		prev_node = tmp;
		tmp = tmp->right;
	}
	if (tmp)
		node->left = tmp;
	prev_node->right = node;
}

int				make_ast(t_lex_tkn **list, t_ast **root)
{
	int			curr_status;
	int			old_status;
	static int	rules[RULES_NUM][3] = {{C_WORD, C_WORD, C_WORD},
	{C_WORD, C_REDIR, C_WORD}, {C_REDIR, C_WORD, C_WORD},
	{C_WORD, C_SEP, C_SEP}, {C_SEP, C_WORD, C_WORD},
	{C_SEP, C_SEP, C_SEP}, {C_PIPE, C_REDIR, C_REDIR},
	{C_PIPE, C_WORD, C_WORD}, {C_WORD, C_PIPE, C_PIPE},
	{C_WORD, C_END, C_WORD}, {C_WORD, C_LOG_OPERS, C_LOG_OPERS},
	{C_LOG_OPERS, C_WORD, C_WORD}, {C_SEP, C_END, C_SEP},
	{C_LOG_OPERS, C_END, C_LOG_OPERS}, {C_SEP, C_REDIR, C_REDIR}};

	curr_status = (*list)->class;
	*root = new_node(list);
	if (curr_status != C_WORD && curr_status != C_REDIR && curr_status != C_SEP)
		return (syntax_err(*list));
	while (*(list + 1))
	{
		old_status = curr_status;
		if (status_update(rules, &curr_status, list) < 0)
			return (syntax_err(*(list + 1)));
		list++;
		if (curr_status != old_status)
			insert(new_node(list), root, (*list)->class);
	}
	return (0);
}
