/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ingest.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 14:29:48 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/31 14:29:48 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "checker.h"
#include "get_next_line.h"

const static char	*g_action_strs[] = {
[SA] = "sa\n",
[SB] = "sb\n",
[SS] = "ss\n",
[PA] = "pa\n",
[PB] = "pb\n",
[RA] = "ra\n",
[RB] = "rb\n",
[RR] = "rr\n",
[RRA] = "rra\n",
[RRB] = "rrb\n",
[RRR] = "rrr\n"
};

static t_result	check_sorted(t_stack *stacks[2])
{
	if (is_sorted(stacks[A]) && stacks[B]->top == -1)
		return (OK);
	return (KO);
}

static t_action	get_action(const char *line)
{
	t_action	action;
	const char	*act_str;

	action = SA;
	while (action != NO_ACTION)
	{
		act_str = g_action_strs[action];
		if (ft_strncmp(line, act_str, ft_strlen(act_str)) == 0)
			break ;
		++action;
	}
	return (action);
}

static void	do_action(t_stack *stacks[2], t_action action)
{
	if (action == SA || action == SS)
		swap(stacks[A]);
	if (action == SB || action == SS)
		swap(stacks[B]);
	if (action == PA)
		push(stacks[B], stacks[A]);
	if (action == PB)
		push(stacks[A], stacks[B]);
	if (action == RA || action == RR)
		rotate(stacks[A]);
	if (action == RB || action == RR)
		rotate(stacks[B]);
	if (action == RRA || action == RRR)
		rotate_rev(stacks[A]);
	if (action == RRB || action == RRR)
		rotate_rev(stacks[B]);
}

t_result	ingest_commands(t_stack *stacks[2])
{
	char		*line;
	t_action	action;

	while (true)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (check_sorted(stacks));
		action = get_action(line);
		free(line);
		if (action == NO_ACTION)
			return (ERROR);
		do_action(stacks, action);
	}
}
