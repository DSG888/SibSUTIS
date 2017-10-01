#ifndef CURSACH_HEADER_H
#define CURSACH_HEADER_H
//диффуры//
double diffur(double x, double y_2, double igrek[]);
double mpd(double x, double igrek[]);
void F(double array[], double x, double igrek[]);
void shot_method();
void double_counting(double array[], int flag_print, double step);
void runge_kutt(double array[], int flag, double step);
//графика//
const int count_points = 6;
void init_window();
void draw_y(int steps, double **points);
void draw_spline(double *h, double *d, double **points_of_interpolation);
void gauss(double **array, int rows, int cols, double *&result);
void calculate_moments(double *h, double *d, double *&M);
double cubic_interpolation(double *h, double *d, double **points_of_interpolation, double x);
#endif
