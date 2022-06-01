/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   selection_sort.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 17:03:58 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/29 17:03:58 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

/**
 * Find the minimum and maximum value and their indices in a section of stack.
 * Puts the min value in limits[0][0], and the max value in limits[1][0]
 * Their indices will go in limits[n][1]
 */
static void	find_minmax_i(
	t_stack *stack,
	int32_t limits[2][2],
	int32_t i,
	int32_t end)
{
	int32_t	value;

	while (i >= end)
	{
		value = stack->arr[i];
		if (value < limits[0][0])
		{
			limits[0][0] = value;
			limits[0][1] = i;
		}
		if (value > limits[1][0])
		{
			limits[1][0] = value;
			limits[1][1] = i;
		}
		--i;
	}
}

/**
 * Find the minimum and the maximum value in the current partition
 * which could be rotated by rotation amount. Rotation will never be negative.
 */
static void	find_minmax(
	t_stack *stack,
	int32_t limits[2][2],
	int32_t count,
	int32_t rotation)
{
	int32_t	i;
	int32_t	bottom;

	limits[0][0] = INT32_MAX;
	limits[1][0] = INT32_MIN;
	i = stack->top;
	bottom = ft_max(0, i - count + rotation);
	find_minmax_i(stack, limits, i, bottom);
	rotation = ft_min(stack->top + 1, rotation);
	find_minmax_i(stack, limits, rotation - 1, 0);
}

/**
 * Calculate the amount of rotations needed to get the smallest or the biggest
 * value on their correct place in the other stack. Most of this is rotating,
 * but the smallest value will also need to be rotated to the back of the other
 * stack.
 */
static t_cost	find_cheapest(t_stack *stack, int32_t limits[2][2])
{
	t_cost	costs[2];

	costs[0].smaller = true;
	costs[1].smaller = false;
	if (limits[0][1] < stack->top / 2)
		costs[0].count = -(limits[0][1] + 1);
	else
		costs[0].count = stack->top - limits[0][1];
	if (limits[1][1] < stack->top / 2)
		costs[1].count = -(limits[1][1] + 1);
	else
		costs[1].count = stack->top - limits[1][1];
	if (abs(costs[0].count) + 1 < abs(costs[1].count))
		return (costs[0]);
	else
		return (costs[1]);
}

/**
 * Perform a selection sort on the top partition of stack B.
 * This could be used for stack A as well, but it only increased command count.
 *
 * First, find the highest and the lowest value in the stack.
 * Then find out which one of those will be cheaper to get to their desired pos
 * The biggest value can just stay on the top of stack A, the smallest one gets
 * rotated to the back of stack A.
 * Instead of rewinding the stack back to it's original position, we keep track
 * of how many rotations we've done, and use that info to know where the
 * partition starts and ends.
 */
bool	selection_sort(t_stack *s[2], t_ins_lst *list, int32_t count)
{
	int32_t			limits[2][2];
	int32_t			rotation;
	t_cost			plan;

	rotation = 0;
	while (count--)
	{
		find_minmax(s[B], limits, count, rotation);
		plan = find_cheapest(s[B], limits);
		do_rotate_n(B, s, plan.count, list);
		do_push(B, s, list);
		if (plan.smaller)
			do_rotate(A, s, false, list);
		rotation += plan.count;
	}
	while (s[A]->arr[0] < get_top(s[A]))
		do_rotate(A, s, true, list);
	if (s[B]->p_idx != -1)
		--s[B]->p_idx;
	return (true);
}
