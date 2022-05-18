#include "push_swap.h"
#include "ft_printf.h"

static const char	*g_actions[11] = {
	"SA", "SB", "SS",
	"PA", "PB", "RA", "RB",
	"RR", "RRA", "RRB", "RRR"};

void	run_action(t_action action, t_stack *a, t_stack *b)
{
	if (action == SA || action == SS)
		swap(a);
	if (action == SB || action == SS)
		swap(b);
	if (action == PA)
		push(a, b);
	if (action == PB)
		push(b, a);
	if (action == RA || action == RR)
		rotate(a);
	if (action == RB || action == RR)
		rotate(b);
	if (action == RRA || action == RRR)
		rotate_rev(a);
	if (action == RRB || action == RRR)
		rotate_rev(b);
	ft_printf("%s\n", g_actions[action]);
}