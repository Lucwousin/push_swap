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

/**
 * After splitting from one stack to another, all the values we did not push
 * will be on the bottom of the stack. If we had partitions in the stack we
 * don't want those to now be on top, so we have to rotate the stack enough
 * to have our partitions back on the bottom. If the partition is smaller than
 * the values we have on the bottom, rotating forwards costs less moves than
 * reversed.
 */
static void	rewind(
		t_s_id n,
		t_stack *s[2],
		int32_t rotated,
		t_ins_lst *list)
{
	int32_t	count;
	bool	reversed;

	reversed = rotated < get_partition(s[n]);
	if (!reversed)
		count = get_partition(s[n]) + 1;
	else
		count = rotated;
	while (count--)
		do_rotate(n, s, reversed, list);
}

/**
 * Split from stack n to the other stack, comparing with the comparator cmp.
 * Cmp will be <= for n == A, > for n == B
 * If we're splitting from stack B to stack A and there's 20 or less values in
 * the top partition, use selection sort to directly sort all the values.
 *
 * I know those indentations for the if/else are wrong, but norminette
 * disagrees with that.
 */
static bool	split(t_s_id n, t_stack **s, t_ins_lst *list, t_cmp cmp)
{
	t_splinf	info;

	info.count = partition_size(s[n]);
	if (info.count == 2)
		do_swap(n, s, list);
	if (info.count <= 2 && n == A)
		return (false);
	if (n == A && s[B]->top >= 0)
		partition(s[B]);
	if (info.count <= SEL_SORT_CUTOFF && n == B)
		return (selection_sort(s, list, info.count));
	info.median = find_median(s[n], info.count);
	info.rotated = 0;
	while (info.count--)
		if (compare(get_top(s[n]), info.median, cmp))
			do_push(n, s, list);
	else
	{
		do_rotate(n, s, false, list);
		++info.rotated;
	}
	if (s[n]->p_idx != -1)
		rewind(n, s, info.rotated, list);
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
	while (idx++ < s->top)
		if (s->arr[idx] != ((int32_t) s->size - 1) - idx)
			break ;
	if (idx == 0)
		return ;
	s->partitions[0] = idx - 1;
	s->p_idx = 0;
}

static void	tri_split(t_stack *s[2], t_ins_lst *list)
{
	int32_t	medians[2];
	int32_t	count;
	int32_t	value;
	int32_t	bot_part_b;

	count = (int32_t) s[A]->top + 1;
	medians[0] = count / 3;
	medians[1] = count * 2 / 3;
	bot_part_b = -1;
	while (count--)
	{
		value = get_top(s[A]);
		if (value > medians[1])
		{
			run_action(RA, s[A], s[B], list);
			continue ;
		}
		run_action(PB, s[A], s[B], list);
		if (value <= medians[0])
		{
			run_action(RB, s[A], s[B], list);
			++bot_part_b;
		}
	}
	s[B]->partitions[++s[B]->p_idx] = bot_part_b;
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
	s[B] = create_stack(a->size, calculate_needed_partitions(a->size));
	if (!s[B])
	{
		delete_stack(a);
		error();
	}
	if (s[A]->size >= TRI_SPLIT_CUTOFF)
		tri_split(s, list);
	while (true)
	{
		update_sorted_partition(s[A]);
		a_is_sorted = get_partition(s[A]) == s[A]->top;
		if (a_is_sorted && s[B]->top == -1)
			break ;
		if (!a_is_sorted)
			while (split(A, s, list, LE))
				update_sorted_partition(s[A]);
		split(B, s, list, GT);
	}
	delete_stack(s[B]);
}
