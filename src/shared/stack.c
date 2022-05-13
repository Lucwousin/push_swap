#include "push_swap_shared.h"
#include "libft.h"

t_stack	*create_stack(uint32_t size)
{
	t_stack	*stack;
	
	stack = ft_calloc(1, sizeof(t_stack));
	if (stack == NULL)
		return (NULL);
	stack->size = size;
	stack->top = (int32_t) size - 1;
	stack->arr = malloc(size * sizeof(int32_t));
	if (stack->arr != NULL)
		return (stack);
	free(stack);
	return (NULL);
}

void	delete_stack(t_stack *stack)
{
	free(stack->arr);
	free(stack);
}

bool	index_stack(t_stack *stack)
{
	int32_t		*arr_copy;
	uint32_t	i;

	arr_copy = malloc(stack->size * sizeof(int32_t));
	if (!arr_copy)
		return (false);
	ft_memcpy(arr_copy, stack->arr, stack->size * sizeof(int32_t));
	quicksort(arr_copy, 0, stack->size - 1);
	i = 0;
	while (i < stack->size)
	{
		stack->arr[i] = (int32_t) binary_search(
				arr_copy, stack->arr[i], stack->size);
		++i;
	}
	free(arr_copy);
	return (true);
}

bool	is_sorted(t_stack *stack)
{
	uint32_t	i;
	
	i = stack->top;
	while (i > 0)
	{
		if (stack->arr[i] > stack->arr[i - 1])
			return (false);
		--i;
	}
	return (true);
}