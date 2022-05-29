/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   median.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 17:17:41 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/29 17:17:41 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

/**
 * Find the median of the topmost count values on the stack.
 * Because the stack is indexed, this is the average of the min and max values.
 */
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
