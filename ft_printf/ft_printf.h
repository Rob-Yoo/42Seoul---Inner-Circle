/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:35:03 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/22 17:00:21 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# define ERROR -1

typedef struct	s_inform{
	int			size;
	char		flag;
	int			width;
	char		prec;
	int			prec_flag;
	int			width_flag;
}				t_inform;


int				ft_printf(const char *format, ...);

void			ft_write(char c, t_inform *inform);
void			width_handler(va_list ap, char w, t_inform *inform);
void			prec_handler(va_list ap, char p, t_inform *inform);
int				specifier_handler(va_list ap, char spec, t_inform *inform);
void			init_inform(t_inform *inform, int sign);

int				ft_cnt_nbr(long long n);
void			ft_putnbr(long long n);

void			ft_printf_c(va_list ap, t_inform *inform);
void			ft_printf_s(va_list ap, t_inform *inform);
void			ft_printf_int(va_list ap, t_inform *inform);
void			ft_printf_u(va_list ap, t_inform *inform);
/*
void			ft_printf_p(va_list ap, const char *format, t_inform *inform);
void			ft_printf_hex(va_list ap, const char *format, t_inform *inform);
*/

int				ft_isalpha(int c);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
#endif
