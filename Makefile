# repowm - window manager for linux
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c repowm.c util.c
OBJ = ${SRC:.c=.o}

all: options repowm

options:
	@echo repowm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

repowm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f repowm ${OBJ} repowm-${VERSION}.tar.gz config.h

dist: clean
	mkdir -p repowm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		repowm.1 drw.h util.h ${SRC} repowm.png transient.c repowm-${VERSION}
	tar -cf repowm-${VERSION}.tar repowm-${VERSION}
	gzip repowm-${VERSION}.tar
	rm -rf repowm-${VERSION}

install: all
	install -d ${DESTDIR}{${PREFIX}/bin,${DESTDIR}${SHAREPREFIX}/xsessions,${DESTDIR}${MANPREFIX}/man1}
	install -m 755 -s repowm ${DESTDIR}${PREFIX}/bin/
	install -m 755 repobar ${DESTDIR}${PREFIX}/bin/
	install -m 755 repoopen ${DESTDIR}${PREFIX}/bin/
	install -m 755 layoutmenu ${DESTDIR}${PREFIX}/bin/
	install -m 644 repowm.1 ${DESTDIR}${MANPREFIX}/man1/
	sed -i 's/VERSION/${VERSION}/g' ${DESTDIR}${MANPREFIX}/man1/repowm.1
	install -m 644 repowm.desktop ${DESTDIR}${SHAREPREFIX}/xsessions

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/repowm\
		${DESTDIR}${PREFIX}/bin/repobar\
		${DESTDIR}${PREFIX}/bin/repoopen\
		${DESTDIR}${PREFIX}/bin/layoutmenu\
		${DESTDIR}${MANPREFIX}/man1/repowm.1\
		${DESTDIR}${SHAREPREFIX}/xsessions/repowm.desktop

.PHONY: all options clean dist install uninstall
