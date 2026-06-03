#include <stdio.h>
#include <stdlib.h>

typedef struct s_stack
{
	int				num;
	int				index;
	struct s_stack	*next;
}					t_stack;
/*
void	simple_sort(t_stack **a, t_stack **b);
void	rotate(t_stack **stack);
void	ft_lstadd_front(t_stack **lst, t_stack *new);
void	ft_lstadd_back(t_stack **lst, t_stack *new);
t_stack	*ft_lstlast(t_stack *lst);
void	print_stack(t_stack **a);
*/
void	push(t_stack **st1, t_stack **st2)
{
	t_stack *tmp;

	if (!*st1)
		return ;
	tmp = *st1;
	*st1 = (*st1)->next;
	tmp->next = NULL;
	ft_lstadd_front(st2, tmp);
}

void	op_pa(t_stack **a, t_stack **b)
{
	push(b, a);
}

void	op_pb(t_stack **a, t_stack **b)
{
	push(a, b);
}

void	rotate(t_stack **stack)
{
	t_stack *tmp;

	if (!*stack || !(*stack)->next)
        return ;
	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = NULL;
	ft_lstadd_back(stack, tmp);
}

void	op_ra(t_stack **a)
{
	rotate(a);
}
/*
void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

void	ft_lstadd_front(t_stack **lst, t_stack *new)
{
	if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

t_stack	*ft_lstlast(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_stack	*ft_lstnew(int num)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->num = num;
	node->next = NULL;
	return (node);
}

static int find_min(t_stack *a)
{
	int		min;

	min = a->num;
	while (a != NULL)
	{
		if (a->num < min)
			min = a->num;
		a = a->next;
	}
	return (min);
}

// O(n²)
void	simple_sort(t_stack **a, t_stack **b)
{
	int	min;

	while (*a != NULL && (*a)->next != NULL)
	{
		min = find_min(*a);
		while (*a != NULL && (*a)->next != NULL)
		{
			if (min != (*a)->num)
				op_ra(a);  // cтек сдвинулся внутри на след элемент
			else
			{
				op_pb(a, b);
				break ;
			}
		}
	}
	while (*b != NULL)
		op_pa(a, b);
}

void	print_stack(t_stack **a)
{
	while (*a != NULL)
	{
		printf("%d ", (*a)->num);
		(*a) = (*a)->next;
	}
}
*/

static size_t	ft_lstsize(t_stack *lst)
{
	int	hmn;

	hmn = 0;
	while (lst != NULL)
	{
		hmn++;
		lst = lst -> next;
	}
	return (hmn);
}

static size_t	ft_sqrt(size_t nb)
{
	int	n;

	n = 1;
	while (n * n <= nb)
		n++;
	return (n - 1);
}

static void	index_of_num(t_stack *a)
{
	t_stack *node_a;
	t_stack	*node_b;

	node_a = a;
	while (node_a != NULL)
	{
		node_b = a;
		node_a->index = 0;
		while (node_b != NULL)
		{
			if (node_b->num < node_a->num)
				node_a->index++;
			node_b = node_b->next;
		}
		node_a = node_a->next;
	}
}

static int	chunk_size(t_stack *a)
{
	// √n - количество чанков
	// n / √n - размер одного чанка
	size_t	size;
	size_t	amount_of_chunks;

	size = ft_lstsize(a);
	amount_of_chunks = ft_sqrt(size);
	return (size / amount_of_chunks);
}

// O(n√n)
void	medium_sort(t_stack **a, t_stack **b)
{
	int		i; 		// счетчик для чанков
	size_t	c_size; // размер одного чанка
	
	index_of_num(*a);
	c_size = chunk_size(*a);
	i = 0;
	
	while (*a != NULL)
	{
		while (*a != NULL)
		{
			if ((*a)->index <= (i+1) * c_size - 1)
			{
				op_pb(a, b);
			}
			else
			{
				op_ra(a); // стек внутри стал следующим
			}
		}
		i++;
	}
}

void	print_stack(t_stack *a)
{
	while (a != NULL)
	{
		printf("%d ", a->num);
		a = a->next;
	}
}

void	print_index(t_stack *a)
{
	while (a != NULL)
	{
		printf("%d ", a->index);
		a = a->next;
	}
}


int	main(void)
{
	// t_stack node_h = {0, NULL};
	// t_stack node_g = {777, &node_h};
	// t_stack node_f = {9, &node_g};
	t_stack node_e = {4, 0, NULL};
	t_stack node_d = {2, 0, &node_e};
	t_stack node_c = {5, 0, &node_d};
	t_stack node_b = {1, 0, &node_c};
	t_stack node_a = {3, 0, &node_b};

	t_stack *a = &node_a;
	//t_stack *b = NULL;

	index_of_num(a);
	print_stack(a);
	printf("\n");
	print_index(a);
	printf("\nchunk_size: %d\n", chunk_size(a));
	// simple_sort(&a, &b);
}