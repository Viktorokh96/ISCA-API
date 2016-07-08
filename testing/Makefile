# Имя компилятора
CC = g++ 
# Указание компилятору на поиск заголовочных файлов
INCLUDE = -I/usr/include  

LIBS = -lform -lreadline

# Направление поиска для make
vpath %.c ./services ./parses ./jobs ./signal
# Установка флагов для компиляции объектных файлов
FLAGS = -Wall -c -g -std=c++98 $(INCLUDE)
# Установка флагов для линковщика
LDFLAGS = $(LIBS)
# Исходные файлы проекта
MAINSRC = framework.cpp
# Объектные файлы
MAINOBJ = $(patsubst %.cpp,%.o,$(MAINSRC))

ALLOBJ	= $(MAINOBJ)

EXE := framework

all: $(EXE)

$(EXE) : $(ALLOBJ)
		$(CC) $^ $(LDFLAGS) -o $@

$(MAINOBJ) : $(MAINSRC)
		$(CC) $^ $(FLAGS) -o $@

clean :
		rm -rf $(ALLOBJ) && rm $(EXE)