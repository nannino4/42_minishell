/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 10:50:55 by jfabi             #+#    #+#             */
/*   Updated: 2021/09/21 15:21:44 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*ret;
	int		i;

	if (s == 0)
		return (0);
	if (len == 0)
		return (ft_strdup(""));
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == 0)
		return (0);
	i = 0;
	while (s[start + i] != 0 && i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
