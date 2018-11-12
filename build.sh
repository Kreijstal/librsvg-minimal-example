g++ -c main.c -o main.o -I/usr/include/glib-2.0/ -I/usr/include/librsvg-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/include/gdk-pixbuf-2.0/ -I/usr/include/cairo/

#g++ main.o -o output /usr/lib/librsvg-2.so /usr/lib/x86_64-linux-gnu/libgobject-2.0.so /usr/lib/x86_64-linux-gnu/libcairo.so
g++ main.o -o output /usr/local/lib/librsvg-2.so /usr/lib/x86_64-linux-gnu/libcairo.so

./output

