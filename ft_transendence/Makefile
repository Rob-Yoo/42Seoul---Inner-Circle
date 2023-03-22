NAME = ft_transcendence

all : $(NAME)

$(NAME) :
	docker-compose -f srcs/docker-compose.yml up --build -d

clean :
	docker-compose -f srcs/docker-compose.yml down --remove-orphans --rmi all --volumes

fclean : clean
	rm -rf ${HOME}/data
	docker network prune --force
	docker volume prune --force
	docker system prune --all --force --volumes

re : fclean all
