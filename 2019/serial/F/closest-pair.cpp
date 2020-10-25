#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <float.h>

#define EPS 0.0000000001
#define INF FLT_MAX
#define BRUTEFORCESSIZE 200
#define MAX 80000000

using namespace std;

struct Point
{
    double x;
    double y;
};

Point point[MAX];
Point border[MAX];

inline double abs2(double a) {
    if (a < 0.0)
        return -a;
    return a;
}

bool compX(const Point& a, const Point& b) {
    if (abs2(a.x-b.x)<EPS)
        return a.y<b.y;
    return a.x<b.x;
}

bool compY(const Point& a, const Point& b) {
    if (abs2(a.y-b.y)<EPS)
        return a.x<b.x;
    return a.y<b.y;
}

inline double sqr(double a) {
    return a * a;
}

inline double distance(Point a, Point b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}

double solve(int l, int r) {
    double minDist = INF;
    double dist;
    int i, j;
    if(r-l+1 <= BRUTEFORCESSIZE){
        for(i=l; i<=r; i++){
            for(j = i+1; j<=r; j++) {
                dist = distance(point[i], point[j]);
                if(dist<minDist){
                    minDist = dist;
                }
            }
        }
        return minDist;
    }

    int m = (l+r)/2;
    double dL = solve(l,m);
    double dR = solve(m,r);
    minDist = (dL < dR ? dL : dR);

    int k = l;
    for(i=m-1; i>=l && abs(point[i].x-point[m].x)<minDist; i--){
        border[k++] = point[i];
    }
    for(i=m+1; i<=r && abs(point[i].x-point[m].x)<minDist; i++){
        border[k++] = point[i];
    }

    if (k-l <= 1) return minDist;

    sort(&border[l], &border[l]+(k-l), compY);

    for(i=l; i<k; i++){
        for(j=i+1; j<k && border[j].y - border[i].y < minDist; j++){
            dist = distance(border[i], border[j]);
            if (dist < minDist){
                minDist = dist;
            }
        }
    }

    return minDist;
}

int main(){
    int n;

    scanf(" %d",&n);

    for(int i=0; i<n; i++){
        scanf(" %lf %lf",&point[i].x,&point[i].y);
    }
    sort(point, point+n, compX);

    cout << fixed << setprecision(6) << sqrt(solve(0,n-1)) << endl;

    return 0;
}
