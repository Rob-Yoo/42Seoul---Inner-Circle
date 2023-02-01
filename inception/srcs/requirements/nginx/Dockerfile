FROM alpine:3.16

RUN apk update \
	&& apk upgrade \
	&& apk add nginx dumb-init openssl \
	&& mkdir /etc/nginx/tls \
	&& openssl req -newkey rsa:4096 -days 365 -nodes -x509 -subj "/C=KR/ST=Seoul/L=Seoul/O=42Seoul/OU=Gon/CN=jinyoo.42.fr" -out /etc/nginx/tls/jinyoo.42.fr.crt -keyout /etc/nginx/tls/jinyoo.42.fr.key \
	&& rm -rf /var/cache/apk/*

COPY ./conf/jinyoo_conf.conf /etc/nginx/http.d/default.conf

ENTRYPOINT ["/usr/bin/dumb-init", "--"]
CMD ["nginx", "-g", "daemon off;"]