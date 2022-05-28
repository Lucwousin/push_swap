#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "push_swap.h"

void	error(void)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	sort_small(t_stack *a, t_ins_lst *list)
{
	if (a->size == 2)
		return (run_action(SA, a, NULL, list));
}

void	sort_three(t_stack *a, t_ins_lst *list)
{
	if (a->arr[a->top] == 0)
	{
		run_action(RRA, a, NULL, list);
		run_action(SA, a, NULL, list);
	}
	else if (a->arr[a->top] == 1 && a->arr[1] == 0)
		run_action(SA, a, NULL, list);
	else if (a->arr[a->top] == 1)
		run_action(RRA, a, NULL, list);
	else if (a->arr[a->top] == 2 && a->arr[1] == 0)
		run_action(RA, a, NULL, list);
	else if (a->arr[a->top] == 2)
	{
		run_action(SA, a, NULL, list);
		run_action(RRA, a, NULL, list);
	}
}

void	sort(t_stack *a, t_ins_lst *list)
{
	if (is_sorted(a))
		return ;
	if (a->size == 2)
		return (run_action(SA, a, NULL, list));
	if (a->size == 3)
		return (sort_three(a, list));
	return (ps_quicksort(a, list));
}

int	main(int argc, char **argv)
{
	t_stack			*stack;
	t_ins_lst	action_list;

	if (argc <= 2)
		exit(EXIT_SUCCESS);
	ft_bzero(&action_list, sizeof(t_ins_lst));
	stack = create_stack(argc - 1);
	if (stack == NULL)
		exit(EXIT_FAILURE);
	if (!parse_args(stack, argv + 1) || !index_stack(stack))
	{
		delete_stack(stack);
		error();
	}
	sort(stack, &action_list);
	combine_list(&action_list);
	print_list(&action_list);
	delete_stack(stack);
}