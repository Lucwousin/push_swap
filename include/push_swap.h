/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 13:17:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/31 13:17:19 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "push_swap_shared.h"
# define SEL_SORT_CUTOFF 25
# define TRI_SPLIT_CUTOFF 20

typedef enum e_action_type {
	SWAP,
	ROTATE,
	PUSH
}	t_a_type;

typedef struct s_a_info {
	const char	*str;
	t_a_type	type;
}	t_a_info;

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
	t_action	action;
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

/*
 * Quicksort
 */
void		ps_quicksort(t_stack *a, t_ins_lst *list);
int32_t		calculate_needed_partitions(uint32_t values);
int32_t		find_median(t_stack *stack, int32_t count);

bool		selection_sort(t_stack *s[2], t_ins_lst *list, int32_t count);

/*
 * Action list stuff
 */
void		run_action(
				t_action action, t_stack *a, t_stack *b, t_ins_lst *list);
bool		add_action(t_ins_lst *list, t_action action);
void		clear(t_ins_lst *list);
t_a_info	get_info(t_action action);

/*
 * Action list optimization
 */
void		optimize(t_ins_lst *list);
t_ins_lst	*clean_rotation(t_ins_lst *list, t_ins_lst *cur);
t_ins_lst	*combine_contradictions(t_ins_lst *list, t_ins_lst *cur);

/*
 * Ways to run actions on a certain stack, from stack name
 * 
 * (do_swap checks if it's more efficient to swap both stacks)
 */
void		do_push(t_s_id from, t_stack *s[2], t_ins_lst *list);
void		do_rotate(t_s_id n, t_stack *s[2], bool rev, t_ins_lst *list);
void		do_rotate_n(t_s_id n, t_stack *s[2], int32_t amt, t_ins_lst *list);
void		do_swap(t_s_id n, t_stack *s[2], t_ins_lst *list);

/*
 * Utils
 */
int32_t		get_partition(t_stack *stack);
void		partition(t_stack *stack);
int32_t		partition_size(t_stack *stack);
bool		compare(int32_t a, int32_t b, t_cmp cmp);

#endif