#指定可执行文件的名字
TARGET := main

#指定编译版本
CPP_FLAGS='-std=c++11'

#指定编译器
CC := arm-linux-g++ -std=c++14

#CSRC指定工程中所有的C源文件列表
CSRCS := $(wildcard *.cc)

#OBJS指定工程中所有的.o文件列表
OBJS := $(patsubst %.cc,%.o,$(CSRCS))

#INCS指定头文件的目录
INCS += -I ./ -I ../inc -I /home/china/arm-jpeg/include

#LIBS指定所需要依赖的库以及库的搜索路径
LIBS += -L ../lib -L /home/china/arm-jpeg/lib -l jpeg -lpthread

#可执行文件的编译规则
$(TARGET) : $(OBJS)
	$(CC) $^ $(LIBS) -o $@

#.o文件的编译规则
%.o : %.cc
	$(CC) -c $< $(INCS) -o $@
	
#"清除":所有的中间文件和最终的可执行文件
clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)

install:
	cp main /mnt/hgfs/Yang/
	
