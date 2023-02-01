# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 19:53:30 by jinyoo            #+#    #+#              #
#    Updated: 2023/01/09 19:54:57 by jinyoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: run

run:
	cd srcs/ && docker compose up
clean:
	cd srcs/ && docker compose down
fclean: clean
	sudo rm -rf /home/jinyoo/data/db /home/jinyoo/data/wp
	docker rmi srcs-mariadb srcs-wordpress srcs-nginx
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re