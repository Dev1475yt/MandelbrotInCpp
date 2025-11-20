# MandelbrotInCpp
Mandelbrot set generator in c++, can use fp128 for extra precision
NOTE: Will require some adjustments for using fp128 in current state

compile with:
bash: "g++ PROGRAM -o OUTPUT_NAME `sdl2-config --cflags --libs` -lquadmath"
and type ./OUTPUT_NAME
