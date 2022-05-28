#include "push_swap.h"
#include "libft.h"

int32_t	find_median(t_stack *stack, int32_t count)
{
	int32_t	min_max[2];
	int32_t	value;

	min_max[0] = INT32_MAX;
	min_max[1] = INT32_MIN;
	while (count--)
	{
		value = stack->arr[stack->top - count];
		min_max[0] = ft_min(value, min_max[0]);
		min_max[1] = ft_max(value, min_max[1]);
	}
	return ((min_max[0] + min_max[1]) / 2);
}

/**
 * Find the closest value in the current partition that compares with median.
 *
 * For example, if there's a partition: 1 3 5 2 4
 * We want to push everything greater than 3 away
 * If we rotate normally we will need 4 instructions to get 4 on top
 * If we rotate reversed we will only need 3 instructions to get 5 on top
 * This function will return a negative number if reverse rotation is better
 */
int32_t	find_closest(t_stack *stack, int32_t count, int32_t median, t_cmp cmp)
{
	int32_t	partit_bot;
	int32_t	distances[2];
	int32_t	values[2];
	int32_t	i;

	distances[0] = -1;
	distances[1] = -1;
	partit_bot = 0;
	if (stack->p_idx != -1)
		partit_bot += stack->partitions[stack->p_idx] + 1;
	i = 0;
	while (i < count && (distances[0] < 0 || distances[1] < 0))
	{
		values[0] = stack->arr[stack->top - i];
		values[1] = stack->arr[partit_bot + i];
		if (distances[0] < 0 && compare(values[0], median, cmp))
			distances[0] = i;
		if (distances[1] < 0 && compare(values[1], median, cmp))
			distances[1] = i + partit_bot + 1;
		++i;
	}
	return (distances[1] - distances[0]);
}