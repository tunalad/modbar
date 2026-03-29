include config.mk

SCRIPTS = $(wildcard scripts/*)

all: modbar

scripts.h: $(SCRIPTS)
	@{ \
	  echo "/* THIS FILE IS AUTO-GENERATED, DO NOT EDIT IT! */"; \
	  for f in $(SCRIPTS); do \
	    name=$$(basename $$f | sed 's/\..*$$//' | tr '-' '_'); \
		echo "static const char *$$name ="; \
	    sed 's/\\/\\\\/g; s/"/\\"/g; s/^/"/; s/$$/\\n"/' $$f; \
	    echo ";"; \
	  done \
	} > $@

modbar: modbar.c config.h scripts.h
	chmod +x ./scripts/*
	${CC} -o modbar modbar.c ${CFLAGS} ${LDFLAGS}

clean:
	rm -f *.o modbar scripts.h

install: modbar
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f modbar ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/modbar

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/modbar

.PHONY: all clean install uninstall
