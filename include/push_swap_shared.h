/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap_shared.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 13:17:11 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/31 13:17:11 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_SHARED_H
# define PUSH_SWAP_SHARED_H
# include <stdint.h>
# include <stdbool.h>

typedef struct s_stack
{
	int32_t		*arr;
	int32_t		top;
	uint32_t	size;
	int32_t		*partitions;
	int32_t		p_idx;
}	t_stack;

typedef enum e_action {
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	NO_ACTION
}	t_action;

typedef enum e_stack_name {
	A,
	B
}	t_s_id;

/*
 * The most important function of all
 */
void	error(void);

/*
 * Parsing
 */
bool	parse_args(t_stack *stack, char **argv);

/*
 * Stack creation
 */
t_stack	*create_stack(uint32_t size, int32_t p_count);
void	delete_stack(t_stack *stack);
bool	index_stack(t_stack *stack);

/*
 * Stack actions
 */
void	swap(t_stack *stack);
void	push(t_stack *from, t_stack *to);
void	rotate(t_stack *stack);
void	rotate_rev(t_stack *stack);

/*
 * Stack utils
 */
bool	is_sorted(t_stack *stack);
int32_t	get_top(t_stack *stack);

#endif