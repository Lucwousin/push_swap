/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   optimizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 16:15:06 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/30 16:15:06 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int32_t	get_length(t_ins_lst *list)
{
	t_ins_lst	*cur;
	int32_t		length;

	length = 0;
	cur = list->next;
	while (cur && cur != list)
	{
		++length;
		cur = cur->next;
	}
	return (length);
}

static void	do_optimization(t_ins_lst *list)
{
	t_ins_lst	*cur;

	cur = list->next;
	while (cur && cur != list)
	{
		if (get_info(cur->action).type == ROTATE)
			cur = clean_rotation(list, cur);
		else
			cur = combine_contradictions(list, cur);
	}
}

void	optimize(t_ins_lst *list)
{
	int32_t		list_len;
	int32_t		new_length;

	list_len = 0;
	new_length = get_length(list);
	while (new_length != list_len)
	{
		list_len = new_length;
		do_optimization(list);
		new_length = get_length(list);
	}
}
