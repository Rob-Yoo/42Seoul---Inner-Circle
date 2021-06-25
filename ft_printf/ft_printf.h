/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:35:03 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/25 16:45:36 by jinyoo           ###   ########.fr       */
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
	int			minus;
	int			zero;
	char		flag;
	int			width;
	int			prec;
	int			prec_flag;
	int			width_flag;
}				t_inform;

int				ft_printf(const char *format, ...);

void			ft_write(char c, t_inform *inf);
void			width_handler(va_list ap, char w, t_inform *inf);
void			prec_handler(va_list ap, char p, t_inform *inf);
int				specifier_handler(va_list ap, char spec, t_inform *inf);
void			init_inform(t_inform *inf, int sign);

int				ft_cnt_nbr(long long n);
void			ft_putnbr(long long n);
char			*ft_toupper(char *s);

void			ft_printf_c(va_list ap, t_inform *inf);
void			ft_printf_per(t_inform *inf);
void			ft_printf_s(va_list ap, t_inform *inf);
void			ft_printf_int(va_list ap, t_inform *inf);
void			ft_printf_u(va_list ap, t_inform *inf);
int				ft_printf_hex(va_list ap, t_inform *inf, char spec);
int				ft_printf_p(va_list ap, t_inform *inf);

int				ft_isalpha(int c);
size_t			ft_strlen(const char *s);
char			*ft_hextoa(unsigned long long arg);
#endif
