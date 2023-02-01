#!/bin/sh

if [ ! -d /var/lib/mysql/$DB_NAME ]; then

	mariadb-install-db --datadir=/var/lib/mysql --user=mysql
	mkdir -p /run/mysqld
	chown -R mysql:mysql /run/mysqld /var/lib/mysql
	/usr/bin/mysqld_safe --datadir='/var/lib/mysql' --user=mysql &
	sleep 1
	mysql -e "CREATE DATABASE IF NOT EXISTS $DB_NAME CHARACTER SET utf8;CREATE USER IF NOT EXISTS '$DB_USER'@'%' IDENTIFIED BY '$DB_USER_PW';GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'%' WITH GRANT OPTION;FLUSH PRIVILEGES;ALTER USER 'root'@'localhost' IDENTIFIED BY '$DB_ROOT_PW';DELETE FROM mysql.user WHERE User='';DROP DATABASE IF EXISTS test;DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';FLUSH PRIVILEGES;"
	mysqladmin -uroot --password=$DB_ROOT_PW shutdown
fi

/usr/bin/mysqld_safe --datadir='/var/lib/mysql'
