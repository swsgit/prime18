#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <omp.h>

typedef uint64_t u64;
typedef unsigned __int128 u128;

#ifdef WIN32

#include <windows.h>
double get_time() {
  LARGE_INTEGER t, f;
  QueryPerformanceCounter(&t);
  QueryPerformanceFrequency(&f);
  return (double)t.QuadPart / (double)f.QuadPart;
}

#else

#include <sys/time.h>
#include <sys/resource.h>

double get_time() {
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec + t.tv_usec * 1e-6;
}

#endif

void print_menu(void) {
  printf("// [Prime18]\n");
  printf("Options:\n");
  printf("\t -> 1 = quick\n");
  printf("\t -> 2 = average\n");
  printf("\t -> 3 = aggressive\n\n");
}

int get_option(void) {
  int opt;
  printf("Enter option [1, 2, 3] > ");
  scanf("%d", &opt);
  return (opt < 1 || opt > 3) ? -1 : opt;
}

u64 lucas_lehmer(u64 p) {
  u128 s = 4;
  u128 M = 1;
  for (size_t i = 0; i < p; i++) {
    M = M * 2;
  }
  M = M - 1;
  for (size_t i = 0; i < p - 2; i++) {
    s = ((s * s) - 2) % M;
  }

  return s == 0 ? p : 0;
}

void run(size_t size) {
  double start, stop, elapsed;
  u64 p, *prime;

  start = get_time();
  prime = malloc((size) * sizeof(*prime));
  #pragma omp parallel for
  for (p = 3; p < size; p++) {
    prime[p - 3] = lucas_lehmer(p);
  }
  free(prime);

  stop = get_time();
  elapsed = stop - start;
  printf("Elapsed time: %lfs", elapsed);
}

int main(void) {
  int opt;
  print_menu();
  opt = get_option();
  if (opt == -1) {
    printf("Invalid Selection\n");
    return 1;
  }
  switch (opt) {
  case 1:
    run(24000);
    break;
  case 2:
    run(240000);
    break;
  case 3:
    run(2400000);
    break;
  default:
    return 1;
  }

  return 0;
}
