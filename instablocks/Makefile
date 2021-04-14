PREFIX ?= /usr/local
CC ?= cc
LDFLAGS = -lX11

output: instablocks.c blocks.def.h blocks.h
	${CC}  instablocks.c $(LDFLAGS) -o instablocks
blocks.h:
	cp blocks.def.h $@


clean:
	rm -f *.o *.gch instablocks
install: output
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 0755 instablocks $(DESTDIR)$(PREFIX)/bin/instablocks
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/instablocks