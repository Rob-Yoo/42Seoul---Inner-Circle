#!/bin/sh

if [ ! -e /var/www/html/wp-config.php ]; then

	# wordpress install
	sleep 3
	curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
	mv wp-cli.phar /usr/local/bin/wp
	mkdir -p /var/www/html
	adduser -D wordpress
	chown -R wordpress:wordpress /var/www/html

	wp core download --locale=en_GB --path='/var/www/html'
	until wp config create --allow-root --dbname=$DB_NAME --dbuser=$DB_USER --dbpass=$DB_USER_PW --dbhost=mariadb:3306 --path='/var/www/html' ; do
		echo "Waiting for MariaDB to start..."
		sleep 2
		done
	wp core install --allow-root --url=$DOMAIN_NAME --title='WordPress for Inception' --admin_user=$WP_USER1\
	--admin_password=$WP_USER1_PW --admin_email="jinyoo@student.42seoul.kr" --path='/var/www/html'
	wp user create --allow-root $WP_USER2 jin@student.42seoul.kr --user_pass=$WP_USER2_PW --role=author --path='/var/www/html'
fi

php-fpm8 -F
