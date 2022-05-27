#include <stdlib.h>
#include <unistd.h>
#include "push_swap.h"
#include "libft.h"
#include "ft_printf.h"

static const char	*g_actions[11] = {
	"sa", "sb", "ss",
	"pa", "pb", "ra", "rb",
	"rr", "rra", "rrb", "rrr"};

bool	add_action(t_action_list *list, t_action action)
{
	t_action_list	*lst_obj;
	
	lst_obj = malloc(sizeof(t_action_list));
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

void	clear(t_action_list *list)
{
	t_action_list	*cur;

	cur = list->next;
	while (cur && cur != list)
	{
		cur = cur->next;
		free(cur->prev);
	}
}

void	run_action(t_action action, t_stack *a, t_stack *b, t_action_list *list)
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

bool	remove_list_item(t_action_list *obj)
{
	obj->prev->next = obj->next;
	obj->next->prev = obj->prev;
	free(obj);
	return (true);
}

bool	modify_and_unlink(t_action_list *cur, t_action_list *nxt, t_action action)
{
	cur->action = action;
	return (remove_list_item(nxt));
}

void	combine_list(t_action_list *list)
{
	bool			changed;
	t_action_list	*cur;
	t_action_list	*nxt;

	changed = true;
	while (changed)
	{
		changed = false;
		cur = list->next;
		while (cur != list->prev)
		{
			nxt = cur->next;
			if ((cur->action == RA && nxt->action == RB)
				|| (cur->action == RB && nxt->action == RA))
				changed |= modify_and_unlink(cur, nxt, RR);
			else if ((cur->action == RRA && nxt->action == RRB)
				|| (cur->action == RRB && nxt->action == RRA))
				changed |= modify_and_unlink(cur, nxt, RRR);
			else if ((cur->action == SA && nxt->action == SB)
				|| (cur->action == SB && nxt->action == SA))
				changed |= modify_and_unlink(cur, nxt, SS);
			else if ((cur->action == RA && nxt->action == RRA)
				|| (cur->action == RRA && nxt->action == RA)
				|| (cur->action == RB && nxt->action == RRB)
				|| (cur->action == RRB && nxt->action == RB)
				|| (cur->action == RR && nxt->action == RRR)
				|| (cur->action == RRR && nxt->action == RR)
				|| (cur->action == PA && nxt->action == PB)
				|| (cur->action == PB && nxt->action == PA))
			{
				cur = nxt->next;
				changed |= remove_list_item(nxt->prev);
				changed |= remove_list_item(nxt);
				continue ;
			}
			cur = cur->next;
		}
	}
}

bool	is_push(t_action action)
{
	return (action == PA || action == PB);
}

bool	is_swap(t_action action)
{
	return (action == SA || action == SB || action == SS);
}

t_action_list	*handle_rotation(t_action_list *list, t_action_list *cur)
{
	int32_t	rot_delta[2];

	rot_delta[A] = 0;
	rot_delta[B] = 0;
	while (cur != list && !is_push(cur->action) && !is_swap(cur->action))
	{
		if (cur->action == RA || cur->action == RR)
			++rot_delta[A];
		if (cur->action == RB || cur->action == RR)
			++rot_delta[B];
		if (cur->action == RRA || cur->action == RRR)
			--rot_delta[A];
		if (cur->action == RRB || cur->action == RRR)
			--rot_delta[B];
		cur = cur->next;
	}
	while (rot_delta[A] || rot_delta[B])
	{
		if (rot_delta[A] > 0 && rot_delta[B] > 0)
		{
			ft_printf("%s\n", g_actions[RR]);
			--rot_delta[A];
			--rot_delta[B];
			continue ;
		}
		if (rot_delta[A] < 0 && rot_delta[B] < 0)
		{
			ft_printf("%s\n", g_actions[RRR]);
			++rot_delta[A];
			++rot_delta[B];
			continue ;
		}
		if (rot_delta[A] > 0)
		{
			ft_printf("%s\n", g_actions[RA]);
			--rot_delta[A];
		}
		if (rot_delta[B] > 0)
		{
			ft_printf("%s\n", g_actions[RB]);
			--rot_delta[B];
		}
		if (rot_delta[A] < 0)
		{
			ft_printf("%s\n", g_actions[RRA]);
			++rot_delta[A];
		}
		if (rot_delta[B] < 0)
		{
			ft_printf("%s\n", g_actions[RRB]);
			++rot_delta[B];
		}
	}
	return (cur);
}

t_action_list	*handle_push_swap(t_action_list *list, t_action_list *cur)
{
	t_action_list	*next;
	
	next = cur->next;
	if (next != list && ((cur->action == SA && next->action == SB) || (next->action == SA && cur->action == SB)))
		ft_printf("%s\n", g_actions[SS]);
	else if (next == list || (!(cur->action == PA && next->action == PB) && !(next->action == PA && cur->action == PB)
		&& !(cur->action == SS && next->action == SS) && !(cur->action == SA && next->action == SA) 
		&& !(cur->action == SB && next->action == SB)))
	{
		ft_printf("%s\n", g_actions[cur->action]);
		return (next);
	}
	return (next->next);
}

void	print_list(t_action_list *list)
{
	t_action_list	*cur;

	if (list->next == NULL)
		return ;
	cur = list->next;
	while (cur != list)
	{
		if (cur->action == RA || cur->action == RB || cur->action == RR
			|| cur->action == RRA || cur->action == RRB || cur->action == RRR)
			cur = handle_rotation(list, cur);
		else
			cur = handle_push_swap(list, cur);
	}
	clear(list);
}