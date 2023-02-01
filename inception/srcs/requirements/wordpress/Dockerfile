FROM alpine:3.16

RUN apk add dumb-init curl mariadb-client php-fpm php-mysqli php8-phar php-mbstring ssmtp\
	&& rm -rf /var/cache/apk/*

COPY tools/start_wordpress.sh /home/
COPY conf/www.conf /etc/php8/php-fpm.d/

RUN chmod +x /home/start_wordpress.sh

EXPOSE 9000

ENTRYPOINT ["/usr/bin/dumb-init", "--"]

CMD ["/home/start_wordpress.sh"]

