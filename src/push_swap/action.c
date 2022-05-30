/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   action.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 16:13:30 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/30 16:13:30 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "push_swap.h"
#include "libft.h"
#include "ft_printf.h"

static const t_a_info	g_actions[] = {
[SA] = {"sa", SWAP},
[SB] = {"sb", SWAP},
[SS] = {"ss", SWAP},
[PA] = {"pa", PUSH},
[PB] = {"pb", PUSH},
[RA] = {"ra", ROTATE},
[RB] = {"rb", ROTATE},
[RR] = {"rr", ROTATE},
[RRA] = {"rra", ROTATE},
[RRB] = {"rrb", ROTATE},
[RRR] = {"rrr", ROTATE},
};

t_a_info	get_info(t_action action)
{
	return (g_actions[action]);
}

bool	add_action(t_ins_lst *list, t_action action)
{
	t_ins_lst	*lst_obj;

	lst_obj = malloc(sizeof(t_ins_lst));
	if (!lst_obj)
		return (false);
	lst_obj->action = action;
	if (list->prev)
	{
		lst_obj->prev = list->prev;
		lst_obj->prev->next = lst_obj;
		list->prev = lst_obj;
	}
	else
	{
		lst_obj->prev = list;
		list->prev = lst_obj;
		list->next = lst_obj;
	}
	lst_obj->next = list;
	return (true);
}

void	clear(t_ins_lst *list)
{
	t_ins_lst	*cur;

	cur = list->next;
	while (cur && cur != list)
	{
		cur = cur->next;
		free(cur->prev);
	}
}

void	run_action(t_action action, t_stack *a, t_stack *b, t_ins_lst *list)
{
	if (action == SA || action == SS)
		swap(a);
	if (action == SB || action == SS)
		swap(b);
	if (action == PA)
		push(b, a);
	if (action == PB)
		push(a, b);
	if (action == RA || action == RR)
		rotate(a);
	if (action == RB || action == RR)
		rotate(b);
	if (action == RRA || action == RRR)
		rotate_rev(a);
	if (action == RRB || action == RRR)
		rotate_rev(b);
	if (!add_action(list, action))
	{
		delete_stack(a);
		delete_stack(b);
		clear(list);
		error();
	}
}
