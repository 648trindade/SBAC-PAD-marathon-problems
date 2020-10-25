#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <math.h>
#include <cmath>
#include <time.h>

#define EPS 0.00000000001

/*
  Generates an input with 80 millions of points.
  You shall change the MAX constant in the closest-pair.cpp to allow input data
  with more than 80 millions of points.
*/
#define SIZE 40000000

using namespace std;

inline double abs2(double a) {
    if (a < 0.0)
        return -a;
    return a;
}

inline int cmp(double a, double b) {
    if (abs2(a - b) < EPS)
        return 0;
    else if (a > b)
        return 1;
    return -1;
}

class Ponto{
	public:
        double x;
        double y;

	bool operator<(const Ponto & ant)const {
        if (cmp(x, ant.x) == -1)
            return true;
        else if (cmp(x, ant.x) == 0 && cmp(y, ant.y) == -1)
            return true;
        else
            return false;
	}
};

unsigned long long llrand() {
    unsigned long long r = 0;

    for (int i = 0; i < 5; ++i) {
        r = (r << 15) | (rand() & 0x7FFF);
    }

    return r & 0xFFFFFFFFFFFFFFFFULL;
}

int main() {
  int c;

  set<Ponto> myPoints;

  srand(time(0));

  printf("%d\n", SIZE);
  for (c = 1; c <= SIZE;) {
        Ponto p;

        p.x = ((double)(llrand() % 20000000000) - 10000000000);
        p.y = ((double)(llrand() % 20000000000) - 10000000000);
        p.x /= 1000.0;
        p.y /= 1000.0;

        if (p.x >= -10000000.0 && p.x <= 10000000.0 && p.y >= -10000000.0 && p.y <= 10000000.0) {

            if (myPoints.find(p) != myPoints.end()) {
                continue;
            } else {
                myPoints.insert(p);
                printf("%.3lf %.3lf\n", p.x, p.y);
                c++;
            }
        }
  }
  printf("\n");

  return 0;
}
