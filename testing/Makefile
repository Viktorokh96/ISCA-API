# Имя компилятора
CC = g++ 
# Указание компилятору на поиск заголовочных файлов
INCLUDE = -I./include  

LIBS = -lform 

# Направление поиска для make
vpath %.cpp ./iosys
# Установка флагов для компиляции объектных файлов
FLAGS = -Wall -c -g -std=c++98 $(INCLUDE)
# Установка флагов для линковщика
LDFLAGS = $(LIBS)
# Исходные файлы проекта
MAINSRC = framework.cpp
LOGSRC = log.cpp
IOSRC = iosystem.cpp
ISCASRC = isca.cpp
STDFSRC = stdform.cpp
# Объектные файлы
MAINOBJ = $(patsubst %.cpp,%.o,$(MAINSRC))
LOGOBJ = $(patsubst %.cpp,%.o,$(LOGSRC))
IOOBJ = $(patsubst %.cpp,%.o,$(IOSRC))
ISCAOBJ = $(patsubst %.cpp,%.o,$(ISCASRC))
STDFOBJ = $(patsubst %.cpp,%.o,$(STDFSRC))

ALLOBJ	= $(MAINOBJ) $(STDFOBJ) $(LOGOBJ) $(IOOBJ) $(INTEROBJ) $(ISCAOBJ) 

EXE := framework

all: $(EXE)

$(EXE) : $(ALLOBJ)
		$(CC) $^ $(LDFLAGS) -o $@

$(MAINOBJ) : $(MAINSRC)
		$(CC) $^ $(FLAGS) -o $@

$(IOOBJ) : $(IOSRC)
		$(CC) $^ $(FLAGS) -o $@

$(LOGOBJ) : $(LOGSRC)
		$(CC) $^ $(FLAGS) -o $@

$(ISCAOBJ) : $(ISCASRC)
		$(CC) $^ $(FLAGS) -o $@

$(STDFOBJ) : $(STDFSRC)
		$(CC) $^ $(FLAGS) -o $@

clean :
		rm -rf $(ALLOBJ) && rm $(EXE)
