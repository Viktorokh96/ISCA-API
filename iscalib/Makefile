CC				= g++
ARCH			= 64
FLAGS_LIB		= -c -fPIC -Wall -g
OUT_LIB			= libisca_x$(ARCH).so

all:	
	$(CC) $(FLAGS_LIB) time/time.cpp -m$(ARCH)
	$(CC) $(FLAGS_LIB) fswork/fswork.cpp -m$(ARCH)
	$(CC) $(FLAGS_LIB) fswork/stat_file.c -m$(ARCH)
	$(CC) $(FLAGS_LIB) windlg/windlg.cpp -m$(ARCH)
	$(CC) $(FLAGS_LIB) screen/screen.cpp -m$(ARCH)
	$(CC) $(FLAGS_LIB) lang/lang.cpp -m$(ARCH)
	$(CC) $(FLAGS_LIB) configurator/configurator.cpp -m$(ARCH)
	$(CC) -shared -o $(OUT_LIB) fswork.o stat_file.o windlg.o screen.o lang.o configurator.o time.o -m$(ARCH)

clean:
	rm -rf *.o

clean-all:
	rm -rf *.o
	rm -rf $(OUT_LIB)