#include "push_swap.h"

void	do_rotate(t_stack *a, t_stack *b)
{
	if (b->top >= 1 && get_i(b, 0) > get_top(b))
	{
		run_action(RR, a, b);
	}
	else run_action(RA, a, b);
}

int32_t	get_sorted_idx(t_stack *b)
{
	int32_t	idx;

	idx = 0;
	while (idx <= b->top)
	{
		if (get_i(b, idx) != idx)
			break ;
		++idx;
	}
	return (idx - 1);
}

void	do_quicksort(t_stack *a, t_stack *b, int32_t median, uint32_t size, bool less_than)
{
	uint32_t	i;
	
	if (size == 1)
		return;
	i = 0;
	while (i++ < size)
	{
		if (less_than) {
			if (get_top(a) < median)
				run_action(PB, a, b);
			else
				do_rotate(a, b);
		}
		else if (get_top(b) >= median)
			run_action(PA, a, b);
		else
			run_action(RB, a, b);
	}
	do_quicksort(a, b, median / 2, size / 2, false);
	do_quicksort(a, b, median / 2, size / 2, true);
}

void	ps_quicksort(t_stack *a)
{
	t_stack *b = create_stack(a->size);
	if (!b) // TODO: change
		return ;
	do_quicksort(a, b, (int32_t) a->size / 2, a->size, true);
	delete_stack(b);
}