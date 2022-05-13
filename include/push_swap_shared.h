#ifndef PUSH_SWAP_SHARED_H
# define PUSH_SWAP_SHARED_H
# include <stdint.h>
# include <stdbool.h>

typedef struct s_stack
{
	int32_t		*arr;
	int32_t		top;
	uint32_t	size;
}	t_stack;

t_stack	*create_stack(uint32_t size);
void	delete_stack(t_stack *stack);
bool	index_stack(t_stack *stack);
bool	is_sorted(t_stack *stack);

bool	parse_args(t_stack *stack, char **argv);

void	swap(t_stack *stack);
void	push(t_stack *from, t_stack *to);
void	rotate(t_stack *stack);
void	rotate_rev(t_stack *stack);

#endif