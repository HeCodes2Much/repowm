# instawm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c instawm.c util.c
OBJ = ${SRC:.c=.o}

all: options instawm

options:
	@echo instawm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

instawm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f instawm ${OBJ} instawm-${VERSION}.tar.gz

dist: clean
	mkdir -p instawm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		instawm.1 drw.h util.h ${SRC} instawm.png transient.c instawm-${VERSION}
	tar -cf instawm-${VERSION}.tar instawm-${VERSION}
	gzip instawm-${VERSION}.tar
	rm -rf instawm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f instawm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/instawm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < instawm.1 > ${DESTDIR}${MANPREFIX}/man1/instawm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/instawm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/instawm\
		${DESTDIR}${MANPREFIX}/man1/instawm.1

.PHONY: all options clean dist install uninstall
