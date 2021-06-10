/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:35:03 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/10 21:29:22 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "Libft/libft.h"
# define ERROR -1

typedef struct	s_inform{
	int			size;
}				t_inform;

void			ft_printf_chr(va_list ap, const char *format, t_inform *inform);
void			ft_printf_p(va_list ap, const char *format, t_inform *inform);
void			ft_printf_int(va_list ap, const char *format, t_inform *inform);
void			ft_printf_u(va_list ap, const char *format, t_inform *inform);
void			ft_printf_hex(va_list ap, const char *format, t_inform *inform);
#endif