CC = gcc
EXEC = AsciiArtTool
OBJS = AsciiArtTool.o RLEList.o main.o
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror
INCLUDES = -I/home/mtm/public/2122b/ex1 -Itool
TOOLTARGET = tool/$*.c

$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

AsciiArtTool.o : tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(INCLUDES) $(DEBUG_FLAG) $(COMP_FLAG) $(TOOLTARGET)

main.o: tool/main.c tool/AsciiArtTool.h
	$(CC) -c $(INCLUDES) $(DEBUG_FLAG) $(COMP_FLAG) $(TOOLTARGET)

clean:
	rm -f $(OBJS) $(EXEC)
