CFLAGS=-Iinclude -Wall -Wextra -s

SRC=\
    src/utils.c \
    src/wingui.c \
    src/core/internal.c \
    src/core/text.c \
    src/core/widget.c \
    src/core/window.c \
    src/widgets/button.c \
    src/widgets/checkbox.c \
    src/widgets/entry.c \
    src/widgets/label.c \
    src/widgets/listbox.c \
	src/widgets/textbox.c


all: bin/libwinguia.dll bin/libwinguiw.dll bin/test.exe

bin/libwinguia.dll: $(SRC)
	gcc -shared -o bin/libwinguia.dll $(SRC) -lgdi32 $(CFLAGS)

bin/libwinguiw.dll: $(SRC)
	gcc -shared -o bin/libwinguiw.dll $(SRC) -lgdi32 $(CFLAGS) -DUNICODE -D_UNICODE

bin/test.exe: bin/libwinguia.dll examples/test.c
	gcc examples/test.c -o bin/test.exe $(CFLAGS) -lwinguia -Lbin

clean:
	del /S /Q bin

.PHONY: all clean