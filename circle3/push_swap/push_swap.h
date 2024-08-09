/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:06:02 by marsenij          #+#    #+#             */
/*   Updated: 2024/04/22 11:27:08 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_stack
{
	int				num;
	int				index;
	int				max_index;
	int				push_cost;
	int				above_median;
	int				cheapest;
	struct s_stack	*target_node;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

void	free_list(t_stack *head);
void	update_node_info(t_stack *a, t_stack *b);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	add_median(t_stack *a);
void	find_target_node(t_stack *a, t_stack *b);
void	update_index(t_stack *a);
void	calc_cheapest(t_stack *a);
int		shared_cost(t_stack *a);
void	update_node_info(t_stack *a, t_stack *b);
void	b_max_on_top(t_stack **a, t_stack **b);
void	push_to_a(t_stack **a, t_stack **b);
void	sort_3(t_stack **a);
void	push_to_b(t_stack **a, t_stack **b);
void	push_to_b_logic(t_stack **a, t_stack *curr_a, t_stack **b);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
t_stack	*last_node(t_stack *a);
t_stack	*max_num(t_stack *a);
t_stack	*min_num(t_stack *a);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *src);
int		ft_strcmp(char *s1, char *s2);
int		wordcnt(char **array);
int		checkdup(t_stack *a, t_stack *a_start);
int		is_sorted(t_stack *a);

void	trouble(t_stack *a, t_stack *b);//needs to be removed

#endif