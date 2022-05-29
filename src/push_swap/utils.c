/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucas <lucas@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/28 20:43:08 by lucas         #+#    #+#                 */
/*   Updated: 2022/05/28 20:43:08 by lucas         ########   odam.nl         */
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
void	do_push(t_stack_name from, t_stack *a, t_stack *b, t_ins_lst *list)
{
	static const t_action	pushes[2] = {[A] = PB, [B] = PA};

	run_action(pushes[from], a, b, list);
}

/**
 * Rotate the stack. If rev, rotate reversed.
 *
 * Because norminette only allows 4 params to a function we give the stack as
 * both params for run_action. Make sure you give the correct stack as param!
 */
void	do_rotate(t_stack_name name, t_stack *stack, bool rev, t_ins_lst *list)
{
	static const t_action	rotates[2][2] = {
	[false] = {[A] = RA, [B] = RB},
	[true] = {[A] = RRA, [B] = RRB}
	};

	run_action(rotates[rev][name], stack, stack, list);
}

/**
 * Rotate stack n amt of times. If amt is negative, rotate reversed
 */
void	do_rotate_n(
	t_stack_name n,
	t_stack *stack,
	int32_t amt,
	t_ins_lst *list)
{
	bool	neg;

	neg = amt < 0;
	while (amt)
	{
		do_rotate(n, stack, neg, list);
		if (amt > 0)
			amt--;
		else if (amt < 0)
			amt++;
	}
}

/**
 * Get the size of the top partition of stack.
 * If the stack has no partitions yet, return the size of the stack.
 */
int32_t	partition_size(t_stack *stack)
{
	int32_t	partition;

	partition = get_partition(stack);
	if (partition == -1)
		return (stack->top + 1);
	else
		return (stack->top + 1 - (partition + 1));
}
