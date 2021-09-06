# Mandelbrot Set - Generating Images

## Mandelbrot Set
The Mandelbrot set is the set of values of c in the complex plane for which the orbit of the critical point z = 0 under iteration of the quadratic map

                                                              Zn+1 = (Zn)^2 + C
remains bounded. Thus, a complex number c is a member of the Mandelbrot set if, when starting with z0 = 0 and applying the iteration repeatedly, 
the absolute value of zn remains bounded for all n > 0.

## Purpose of this project
This project was created to study the parallelism in the generation of Mandelbrot Set in terms of granularity.
It grabs a particular rectangle where Mandelbrot Set can be visualized and it is given an input number of threads and granularity.
The tasks to calculate are devided according to the number of threads and granularity and at the end of the program we are given .ppm file where the visualization is stored 
and the time it took for the program to calculate this particular set.

## Generated Image
![alt text](https://github.com/Ninachev/Parallel-processing-systems-course-FMI/blob/main/MandelbrotSet_ParallelProgramming/Mandelbrot-Set-Generated-Picture.png)
