/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:13:31 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 18:10:38 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list *)ft_malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

// #include <stdio.h>

// int	main(int argc, char **argv)
// {
// 	t_list	*lst;
// 	char	*str;

// 	str = ft_strdup("Hello linked list");
// 	lst = ft_lstnew(str);
// 	free(str);
// 	printf("%s", lst->content);
// 	if (lst->next == NULL)
// 		printf("\nNULL");
// 	return (0);
// }
