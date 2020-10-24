#include <iostream>
#include <sstream>
#include <sys/time.h>

using namespace std;

void sum(char* output, const long unsigned int d, const long unsigned int n)
{
    long unsigned int digits[d + 11];
    for (long unsigned int digit = 0; digit < d + 11; ++digit)
    {
        digits[digit] = 0;
    }
    for (long unsigned int i = 1; i <= n; ++i)
    {
        long unsigned int remainder = 1;
        for (long unsigned int digit = 0; digit < d + 11 && remainder; ++digit)
        {
            long unsigned int div = remainder / i;
            long unsigned int mod = remainder % i;
            digits[digit] += div;
            remainder = mod * 10;
        }
    }
    for (long unsigned int i = d + 11 - 1; i > 0; --i)
    {
        digits[i - 1] += digits[i] / 10;
        digits[i] %= 10;
    }
    if (digits[d + 1] >= 5)
    {
        ++digits[d];
    }
    for (long unsigned int i = d; i > 0; --i)
    {
        digits[i - 1] += digits[i] / 10;
        digits[i] %= 10;
    }
    stringstream stringstreamA;
    stringstreamA << digits[0] << ",";
    for (long unsigned int i = 1; i <= d; ++i)
    {
        stringstreamA << digits[i];
    }
    string stringA = stringstreamA.str();
    stringA.copy(output, stringA.size());
}

int main()
{
    struct timeval timevalA;
    struct timeval timevalB;

    long unsigned int d, n;

    cin >> d >> n;

    char output[d + 10]; // extra precision due to possible error

    gettimeofday(&timevalA, NULL);
    sum(output, d, n);
    gettimeofday(&timevalB, NULL);

    cout << output << endl;
    cout << "time="
         << timevalB.tv_sec - timevalA.tv_sec +
                (timevalB.tv_usec - timevalA.tv_usec) / (double)1000000
         << endl;

    return 0;
}