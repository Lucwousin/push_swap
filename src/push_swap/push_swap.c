#include <unistd.h>
#include "push_swap.h"
#include "push_swap_shared.h"

static void	error(void)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	sort_small(t_stack *a)
{
	if (a->size == 2)
		return (ft_putendl_fd("sa", STDOUT_FILENO));
}

void	sort(t_stack *a)
{
	if (is_sorted(a))
		return ;
	if (a->size <= 5)
		return (sort_small(a));
}

int	main(int argc, char **argv)
{
	t_stack	*stack;

	if (argc <= 2)
		exit(EXIT_SUCCESS);
	stack = create_stack(argc - 1);
	if (stack == NULL)
		exit(EXIT_FAILURE);
	if (!parse_args(stack, argv + 1) || !index_stack(stack))
	{
		delete_stack(stack);
		error();
	}
	sort(stack);
	delete_stack(stack);
}