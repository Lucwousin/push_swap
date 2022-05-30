/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   contradictions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 16:15:30 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/30 16:15:30 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

static const t_action	g_contradictions[] = {
[SA] = SA,
[SB] = SB,
[SS] = SS,
[PA] = PB,
[PB] = PA,
[RA] = NO_ACTION,
[RB] = NO_ACTION,
[RR] = NO_ACTION,
[RRA] = NO_ACTION,
[RRB] = NO_ACTION,
[RRR] = NO_ACTION
};

static t_ins_lst	*remove_items(t_ins_lst *cur, t_ins_lst *next)
{
	cur->prev->next = next->next;
	next->next->prev = cur->prev;
	cur = next;
	next = next->next;
	free(cur->prev);
	free(cur);
	return (next);
}

t_ins_lst	*combine_contradictions(t_ins_lst *list, t_ins_lst *cur)
{
	t_ins_lst	*next;

	next = cur->next;
	if (next == list)
		return (list);
	if (g_contradictions[cur->action] == next->action)
		return (remove_items(cur, next));
	return (next);
}
