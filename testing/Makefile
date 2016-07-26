# Имя компилятора
CC = g++ 
# Указание компилятору на поиск заголовочных файлов
INCLUDE = -I./include  

LIBS = -lform 

# Направление поиска исходных файлов для make
vpath %.cpp ./isca ./isca/iosys ./isca/stdform
# Направление поиска заголовочных файлов для make
vpath %.h ./include
# Установка флагов для компиляции объектных файлов
FLAGS = -Wall -c -g -std=c++98 $(INCLUDE)
# Установка флагов для линковщика
LDFLAGS = $(LIBS)
# Исходные файлы проекта и их зависимости от заголовочных файлов
MAINSRC = framework.cpp isca.h
LOGSRC = log.cpp log.h iosystem.h
IOSRC = iosystem.cpp iosystem.h stdform.h
APPLICSRC = application.cpp iosystem.h application.h
STDFSRC = stdform.cpp iosystem.h stdform.h
# Объектные файлы
MAINOBJ = framework.o
LOGOBJ = log.o
IOOBJ = iosystem.o
STDFOBJ = stdform.o
APPLICOBJ = application.o

ALLOBJ	= $(MAINOBJ) $(STDFOBJ) $(LOGOBJ) $(IOOBJ) $(INTEROBJ) $(APPLICOBJ) 

EXE := framework

all: $(EXE)

$(EXE) : $(ALLOBJ)
		$(CC) $^ $(LDFLAGS) -o $@

# $< - переменная хранящая первый параметр строки пререквизита
$(MAINOBJ) : $(MAINSRC)
		$(CC) $< $(FLAGS) -o $@

$(IOOBJ) : $(IOSRC)
		$(CC) $< $(FLAGS) -o $@

$(LOGOBJ) : $(LOGSRC)
		$(CC) $< $(FLAGS) -o $@

$(APPLICOBJ) : $(APPLICSRC)
		$(CC) $< $(FLAGS) -o $@

$(STDFOBJ) : $(STDFSRC)
		$(CC) $< $(FLAGS) -o $@

.PHONY: clean
clean :
		rm -rf $(ALLOBJ) && rm $(EXE)
