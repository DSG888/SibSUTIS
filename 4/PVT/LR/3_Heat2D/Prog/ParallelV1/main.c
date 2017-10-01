#include <inttypes.h>
#include <math.h>
#include <float.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define EPS 0.001
#define PI 3.14159265358979323846

#define IND(i, j) ((i) * nx + (j))

int main(int argc, char *argv[]) 
{
	double ttotal = -omp_get_wtime();
	int rows = (argc> 1) ? atoi(argv[1]) : 100;
	int cols = (argc> 2) ? atoi(argv[2]) : 100;
	const char *filename = (argc> 3) ? argv[3] : NULL;    
	if (cols < 1 || rows < 1) {
		fprintf(stderr, "Invalid size of grid: rows %d, cols %d\n", rows, cols);
		exit(EXIT_FAILURE);
	}
	int ny = rows;
	int nx = cols;
	double talloc = -omp_get_wtime();
	
	double *local_grid = malloc(ny * nx * sizeof(*local_grid));
	double *local_newgrid = malloc(ny * nx * sizeof(*local_newgrid));
	talloc += omp_get_wtime();
	
	double tinit = -omp_get_wtime();
	double dx = 1.0 / (nx - 1.0);
	#pragma omp parallel for
	for (int j = 0; j < nx; j++) {
		int ind = IND(0, j);
		local_newgrid[ind] = local_grid[ind] = sin(PI * dx * j);
	}
	#pragma omp parallel for
	for (int j = 0; j < nx; j++) {
		int ind = IND(ny -1, j);
		local_newgrid[ind] = local_grid[ind] = sin(PI * dx * j) * exp(-PI);
	}
	#pragma omp parallel for
	for (int i = 1; i < ny - 1; i++) {
		for (int j = 1; j < nx - 1; j++) {
			local_newgrid[IND(i, j)] = 0.0;
			local_grid[IND(i, j)] = 0.0;
		}
	}
	tinit += omp_get_wtime();
	
	int niters = 0;
	for (; ;) {
		niters++;
		
		#pragma omp parallel for
		for (int i = 1; i < ny - 1; i++) {
			for (int j = 1; j < nx - 1; j++) {
				local_newgrid[IND(i, j)] = (local_grid[IND(i - 1, j)] + local_grid[IND(i + 1, j)] + local_grid[IND(i, j - 1)] + local_grid[IND(i, j + 1)]) * 0.25;
			}
		}
		
		double maxdiff = -DBL_MAX;
		#pragma omp parallel for reduction(max:maxdiff)
		for (int i = 1; i < ny - 1; i++) {
			for (int j = 1; j < nx - 1; j++) {
				int ind = IND(i, j);
				maxdiff = fmax(maxdiff, fabs(local_grid[ind] - local_newgrid[ind]));
			}
		}
		
		double *p = local_grid;
		local_grid = local_newgrid;
		local_newgrid = p;
		
		if (maxdiff < EPS) break;
	}
	ttotal += omp_get_wtime();
	
	printf("# Heat 2D (serial): grid: rows %d, cols %d\n", rows, cols); 
	printf("# niters %d, total time (sec.): %.6f\n", niters, ttotal);
	printf("# talloc: %.6f, tinit: %.6f, titers: %.6f\n", talloc, tinit, ttotal - talloc - tinit);
	
	if (filename) {
		FILE *fout = fopen(filename, "w");
		if (!fout) {
			perror("Can't open file");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < ny; i++) {
			for (int j = 0; j < nx; j++) 
				fprintf(fout, "%.4f ", local_grid[IND(i, j)]);
			fprintf(fout, "\n");
		}
		fclose(fout);
	}
	
	return 0;
}
