#include "push_swap_shared.h"
#include "libft.h"

static bool	read_number(char *arg, int32_t *n)
{
	int8_t	sign;
	int64_t	number;

	sign = 1;
	if (*arg == '-')
	{
		sign = -1;
		++arg;
	}
	number = 0;
	while (ft_isdigit(*arg))
	{
		number *= 10;
		number += *arg - '0';
		++arg;
		if ((number > (int64_t) INT32_MAX + 1) ||
			(number > INT32_MAX && sign == 1))
			return (false);
	}
	if (*arg != '\0')
		return (false);
	number *= sign;
	*n = (int32_t) number;
	return (true);
}

static bool	contains_no_duplicates(const int32_t *arr, uint32_t size)
{
	uint32_t	i;
	uint32_t	j;
	
	i = 0;
	while (i < size - 1)
	{
		j = i;
		while (++j < size)
			if (arr[i] == arr[j])
				return (false);
		++i;
	}
	return (true);
}

bool	parse_args(t_stack *stack, char **argv)
{
	uint32_t	i;

	stack->top = (int32_t) stack->size - 1;
	i = stack->size;
	while (i-- > 0)
		if (!read_number(*(argv++), stack->arr + i))
			return (false);
	return (contains_no_duplicates(stack->arr, stack->size));
}