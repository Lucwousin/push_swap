/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_quicksort.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/28 19:32:15 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/28 19:32:15 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

/**
 * Check if the top 2 values of stack n should be swapped.
 * If yes, check if swapping other stack's values also improves performance
 *
 * The swap[n] assignments are spread out over multiple lines because the norm
 * could not handle my beautiful code. (No, it's a bug)
 * https://github.com/42School/norminette/issues/319
 */
static void	do_swap(t_stack *a, t_stack *b, t_stack_name n, t_action_list *list)
{
	bool	swap[2];

	swap[A] = false;
	swap[B] = false;
	if (a->top > 0)
		swap[A] = a->arr[a->top] > a->arr[a->top - 1];
	if (b->top > 0)
		swap[B] = b->arr[b->top] < b->arr[b->top - 1];
	if (!swap[n])
		return ;
	if (swap[A] && swap[B])
		run_action(SS, a, b, list);
	else if (swap[A])
		run_action(SA, a, b, list);
	else if (swap[B])
		run_action(SB, a, b, list);
}

/**
 * Find the median of the last partition
 */
int32_t	find_median(t_stack *s)
{
	int32_t	count;
	int32_t	value;
	int32_t	limits[2];
	
	count = s->top + 1;
	if (s->p_idx != -1)
		count -= (s->partitions[s->p_idx] + 1);
	limits[0] = INT32_MAX;
	limits[1] = INT32_MIN;
	while (count--)
	{
		value = s->arr[s->top - count];
		limits[0] = ft_min(limits[0], value);
		limits[1] = ft_max(limits[1], value);
	}
	return ((limits[0] + limits[1]) / 2);
}

void	rewind_a(t_stack *a, int32_t rotated, t_action_list *list)
{
	t_action	action;
	int32_t		count;
	
	if (rotated < a->partitions[a->p_idx])
		action = RRA;
	else
		action = RA;
	if (action == RRA)
		count = rotated;
	else
		count = a->partitions[a->p_idx] + 1;
	while (count--)
		run_action(action, a, NULL, list);
}

void	rewind_b(t_stack *b, int32_t rotated, t_action_list *list)
{
	t_action	action;
	int32_t		count;

	if (rotated < b->partitions[b->p_idx])
		action = RRB;
	else
		action = RB;
	if (action == RRB)
		count = rotated;
	else
		count = b->partitions[b->p_idx] - b->top;
	while (count--)
		run_action(action, NULL, b, list);
}

bool	split_a(t_stack *a, t_stack *b, t_action_list *list)
{
	int32_t	count;
	int32_t	median;
	int32_t	rotated;

	count = a->top + 1;
	if (a->p_idx != -1)
		count -= (a->partitions[a->p_idx] + 1);
	if (count == 2)
	{
		do_swap(a, b, A, list);
		return (false);
	}
	if (count <= 1)
		return (false);
	if (b->top != -1)
		b->partitions[++b->p_idx] = b->top;
	median = find_median(a);
	rotated = 0;
	while (count--)
	{
		if (a->arr[a->top] <= median)
		{
			run_action(PB, a, b, list);
			continue ;
		}
		run_action(RA, a, b, list);
		rotated++;
	}
	if (a->p_idx != -1)
		rewind_a(a, rotated, list);
	return (true);
}

void	find_minmax(t_stack *stack, int32_t limits[2][2], int32_t count, int32_t rotation)
{
	int32_t	i;
	int32_t	bottom;
	int32_t	value;

	limits[0][0] = INT32_MAX;
	limits[1][0] = INT32_MIN;
	i = stack->top;
	bottom = ft_max(0, i - count + rotation);
	while (i >= bottom)
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
	rotation = ft_min(stack->top + 1, rotation);
	while (rotation-- > 0)
	{
		value = stack->arr[rotation];
		if (value < limits[0][0])
		{
			limits[0][0] = value;
			limits[0][1] = rotation;
		}
		if (value > limits[1][0])
		{
			limits[1][0] = value;
			limits[1][1] = rotation;
		}
	}
}

