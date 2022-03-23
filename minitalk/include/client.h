/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:27:08 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/07 16:32:25 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <stdlib.h>
# include "util.h"

typedef struct s_msg
{
	char	*msg;
	int		pid;
}	t_msg;

#endif