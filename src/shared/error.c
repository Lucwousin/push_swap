/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 14:17:47 by lsinke        #+#    #+#                 */
/*   Updated: 2022/05/31 14:17:47 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

void	error(void)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
