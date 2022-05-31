/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 13:41:35 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/31 13:41:35 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	delete_stacks(t_stack *stacks[2])
{
	delete_stack(stacks[A]);
	delete_stack(stacks[B]);
}

static void	print_result(t_result result)
{
	if (result == OK)
		ft_putendl_fd("OK", STDOUT_FILENO);
	else if (result == KO)
		ft_putendl_fd("KO", STDOUT_FILENO);
	else if (result == ERROR)
		ft_putendl_fd("Error", STDERR_FILENO);
}

int	main(int argc, char **argv)
{
	t_stack		*stacks[2];
	t_result	result;

	if (argc == 1)
		exit(EXIT_SUCCESS);
	stacks[A] = create_stack(argc - 1, 0);
	stacks[B] = create_stack(argc - 1, 0);
	if (stacks[A] == NULL || stacks[B] == NULL)
	{
		delete_stacks(stacks);
		exit(EXIT_FAILURE);
	}
	if (!parse_args(stacks[A], argv + 1))
	{
		delete_stacks(stacks);
		error();
	}
	result = ingest_commands(stacks);
	print_result(result);
	delete_stacks(stacks);
}
