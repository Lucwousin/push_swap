#include "push_swap_shared.h"

void	do_rotate(t_stack *a, t_stack *b)
{
	if (b->top >= 1 && get_i(b, 0) > get_top(b))
	{
		rotate(a);
		rotate(b);
	}
	else rotate(a);
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

void	do_quicksort(t_stack *a, t_stack *b, uint16_t median, uint32_t size)
{
	int32_t	pushed = 0;
	uint32_t	i = 0;
	if (size <= 1)
		return;
	while (i < size)
	{
		if (get_top(a) <= median) {
			push(a, b);
			++pushed;
		} else
			do_rotate(a, b);
		i++;
	}
	//int32_t sorted = get_sorted_idx(b);
	while (b->top != -1)
		push(b, a);
	//	++pushed_back;
	//}
	//if (a->top == 0) {
	//	while (b->top >= 0)
	//		push(b, a);
	//	return;
	//}
	if (median == 1)
		do_quicksort(a, b, 0, pushed);
	else if (median != 0)
		do_quicksort(a, b, (median + 1) / 2, pushed);
	while (a->arr[a->top] <= median)
		rotate(a);
	if (median > 1)
		do_quicksort(a, b, median * 3 / 2, size - pushed);
}

void	ps_quicksort(t_stack *a)
{
	t_stack *b = create_stack(a->size);
	if (!b) // TODO: change
		return ;
	do_quicksort(a, b, (a->size + 1) / 2, a->size);
	delete_stack(b);
}