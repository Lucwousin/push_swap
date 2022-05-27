#include "push_swap.h"
#include "libft.h"
#include "ft_printf.h"

void	do_swap(t_stack *a, t_stack *b, t_stack_name n, t_action_list *list)
{
	bool	swap[2];

	swap[A] = a->top > 0 && get_top(a) > get_i(a, a->top - 1);
	swap[B] = b->top > 0 && get_top(b) < get_i(b, b->top - 1);
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
		value = get_i(s, s->top - count);
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
		if (get_top(a) <= median)
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

void	find_minmax(t_stack *stack, int32_t limits[2][2])
{
	int32_t	i;
	int32_t	bottom;
	int32_t	value;

	limits[0][0] = INT32_MAX;
	limits[1][0] = INT32_MIN;
	i = stack->top;
	bottom = -1;
	if (stack->p_idx != -1)
		bottom = stack->partitions[stack->p_idx];
	while (i > bottom)
	{
		value = get_i(stack, i);
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

t_cost	find_cheapest(t_stack *stack, int32_t limits[2][2])
{
	int32_t	costs[2];

	costs[0] = stack->top - limits[0][1];
	costs[1] = stack->top - limits[1][1];
	if (costs[0] * 2 + 3 < costs[1] * 2 + 1)
		return ((t_cost){costs[0], true});
	else
		return ((t_cost){costs[1], false});
}

void	select_sort(t_stack *a, t_stack *b, t_action_list *list, int32_t count)
{
	int32_t	limits[2][2];
	int32_t	rewind;
	t_cost	plan;

	while (count--)
	{
		find_minmax(b, limits);
		plan = find_cheapest(b, limits);
		rewind = plan.count;
		while (plan.count--)
			run_action(RB, a, b, list);
		run_action(PA, a, b, list);
		if (plan.smaller)
			run_action(RA, a, b, list);
		if (b->p_idx != -1)
			while (rewind--)
				run_action(RRB, a, b, list);
	}
	while (get_i(a, 0) < get_i(a, 1))
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
	if (count <= 20)
		return (select_sort(a, b, list, count));
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
	}
	rotated = 0;
	while (count-- && b->top >= 0)
	{
		if (get_top(b) > median)
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

void	update_a_p(t_stack *s)
{
	int32_t	highest;
	int32_t	idx;

	if (s->top == -1)
		return ;
	highest = INT32_MIN;
	idx = -1;
	while (idx++ < s->top)
		highest = ft_max(highest, get_i(s, idx));
	idx = -1;
	while (idx++ < s->top) {
		if (get_i(s, idx) != highest - idx)
			break;
	}
	s->partitions[0] = idx - 1;
	if (s->partitions[0] == -1)
		s->p_idx = -1;
	else
		s->p_idx = 0;
}

void	print_stacks(t_stack *a, t_stack *b, const char *msg)
{
	ft_printf("\n%s\n", msg);
	int i = a->top, j = b->top;
	while (i >= 0 && j >= 0)
	{
		ft_printf("%3d | %3d\n", get_i(a, i), get_i(b, j));
		--i;
		--j;
	}
	while (i >= 0)
	{
		ft_printf("%3d | ---\n", get_i(a, i));
		--i;
	}
	while (j >= 0)
	{
		ft_printf("--- | %2d\n", get_i(b, j));
		--j;
	}
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
		a_is_sorted = is_sorted(a);
		if (a_is_sorted && b->top == -1)
			break ;
		update_a_p(a);
		if (!a_is_sorted)
			while (split_a(a, b, list))
			{
				update_a_p(a);
				//print_stacks(a, b, "Split a");
			}
		split_b(a, b, list);
		//print_stacks(a, b, "Split b");
	}
	delete_stack(b);
}