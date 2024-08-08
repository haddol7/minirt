/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:08:47 by daeha             #+#    #+#             */
/*   Updated: 2024/08/08 22:17:39 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- != 0 && (*s1 != '\0' || *s2 != '\0'))
	{	
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char) *s2);
		s1++;
		s2++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// int main(int argc, char **argv)
// {
// 	const char *s1 = (const char *)argv[1];
// 	const char *s2 = (const char *)argv[2];
// 	size_t n = (size_t)atoi(argv[3]);

// 	printf("%d",ft_strncmp("SP", "SPL", 3));
// 	return (0);
// }
