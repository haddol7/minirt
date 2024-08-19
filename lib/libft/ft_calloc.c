/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:20:18 by daeha             #+#    #+#             */
/*   Updated: 2024/08/19 18:10:53 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*new_mem;
	size_t			i;

	i = 0;
	new_mem = (unsigned char *)ft_malloc(count * size * sizeof(unsigned char));
	if (new_mem == NULL)
		return (NULL);
	while (i < count * size)
	{
		new_mem[i] = 0;
		i++;
	}
	return ((void *)new_mem);
}
