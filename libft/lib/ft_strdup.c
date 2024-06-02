/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:18:52 by fkeitel           #+#    #+#             */
/*   Updated: 2024/05/21 17:34:24 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	counter;

	counter = 0;
	s2 = malloc(ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[counter] != '\0')
	{
		s2[counter] = s1[counter];
		counter++;
	}
	s2[counter] = '\0';
	return (s2);
}

/*
int main()
{
	char source[] = "lorem ipsum dolor sit amet";
	char* target = ft_strdup(source);
	printf("%s", target);
	free(target);
	return 0;
}
*/
