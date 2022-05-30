/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotation.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/29 17:51:14 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/29 17:51:14 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static const t_action	g_rotates[2][2] = {
[false] = {[A] = RA, [B] = RB},
[true] = {[A] = RRA, [B] = RRB}
};

static t_ins_lst	*get_rotation_deltas(
	int32_t rot_delta[2],
	t_ins_lst *list,
	t_ins_lst *cur)
{
	rot_delta[A] = 0;
	rot_delta[B] = 0;
	while (cur != list && get_info(cur->action).type == ROTATE)
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
	return (cur);
}

static void	create_new_rotation(int32_t rot_delta[2], t_ins_lst *new_list)
{
	while (rot_delta[A] || rot_delta[B])
	{
		if (rot_delta[A] > 0 && rot_delta[B] > 0)
			add_action(new_list, RR);
		else if (rot_delta[A] < 0 && rot_delta[B] < 0)
			add_action(new_list, RRR);
		else
		{
			if (rot_delta[A])
				add_action(new_list, g_rotates[rot_delta[A] < 0][A]);
			if (rot_delta[B])
				add_action(new_list, g_rotates[rot_delta[B] < 0][B]);
		}
		if (rot_delta[A] < 0)
			rot_delta[A]++;
		else if (rot_delta[A] > 0)
			rot_delta[A]--;
		if (rot_delta[B] < 0)
			rot_delta[B]++;
		else if (rot_delta[B] > 0)
			rot_delta[B]--;
	}
}

void	replace_list(t_ins_lst *after, t_ins_lst *before, t_ins_lst *with)
{
	t_ins_lst	tmp_list;

	tmp_list.next = after->next;
	tmp_list.prev = before->prev;
	tmp_list.next->prev = &tmp_list;
	tmp_list.prev->next = &tmp_list;
	clear(&tmp_list);
	after->next = with->next;
	after->next->prev = after;
	before->prev = with->prev;
	before->prev->next = before;
}

t_ins_lst	*clean_rotation(t_ins_lst *list, t_ins_lst *cur)
{
	t_ins_lst	new_list;
	t_ins_lst	*next;
	int32_t		rot_delta[2];

	new_list.next = 0;
	new_list.prev = 0;
	next = get_rotation_deltas(rot_delta, list, cur);
	create_new_rotation(rot_delta, &new_list);
	replace_list(cur->prev, next, &new_list);
	return (next);
}
