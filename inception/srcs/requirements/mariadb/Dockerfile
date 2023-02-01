FROM alpine:3.16

RUN apk update \
	&& apk upgrade \
	&& apk add mariadb mariadb-client dumb-init \
	&& rm -rf /var/cache/apk/* 

COPY conf/mariadb-server.cnf /etc/my.cnf.d/
COPY tools/start_mariadb.sh /home

RUN chmod +x /home/start_mariadb.sh

EXPOSE 3306

ENTRYPOINT ["/usr/bin/dumb-init","--"]

CMD ["/home/start_mariadb.sh"]
