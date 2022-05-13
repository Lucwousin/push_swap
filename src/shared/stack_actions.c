#include "push_swap_shared.h"

void	swap(t_stack *stack)
{
	int32_t	tmp;

	if (stack->size <= 1)
		return ;
	tmp = stack->arr[stack->top];
	stack->arr[stack->top] = stack->arr[stack->top - 1];
	stack->arr[stack->top - 1] = tmp;
}

void	push(t_stack *from, t_stack *to)
{
	if (from->top < 0)
		return ;
	to->arr[++to->top] = from->arr[from->top--];
}

void	rotate(t_stack *stack)
{
	int32_t	val;
	int32_t	tmp;
	int32_t	i;
	
	if (stack->top <= 0)
		return ;
	i = 0;
	val = stack->arr[stack->top];
	while (i <= stack->top)
	{
		tmp = stack->arr[i];
		stack->arr[i] = val;
		val = tmp;
		++i;
	}
}

void	rotate_rev(t_stack *stack)
{
	int32_t	val;
	int32_t	tmp;
	int32_t	i;

	if (stack->top <= 0)
		return ;
	i = stack->top;
	val = stack->arr[0];
	while (i >= 0)
	{
		tmp = stack->arr[i];
		stack->arr[i] = val;
		val = tmp;
		--i;
	}
}