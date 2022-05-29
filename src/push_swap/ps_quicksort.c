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
static void	do_swap(t_stack *a, t_stack *b, t_stack_name n, t_ins_lst *list)
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

bool	selection_sort(t_stack *s[2], t_ins_lst *list, int32_t count, t_cmp cmp)
{
	int32_t			limits[2][2];
	int32_t			rotation;
	t_cost			plan;

	rotation = 0;
	while (count--)
	{
		find_minmax(s[B], limits, count, rotation);
		plan = find_cheapest(s[B], limits);
		do_rotate_n(B, s[B], plan.count, list);
		do_push(B, s[A], s[B], list);
		if (plan.smaller)
			do_rotate(A, s[A], false, list);
		rotation += plan.count;
	}
	while (!compare(s[A]->arr[0], get_top(s[A]), cmp))
		do_rotate(A, s[A], true, list);
	if (s[B]->p_idx != -1)
		--s[B]->p_idx;
	return (false);
}

/**
 * After splitting from one stack to another, all the values we did not push
 * will be on the bottom of the stack. If we had partitions in the stack we
 * don't want those to now be on top, so we have to rotate the stack enough
 * to have our partitions back on the bottom. If the partition is smaller than
 * the values we have on the bottom, rotating forwards costs less moves than
 * reversed.
 */
static void	rewind(t_stack_name n, t_stack *stack, int32_t rotated, t_ins_lst *list)
{
	int32_t	count;
	bool	reversed;

	reversed = rotated < get_partition(stack);
	if (!reversed)
		count = get_partition(stack) + 1;
	else
		count = rotated;
	while (count--)
		do_rotate(n, stack, reversed, list);
}

/**
 * Split from stack n to the other stack, comparing with the comparator cmp.
 * Cmp will be <= for n == A, > for n == B
 * If we're splitting from stack B to stack A and there's 20 or less values in
 * the top partition, use selection sort to directly sort all the values.
 */
static bool	split(t_stack_name n, t_stack **s, t_ins_lst *list, t_cmp cmp)
{
	t_splinf	info;

	info.count = partition_size(s[n]);
	if (info.count == 2)
		do_swap(s[A], s[B], n, list);
	if (info.count <= 2 && n == A)
		return (false);
	if (n == A && s[B]->top >= 0)
		partition(s[B], s[B]->top);
	if (info.count <= 20 && n == B)
		return (selection_sort(s, list, info.count, cmp));
	info.median = find_median(s[n], info.count);
	info.rotated = 0;
	while (info.count--)
		if (compare(get_top(s[n]), info.median, cmp))
			do_push(n, s[A], s[B], list);
		else
		{
			do_rotate(n, s[n], false, list);
			++info.rotated;
		}
	if (s[n]->p_idx != -1)
		rewind(n, s[n], info.rotated, list);
	return (true);
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
	s->partitions[0] = idx - 1;
	s->p_idx = 0;
}

/**
 * Iterative quicksort
 *
 * First, push everything in A smaller than the median value to B.
 * Repeat until everything that's left in A is sorted.
 * Then, push everything in the top partition of B that's bigger than the
 * median back to stack A. If the top partition of B is small, a selection sort
 * is cheaper than just doing it all with quicksort.
 * If A is still sorted, we can split B again, else we split the top partition
 * of A back to B.. repeat.
 */
void	ps_quicksort(t_stack *a, t_ins_lst *list)
{
	bool	a_is_sorted;
	t_stack	*s[2];

	s[A] = a;
	s[B] = create_stack(a->size);
	if (!s[B]) // TODO: change
		return ;
	while (true)
	{
		update_sorted_partition(s[A]);
		a_is_sorted = s[A]->p_idx != -1 && get_partition(s[A]) == s[A]->top;
		if (a_is_sorted && s[B]->top == -1)
			break ;
		if (!a_is_sorted)
			while (split(A, s, list, LE))
				update_sorted_partition(s[A]);
		split(B, s, list, GT);
	}
	delete_stack(s[B]);
}