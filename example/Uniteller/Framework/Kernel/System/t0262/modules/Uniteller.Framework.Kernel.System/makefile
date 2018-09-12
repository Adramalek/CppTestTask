include ~/Platform/common.make
INCDIRS = $(INC) -I../include -I../../include -I../../references
CFLAGS_DEBUG = $(CFLAGS) -D_ITERATOR_DEBUG_LEVEL=1

SRCS = ./Uniteller.Framework.Kernel.System.cpp machine.cpp StringUtils.cpp
OBJS = $(SRCS:%.cpp=Debug/Obj/%.o) Debug/Obj/Utils.o Debug/Obj/xregistrykey.o Debug/Obj/watermark.o


all: prepare compile

prepare:
	test -d Debug || mkdir -p Debug
	test -d Debug/Obj || mkdir -p Debug/Obj
	rm -f Debug/Obj/*.*

compile: $(OBJS) 
	g++ -shared $(INCDIRS) $(CFLAGS_DEBUG) ./metadata.S $(OBJS) -o ./Debug/Uniteller.Framework.Kernel.System.so -ldl -pthread

Debug/Obj/%.o: %.cpp
	g++ $(CFLAGS_DEBUG) $(INCDIRS) -c $<  -o $@

Debug/Obj/Utils.o:
	g++ $(INCDIRS) $(CFLAGS_DEBUG) -c ../../references/kernel/Utils.cpp -o Debug/Obj/Utils.o

Debug/Obj/xregistrykey.o:
	g++ $(INCDIRS) $(CFLAGS_DEBUG) -c ../../references/kernel/xregistrykey.cpp -o Debug/Obj/xregistrykey.o

Debug/Obj/watermark.o:
	g++ $(INCDIRS) $(CFLAGS_DEBUG) -c ../include/watermark.cpp -o Debug/Obj/watermark.o

