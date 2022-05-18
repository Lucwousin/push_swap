#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "push_swap_shared.h"

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
	RRR
}	t_action;

void	run_action(t_action action, t_stack *a, t_stack *b);

void	ps_quicksort(t_stack *a);

#endif