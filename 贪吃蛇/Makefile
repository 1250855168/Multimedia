#指定可执行文件的名字
TARGET := main

#指定编译器
CC := arm-linux-gcc

#CSRC指定工程中所有的C源文件列表
CSRCS := $(wildcard *.c)

#OBJS指定工程中所有的.o文件列表
OBJS := $(patsubst %.c,%.o,$(CSRCS))

#INCS指定头文件的目录
INCS += -I ./ -I ../inc -I /home/china/arm-jpeg/include

#LIBS指定所需要依赖的库以及库的搜索路径
LIBS += -L ../lib -L /home/china/arm-jpeg/lib -l jpeg -l pthread

#可执行文件的编译规则
$(TARGET) : $(OBJS)
	$(CC) $^ $(LIBS) -o $@

#.o文件的编译规则
%.o : %.c
	$(CC) -c $< $(INCS) -o $@
	
#"清除":所有的中间文件和最终的可执行文件
clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)
install:
	cp main /mnt/hgfs/Yang
	
