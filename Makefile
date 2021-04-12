# instawm - window manager for linux
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c instawm.c util.c
OBJ = ${SRC:.c=.o}

.PHONY: all
all: options instawm

.PHONY: options
options:
	${info instawm build options}
	${info CFLAGS   = ${CFLAGS}}
	${info LDFLAGS  = ${LDFLAGS}}
	${info DESTDIR  = ${DESTDIR}}
	${info PREFIX   = ${PREFIX}}
	${info CC       = ${CC}}
	${info VERSION  = ${VERSION}}
	@true

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

instawm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

.PHONY: clean
clean:
	rm -f instawm ${OBJ} instawm-${CMS_VERSION}.tar.gz

.PHONY: dist
dist: clean
	tar --transform 's|^|instawm-${CMS_VERSION}/|' \
		-czf instawm-${CMS_VERSION}.tar.gz \
		LICENSE Makefile README.md config.def.h config.mk\
		instawm.1 drw.h util.h ${SRC}

.PHONY: install
install: all
	install -d ${DESTDIR}{${PREFIX}/bin,/usr/share/xsessions,${MANPREFIX}/man1}
	install -m  755 -s instawm ${DESTDIR}${PREFIX}/bin/
	install -Dm  755 instabar.sh ${DESTDIR}${PREFIX}/bin/instabar
	install -m  644 instawm.1 ${DESTDIR}${MANPREFIX}/man1/
	sed -i 's/VERSION/${VERSION}/g' ${DESTDIR}${MANPREFIX}/man1/instawm.1
	install -m  644 instawm.desktop ${DESTDIR}/usr/share/xsessions

.PHONY: uninstall
uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/instawm\
		${DESTDIR}${PREFIX}/bin/instabar\
		${DESTDIR}${MANPREFIX}/man1/instawm.1\
		${DESTDIR}/usr/share/xsessions/instawm.desktop\
