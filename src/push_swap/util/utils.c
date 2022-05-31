/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/28 20:43:08 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/28 20:43:08 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Compare using the comparator!
 */
bool	compare(int32_t a, int32_t b, t_cmp cmp)
{
	if (cmp == LE)
		return (a <= b);
	if (cmp == GT)
		return (a > b);
	return (false);
}

/**
 * Push from stack to other stack
 */
void	do_push(t_s_id from, t_stack *s[2], t_ins_lst *list)
{
	static const t_action	pushes[2] = {[A] = PB, [B] = PA};

	run_action(pushes[from], s[A], s[B], list);
}

/**
 * Rotate the stack. If rev, rotate reversed.
 *
 * Because norminette only allows 4 params to a function we give the stack as
 * both params for run_action. Make sure you give the correct stack as param!
 */
void	do_rotate(t_s_id n, t_stack *s[2], bool rev, t_ins_lst *list)
{
	static const t_action	rotates[2][2] = {
	[false] = {[A] = RA, [B] = RB},
	[true] = {[A] = RRA, [B] = RRB}
	};

	run_action(rotates[rev][n], s[A], s[B], list);
}

/**
 * Rotate stack n amt of times. If amt is negative, rotate reversed
 */
void	do_rotate_n(t_s_id n, t_stack *s[2], int32_t amt, t_ins_lst *list)
{
	bool	neg;

	neg = amt < 0;
	while (amt)
	{
		do_rotate(n, s, neg, list);
		if (amt > 0)
			amt--;
		else if (amt < 0)
			amt++;
	}
}
