g++ -g $(pkg-config --cflags --libs opencv) conway.cpp -o conway.out
time ./conway.out