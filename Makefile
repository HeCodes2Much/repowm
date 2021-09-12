# repowm - window manager for linux
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c repowm.c util.c
OBJ = ${SRC:.c=.o}

.PHONY: all
all: options repowm

.PHONY: options
options:
	${info repowm build options}
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

repowm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

.PHONY: clean
clean:
	rm -f repowm config.h ${OBJ} repowm-${CMS_VERSION}.tar.gz

.PHONY: dist
dist: clean
	tar --transform 's|^|repowm-${CMS_VERSION}/|' \
		-czf repowm-${CMS_VERSION}.tar.gz \
		LICENSE Makefile README.md config.def.h config.mk\
		repowm.1 drw.h util.h ${SRC}

.PHONY: install
install: all
	install -d ${DESTDIR}{${PREFIX}/bin,/usr/share/xsessions,${MANPREFIX}/man1}
	install -m  755 -s repowm ${DESTDIR}${PREFIX}/bin/
	install -Dm  755 layoutmenu ${DESTDIR}${PREFIX}/bin/layoutmenu
	install -Dm  755 repoopen ${DESTDIR}${PREFIX}/bin/repoopen
	install -Dm  755 repobar ${DESTDIR}${PREFIX}/bin/repobar
	install -m  644 repowm.1 ${DESTDIR}${MANPREFIX}/man1/
	sed -i 's/VERSION/${VERSION}/g' ${DESTDIR}${MANPREFIX}/man1/repowm.1
	install -m  644 repowm.desktop ${DESTDIR}/usr/share/xsessions

.PHONY: uninstall
uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/repowm\
		${DESTDIR}${PREFIX}/bin/layoutmenu\
		${DESTDIR}${PREFIX}/bin/repoopen\
		${DESTDIR}${PREFIX}/bin/repobar\
		${DESTDIR}${MANPREFIX}/man1/repowm.1\
		${DESTDIR}/usr/share/xsessions/repowm.desktop\