t_cost	find_cheapest(t_stack *stack, int32_t limits[2][2])
{
	t_cost	costs[2];

	if (limits[0][1] < stack->top / 2)
		costs[0] = (t_cost){-(limits[0][1] + 1), true};
	else
		costs[0] = (t_cost){stack->top - limits[0][1], true};
	if (limits[1][1] < stack->top / 2)
		costs[1] = (t_cost){-(limits[1][1] + 1), false};
	else
		costs[1] = (t_cost){stack->top - limits[1][1], false};

	if (abs(costs[0].count) + 2 < abs(costs[1].count) + 1)
		return (costs[0]);
	else
		return (costs[1]);
}

void	do_rotate(t_stack *a, t_stack *b, int32_t rots[2], t_action_list *list)
{
	while (rots[0])
		if (rots[0] > 0)
		{
			run_action(RA, a, b, list);
			--rots[0];
		}
		else
		{
			run_action(RRA, a, b, list);
			++rots[0];
		}
	while (rots[1])
		if (rots[1] > 0)
		{
			run_action(RB, a, b, list);
			--rots[1];
		}
		else
		{
			run_action(RRB, a, b, list);
			++rots[1];
		}
}

void	select_sort(t_stack *a, t_stack *b, t_action_list *list, int32_t count)
{
	int32_t	limits[2][2];
	int32_t	rotation;
	t_cost	plan;

	rotation = 0;
	while (count--)
	{
		find_minmax(b, limits, count, rotation);
		plan = find_cheapest(b, limits);
		do_rotate(a, b, (int32_t[]){0, plan.count}, list);
		run_action(PA, a, b, list);
		if (plan.smaller)
			run_action(RA, a, b, list);
		rotation += plan.count;
	}
	while (a->arr[0] < a->arr[a->top])
		run_action(RRA, a, b, list);
	if (b->p_idx != -1)
		--b->p_idx;
}

void	split_b(t_stack *a, t_stack *b, t_action_list *list) {
	int32_t	count;
	int32_t	median;
	int32_t	rotated;

	median = find_median(b);
	count = b->top + 1;
	if (b->p_idx != -1)
		count -= (b->partitions[b->p_idx] + 1);
	if (count == 2)
	{
		do_swap(a, b, B, list);
		run_action(PA, a, b, list);
		count = 1;
	}
	if (count == 1)
	{
		run_action(PA, a, b, list);
		if (b->p_idx != -1)
			--b->p_idx;
		return ;
	}
	if (count <= 20)
		return (select_sort(a, b, list, count));
	rotated = 0;
	while (count-- && b->top >= 0)
	{
		if (b->arr[b->top] > median)
		{
			run_action(PA, a, b, list);
			continue;
		}
		run_action(RB, a, b, list);
		++rotated;
	}
	if (b->p_idx != -1)
		rewind_b(b, rotated, list);
}

/**
 * Update the partitions in stack A
 *
 * partitions[p_idx] will contain the index to the last sorted number on stack.
 * If p_idx is -1, nothing is sorted.
 */
static void	update_sorted_partition(t_stack *s)
{
	int32_t	idx;

	if (s->top == -1)
		return ;
	idx = -1;
	while (idx++ < s->top) {
		if (s->arr[idx] != ((int32_t) s->size - 1) - idx)
			break ;
	}
	if (idx == 0)
		return ;
	s->partitions[++s->p_idx] = idx - 1;
}

void	ps_quicksort(t_stack *a, t_action_list *list)
{
	bool	a_is_sorted;
	t_stack	*b;

	b = create_stack(a->size);
	if (!b) // TODO: change
		return ;
	while (true)
	{
		update_sorted_partition(a);
		a_is_sorted = a->p_idx != -1 && a->partitions[a->p_idx] == a->top;
		if (a_is_sorted && b->top == -1)
			break ;
		if (!a_is_sorted)
			while (split_a(a, b, list))
				update_sorted_partition(a);
		split_b(a, b, list);
	}
	delete_stack(b);
}