// Параллельная версия 5: дополнительная память вместо вычислений
#include <inttypes.h>
#include <math.h>
#include <float.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

struct particle { float x, y, z; };

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

const float G = 6.67e-11;

/*void calculate_forces(struct particle *p, struct particle *f, float *m, int n)
{
	#pragma omp for schedule(dynamic, 4) nowait
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				continue;
			float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) + powf(p[i].z - p[j].z, 2));
			float mag = (G * m[i] * m[j]) / powf(dist, 2);
			struct particle dir = {.x = p[j].x - p[i].x, .y = p[j].y - p[i].y, .z = p[j].z - p[i].z};
			f[i].x += mag * dir.x / dist;
			f[i].y += mag * dir.y / dist;
			f[i].z += mag * dir.z / dist;
		}
	}
}*/
void calculate_forces(struct particle *p, struct particle *f[], float *m, int n)
{
	int tid = omp_get_thread_num();
	int nthreads = omp_get_num_threads();
	for (int i = 0; i < n; i++)
	{
		f[tid][i].x = 0;
		f[tid][i].y = 0;
		f[tid][i].z = 0;
	}
	#pragma omp for schedule(dynamic, 8)
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) + powf(p[i].z - p[j].z, 2));
			float mag = (G * m[i] * m[j]) / powf(dist, 2);
			struct particle dir = { .x = p[j].x - p[i].x, .y = p[j].y - p[i].y, .z = p[j].z - p[i].z };
			f[tid][i].x += mag * dir.x / dist;
			f[tid][i].y += mag * dir.y / dist;
			f[tid][i].z += mag * dir.z / dist;
			f[tid][j].x += mag * dir.x / dist;
			f[tid][j].y += mag * dir.y / dist;
			f[tid][j].z += mag * dir.z / dist;
		}
	}
	#pragma omp single // Суммарная сила будет хранится в первой строке – f[0][i]
	{
		for (int i = 0; i < n; i++)
		{
			for (int tid = 1; tid < nthreads; tid++)
			{
				f[0][i].x += f[tid][i].x;
				f[0][i].y += f[tid][i].y;
				f[0][i].z += f[tid][i].z;
			}
		}
	}
}

void move_particles(struct particle *p, struct particle *f[], struct particle *v, float *m, int n, double dt)
{
	#pragma omp for
	for (int i = 0; i < n; i++)
	{
		struct particle dv = {.x = f[0][i].x / m[i] * dt, .y = f[0][i].y / m[i] * dt, .z = f[0][i].z / m[i] * dt,};
		struct particle dp = {.x = (v[i].x + dv.x / 2) * dt, .y = (v[i].y + dv.y / 2) * dt, .z = (v[i].z + dv.z / 2) * dt,};
		v[i].x += dv.x;
		v[i].y += dv.y;
		v[i].z += dv.z;
		p[i].x += dp.x;
		p[i].y += dp.y;
		p[i].z += dp.z;
		//f[i].x = f[i].y = f[i].z = 0;
	}
}


int main(int argc, char *argv[])
{
	double ttotal, tinit = 0, tforces = 0, tmove = 0;
	ttotal = wtime();
	int n = (argc > 1) ? atoi(argv[1]) : 10;
	char *filename = (argc > 2) ? argv[2] : NULL;
	tinit = -wtime();
	struct particle *p = malloc(sizeof(*p) * n);
	struct particle *f[omp_get_max_threads()];
	for (int i = 0; i < omp_get_max_threads(); i++)
		f[i] = malloc(sizeof(struct particle) * n);
	struct particle *v = malloc(sizeof(*v) * n);
	float *m = malloc(sizeof(*m) * n);
	for (int i = 0; i < n; ++i)
	{
		p[i].x = rand() / (float)RAND_MAX - 0.5;
		p[i].y = rand() / (float)RAND_MAX - 0.5;
		p[i].z = rand() / (float)RAND_MAX - 0.5;
		v[i].x = rand() / (float)RAND_MAX - 0.5;
		v[i].y = rand() / (float)RAND_MAX - 0.5;
		v[i].z = rand() / (float)RAND_MAX - 0.5;
		m[i] = rand() / (float)RAND_MAX * 10 + 0.01;
	}
	tinit += wtime();

	double dt = 1e-5;
	#pragma omp parallel
	{
		for (double t = 0; t <= 1; t += dt)
		{
			calculate_forces(p, f, m, n);
			#pragma omp barrier
			move_particles(p, f, v, m, n, dt);
			#pragma omp barrier
		}
	}


	ttotal = wtime() - ttotal;
	printf("# NBody (n=%d)\n", n);
	printf("# Elapsed time (sec): ttotal %.6f, tinit %.6f, tforces %.6f, tmove %.6f\n",
	ttotal, tinit, tforces, tmove);

	if (filename)
	{
		FILE *fout = fopen(filename, "w");
		if (!fout)
		{
			fprintf(stderr, "Can't save file\n");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < n; i++)
		{
			fprintf(fout, "%15f %15f %15f\n", p[i].x, p[i].y, p[i].z);
		}
		fclose(fout);
	}
	free(m);
	free(v);
	free(p);
	return 0;
}


