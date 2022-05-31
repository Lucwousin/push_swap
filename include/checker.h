/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 13:41:37 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/31 13:41:37 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "push_swap_shared.h"

typedef enum e_result {
	OK,
	KO,
	ERROR
}	t_result;

t_result	ingest_commands(t_stack *stacks[2]);

#endif