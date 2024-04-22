CC = gcc
CFLAGS = -I/usr/include/python3.10
LDFLAGS = -Wl,-rpath,/<path>/<to>/<plugin>/dataclay-plugin
LIBS = -lpython3.10 /<path>/<to>/<plugin>/dataclay-plugin/libdataclayplugin.so

SRC = main.c
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)


