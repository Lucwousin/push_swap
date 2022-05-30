#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "push_swap_shared.h"
# define SEL_SORT_CUTOFF 25

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

typedef enum e_action_type {
	SWAP,
	ROTATE,
	PUSH
}	t_a_type;

typedef struct s_a_info {
	const char	*str;
	t_a_type	type;
}	t_a_info;

typedef enum e_stack_name {
	A,
	B
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
int32_t	calculate_needed_partitions(uint32_t values);
int32_t	find_median(t_stack *stack, int32_t count);

bool	selection_sort(t_stack *s[2], t_ins_lst *list, int32_t count);

int32_t	get_partition(t_stack *stack);
void	partition(t_stack *stack);
int32_t	partition_size(t_stack *stack);

void	do_push(t_stack_name from, t_stack *a, t_stack *b, t_ins_lst *list);
void	do_rotate(t_stack_name name, t_stack *stack, bool rev, t_ins_lst *list);
void	do_rotate_n(t_stack_name n, t_stack *stack, int32_t amt, t_ins_lst *list);

bool	add_action(t_ins_lst *list, t_action action);
void	print_list(t_ins_lst *list);
void	clear(t_ins_lst *list);
t_a_info	get_info(t_action action);

void	optimize(t_ins_lst *list);
t_ins_lst	*clean_rotation(t_ins_lst *list, t_ins_lst *cur);
t_ins_lst	*combine_contradictions(t_ins_lst *list, t_ins_lst *cur);

bool	compare(int32_t a, int32_t b, t_cmp cmp);

#endif