/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 21:49:08 by jinyoo            #+#    #+#             */
/*   Updated: 2021/05/03 22:25:47 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int sign;
	int num;
	int i;

	i = 0;
	num = 0;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	else if (str[i] == '+')
		sign = 1;
	i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += *str - '0';
		i++;
	}
	return (sign * num);
}
