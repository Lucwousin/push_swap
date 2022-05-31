/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 17:11:30 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/29 17:11:30 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "push_swap.h"

static void	sort_three(t_stack *a, t_ins_lst *list)
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

static void	sort(t_stack *a, t_ins_lst *list)
{
	if (is_sorted(a))
		return ;
	if (a->size == 2)
		return (run_action(SA, a, NULL, list));
	if (a->size == 3)
		return (sort_three(a, list));
	return (ps_quicksort(a, list));
}

void	print_list(t_ins_lst *list)
{
	t_ins_lst	*cur;

	cur = list->next;
	while (cur != list)
	{
		ft_putendl_fd((char *) get_info(cur->action).str, STDOUT_FILENO);
		cur = cur->next;
	}
}

int	main(int argc, char **argv)
{
	t_stack		*stack;
	t_ins_lst	action_list;

	if (argc == 1)
		exit(EXIT_SUCCESS);
	ft_bzero(&action_list, sizeof(t_ins_lst));
	stack = create_stack(argc - 1, 1);
	if (stack == NULL)
		exit(EXIT_FAILURE);
	if (!parse_args(stack, argv + 1) || !index_stack(stack))
	{
		delete_stack(stack);
		error();
	}
	sort(stack, &action_list);
	optimize(&action_list);
	print_list(&action_list);
	clear(&action_list);
	delete_stack(stack);
}
