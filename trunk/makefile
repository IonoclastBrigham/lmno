# makefile
# LMNO LALR(1) parser generator

CC=/usr/bin/gcc
CFLAGS=-std=gnu99 -O2
TOUCH=/usr/bin/touch
srcdir=src/
builddir=build/
PREFIX=/usr/local/bin

all : lmno

lmno : ${builddir} ${builddir}action.o ${builddir}assert.o ${builddir}build.o ${builddir}configlist.o ${builddir}error.o ${builddir}main.o ${builddir}msort.o ${builddir}option.o ${builddir}parse.o ${builddir}plink.o ${builddir}report.o ${builddir}set.o ${builddir}table.o
	 ${CC} ${CFLAGS} -o lmno ${builddir}*.o
	 @echo "Build Successful!"

${builddir}action.o : ${srcdir}action.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}action.c -o ${builddir}action.o

${builddir}assert.o : ${srcdir}assert.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}assert.c -o ${builddir}assert.o

${builddir}build.o : ${srcdir}build.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}build.c -o ${builddir}build.o

${builddir}configlist.o : ${srcdir}configlist.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}configlist.c -o ${builddir}configlist.o

${builddir}error.o : ${srcdir}error.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}error.c -o ${builddir}error.o

${builddir}main.o : ${srcdir}main.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}main.c -o ${builddir}main.o

${builddir}msort.o : ${srcdir}msort.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}msort.c -o ${builddir}msort.o

${builddir}option.o : ${srcdir}option.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}option.c -o ${builddir}option.o

${builddir}parse.o : ${srcdir}parse.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}parse.c -o ${builddir}parse.o

${builddir}plink.o : ${srcdir}plink.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}plink.c -o ${builddir}plink.o

${builddir}report.o : ${srcdir}report.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}report.c -o ${builddir}report.o

${builddir}set.o : ${srcdir}set.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}set.c -o ${builddir}set.o

${builddir}table.o : ${srcdir}table.c ${srcdir}global.h
	${CC} ${CFLAGS} -c ${srcdir}table.c -o ${builddir}table.o

${srcdir}global.h : ${srcdir}action.h ${srcdir}assert.h ${srcdir}build.h ${srcdir}configlist.h ${srcdir}error.h ${srcdir}option.h ${srcdir}parse.h ${srcdir}plink.h ${srcdir}report.h ${srcdir}set.h ${srcdir}struct.h ${srcdir}table.h
	${TOUCH} ${srcdir}global.h

${builddir} :
	mkdir -p ${builddir}

debug : clean
	make lmno CFLAGS="-std=gnu99 -O0 -Wall -g"

install : lmno
	cp lmno "${PREFIX}/"
	cp parser_template.* "${PREFIX}/"
	 @echo "Install Successful!"

clean :
	rm -f ${builddir}*.o lmno
