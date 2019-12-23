/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init_hash2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:49:46 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 18:49:48 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_hash	**init_standart_templates_other(t_hash **table, int hash_size)
{
	char	symb[2];

	symb[1] = '\0';
	symb[0] = RL_K_CTRL_X;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_x, hash_size);
	symb[0] = RL_K_CTRL_V;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_v, hash_size);
	symb[0] = RL_K_CTRL_C;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_c, hash_size);
	symb[0] = RL_K_ENTER;
	table = push_hash(table, symb, (void*)&rl_k_enter, hash_size);
	symb[0] = RL_K_CTRL_H;
	table = push_hash(table, symb, (void*)&rl_k_bcsp, hash_size);
	symb[0] = RL_K_CTRL_R;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_r, hash_size);
	symb[0] = RL_K_BCSP;
	table = push_hash(table, symb, (void*)&rl_k_bcsp, hash_size);
	symb[0] = RL_K_CTRL_D;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_d, hash_size);
	symb[0] = RL_K_CTRL_J;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_j, hash_size);
	symb[0] = RL_K_ESC;
	table = push_hash(table, symb, (void*)&rl_k_esc, hash_size);
	symb[0] = RL_K_CTRL_G;
	return (push_hash(table, symb, (void*)&rl_k_ctrl_g, hash_size));
}

t_hash	**init_emacs_hash_other(t_hash **table, int hash_size)
{
	char	symb[2];

	symb[1] = '\0';
	symb[0] = RL_K_CTRL_B;
	table = push_hash(table, symb, (void*)&rl_k_left, hash_size);
	symb[0] = RL_K_CTRL_F;
	table = push_hash(table, symb, (void*)&rl_k_right, hash_size);
	symb[0] = RL_K_CTRL_A;
	table = push_hash(table, symb, (void*)&rl_k_home, hash_size);
	symb[0] = RL_K_CTRL_E;
	table = push_hash(table, symb, (void*)&rl_k_end, hash_size);
	symb[0] = RL_K_CTRL_P;
	table = push_hash(table, symb, (void*)&rl_k_up, hash_size);
	symb[0] = RL_K_CTRL_N;
	table = push_hash(table, symb, (void*)&rl_k_down, hash_size);
	symb[0] = RL_K_CTRL_L;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_l, hash_size);
	symb[0] = RL_K_CTRL_U;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_u, hash_size);
	symb[0] = RL_K_CTRL_K;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_k, hash_size);
	symb[0] = RL_K_CTRL_Y;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_v, hash_size);
	return (table);
}

t_hash	**init_vi_hash_other(t_hash **table, int hash_size)
{
	table = push_hash(table, RL_K_X_UPPER, (void*)&rl_k_x_upper, hash_size);
	table = push_hash(table, RL_K_X_LOWER, (void*)&rl_k_x_lower, hash_size);
	table = push_hash(table, RL_K_V, (void*)&rl_k_v, hash_size);
	table = push_hash(table, RL_K_F_LOWER, (void*)&rl_k_f_lower, hash_size);
	table = push_hash(table, RL_K_F_UPPER, (void*)&rl_k_f_upper, hash_size);
	table = push_hash(table, RL_K_SEMICOLON, (void*)&rl_k_semicolon, hash_size);
	table = push_hash(table, RL_K_COMMA, (void*)&rl_k_comma, hash_size);
	table = push_hash(table, RL_K_R_LOWER, (void*)&rl_k_r_lower, hash_size);
	table = push_hash(table, RL_K_R_UPPER, (void*)&rl_k_r_upper, hash_size);
	table = push_hash(table, RL_K_P_LOWER, (void*)&rl_k_p_lower, hash_size);
	table = push_hash(table, RL_K_P_UPPER, (void*)&rl_k_ctrl_v, hash_size);
	table = push_hash(table, RL_K_Y_UPPER, (void*)&rl_k_y_upper, hash_size);
	table = push_hash(table, RL_K_D_UPPER, (void*)&rl_k_d_upper, hash_size);
	table = push_hash(table, RL_K_C_UPPER, (void*)&rl_k_d_upper, hash_size);
	return (table);
}