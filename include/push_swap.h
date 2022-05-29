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
	B,
	END_SN
}	t_stack_name;

typedef enum e_cmp {
	LE,
	GT
}	t_cmp;

typedef struct s_action_cost {
	int32_t	count;
	bool	smaller;
}	t_cost;

typedef struct s_action_list	t_ins_lst;

struct s_action_list
{
	t_action		action;
	t_ins_lst	*next;
	t_ins_lst	*prev;
};

/**
 * Local variables for the quicksort split function.
 * Thanks norminette.
 */
typedef struct s_split_info {
	int32_t	count;
	int32_t	median;
	int32_t	rotated;
}	t_splinf;

void	error(void);

void	run_action(t_action action, t_stack *a, t_stack *b, t_ins_lst *list);

void	ps_quicksort(t_stack *a, t_ins_lst *action_list);

int32_t	find_median(t_stack *stack, int32_t count);
int32_t	find_closest(t_stack *stack, int32_t count, int32_t median, t_cmp cmp);
int32_t	partition_size(t_stack *stack);

void	do_push(t_stack_name from, t_stack *a, t_stack *b, t_ins_lst *list);
void	do_rotate(t_stack_name name, t_stack *stack, bool rev, t_ins_lst *list);
void	do_rotate_n(t_stack_name name, t_stack *stack, int32_t amt, t_ins_lst *list);

void	print_list(t_ins_lst *list);
void	combine_list(t_ins_lst *list);

bool	compare(int32_t a, int32_t b, t_cmp cmp);

#endif