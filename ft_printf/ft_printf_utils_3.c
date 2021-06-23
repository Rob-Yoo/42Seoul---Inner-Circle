/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 15:46:11 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/23 21:35:37 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

size_t			ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int		hex_len(unsigned long long n, int cnt)
{
	if ((n / 16) == 0)
		return (++cnt);
	return (hex_len(n / 16, ++cnt));
}

static void		hextoa_handler(char *s, char *hex, unsigned long long n, int i)
{
	if ((n / 16) == 0)
	{
		s[i] = hex[n];
		return ;
	}
	s[i] = hex[n % 16];
	hextoa_handler(s, hex, n / 16, --i);
}

char			*ft_hextoa(unsigned long long arg)
{
	char	*hex;
	char	*ret;
	int		len;

	hex = "0123456789abcdef";
	len = hex_len(arg, 0) + 1;
	ret = (char *)malloc(sizeof(char) * len);
	if (!ret)
		return (0);
	hextoa_handler(ret, hex, arg, len - 2);
	ret[len - 1] = '\0';
	return (ret);
}
