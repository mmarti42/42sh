/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 05:50:22 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/11 16:26:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char				*ft_getalias(char *name, char **varlist)
{
	char	*tmp;
	long	varlen;

	if (!name || !*name)
		return (NULL);
	while (*varlist)
	{
		tmp = ft_strchr(*varlist, '=');
		varlen = tmp - *varlist;
		if ((long)ft_strlen(name) == varlen &&
				!ft_strncmp(name, *varlist, varlen))
			return (*varlist);
		++varlist;
	}
	return (NULL);
}

static int			check_cycle(char *alias, t_cycle_list *l, t_lex_tkn **curr)
{
	while (l)
	{
		if (!ft_strcmp(alias, l->name))
		{
			if (curr && ft_strcmp((*curr)->value, l->name))
				return (1);
		}
		l = l->next;
	}
	return (0);
}

static t_lex_tkn	**get_alias_tkn(t_lex_tkn **tkn, char *val,
													t_cycle_list **l)
{
	char		*alias;
	t_lex_tkn	**new_tkn;
	char		*tmp;

	if (!(alias = ft_getalias(val, g_aliases.vars)))
		return (tkn);
	if (check_cycle(alias, *l, tkn))
	{
		lex_del_tkns(tkn);
		return (NULL);
	}
	add_to_cycle_list(alias, l);
	tmp = ft_strchr(alias, '=') + 1;
	if (!tkn)
		new_tkn = lex_get_tkns(&tmp);
	else
		new_tkn = lex_insert_tkns(tkn, lex_get_tkns(&tmp), 0);
	if (ft_strncmp(alias, (*new_tkn)->value, tmp - alias - 1))
		return (get_alias_tkn(new_tkn, (*new_tkn)->value, l));
	return (new_tkn);
}

static void			skip_delim(t_lex_tkn **list, int *i)
{
	while (list[*i]->class != C_END)
	{
		if (list[*i]->class == C_SEP || list[*i]->class == C_PIPE
				|| list[*i]->class == C_LOG_OPERS)
			break ;
		(*i)++;
	}
}

t_lex_tkn			**alias_handle(t_lex_tkn **list)
{
	t_lex_tkn			**new;
	int					i;
	static t_cycle_list	*l;

	i = 0;
	while (list[i]->class != C_END)
	{
		if (list[i]->type == T_WORD)
		{
			if ((new = get_alias_tkn(NULL, list[i]->value, &l)))
				list = lex_insert_tkns(list, new, i);
			skip_delim(list, &i);
			if (list[i]->class == C_END)
				break ;
		}
		i++;
	}
	free_cycle_list(l);
	l = NULL;
	return (list);
}
