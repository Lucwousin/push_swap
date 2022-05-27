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

typedef enum e_stack_name {
	A,
	B
}	t_stack_name;

typedef struct s_action_cost {
	int32_t	count;
	bool	smaller;
}	t_cost;

typedef struct s_action_list	t_action_list;

struct s_action_list
{
	t_action		action;
	t_action_list	*next;
	t_action_list	*prev;
};

void	error(void);

void	run_action(t_action action, t_stack *a, t_stack *b, t_action_list *list);

void	ps_quicksort(t_stack *a, t_action_list *action_list);

void	print_list(t_action_list *list);
void	combine_list(t_action_list *list);

#endif