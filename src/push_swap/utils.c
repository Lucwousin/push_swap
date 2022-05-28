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

bool	compare(int32_t a, int32_t b, t_cmp cmp)
{
	if (cmp == LE)
		return (a <= b);
	if (cmp == GT)
		return (a > b);
	return (false);
}

void	do_push(t_stack_name from, t_stack *a, t_stack *b, t_ins_lst *list)
{
	static const t_action	pushes[2] = {[A] = PB, [B] = PA};

	run_action(pushes[from], a, b, list);
}

// Can only have 5 args...
void	do_rotate(t_stack_name name, t_stack *stack, bool rev, t_ins_lst *list)
{
	static const t_action	rotates[2][2] = {
	[false] = {[A] = RA, [B] = RB},
	[true] = {[A] = RRA, [B] = RRB}
	};

	run_action(rotates[rev][name], stack, stack, list);
}

void	do_rotate_n(t_stack_name name, t_stack *stack, int32_t amt, t_ins_lst *list)
{
	bool	neg;

	neg = amt < 0;
	while (amt)
	{
		do_rotate(name, stack, neg, list);
		if (amt > 0)
			amt--;
		else if (amt < 0)
			amt++;
	}
}

int32_t	partition_size(t_stack *stack)
{
	int32_t	partition;

	partition = get_partition(stack);
	if (partition == -1)
		return (stack->top + 1);
	else
		return (stack->top + 1 - (partition + 1));
}
