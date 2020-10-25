#include "pi.h"
#include <iostream>
#include <sys/time.h>

using namespace std;

int main()
{
    struct timeval timevalA;
    struct timeval timevalB;
    int places;

    cin >> places;

    gettimeofday(&timevalA, NULL);
    pi PI(places);
    cout << PI << endl;
    gettimeofday(&timevalB, NULL);

    cout << "time="
         << timevalB.tv_sec - timevalA.tv_sec +
                (timevalB.tv_usec - timevalA.tv_usec) / (double)1000000
         << endl;

    return 0;
}
