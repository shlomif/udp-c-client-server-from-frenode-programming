all: client serv

client: udp_client.c headerFiles.h
	gcc -g -o $@ $<

serv: udp_server.c headerFiles.h
	gcc -g -o $@ $<

clean:
	rm -f client serv
