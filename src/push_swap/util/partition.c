/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   partition.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 18:04:31 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/30 18:04:31 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Get the top partition of the stack.
 * If there is no top partition, return -1.
 */
int32_t	get_partition(t_stack *stack)
{
	if (stack->p_idx == -1)
		return (-1);
	return (stack->partitions[stack->p_idx]);
}

/**
 * Create a partition for the stack.
 */
void	partition(t_stack *stack)
{
	stack->partitions[++stack->p_idx] = stack->top;
}

/**
 * Get the size of the top partition of stack.
 * If the stack has no partitions yet, return the size of the stack.
 */
int32_t	partition_size(t_stack *stack)
{
	int32_t	partition;

	partition = get_partition(stack);
	if (partition == -1)
		return (stack->top + 1);
	else
		return (stack->top + 1 - (partition + 1));
}

/**
 * Calculate the maximum amount of partitions needed for quicksort
 *
 * This is a worst case estimate, without keeping selection sort in mind
 */
int32_t	calculate_needed_partitions(uint32_t values)
{
	int32_t	needed;

	needed = 0;
	while (values != 1)
	{
		++needed;
		values /= 2;
	}
	return (needed);
}
