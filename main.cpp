#include <iostream>
#include <cmath>

using namespace std;

int evenNumberDistCount = 0;

static double primeDist(int x) {
    return log(x * evenNumberDistCount);
}

static int max(int x, int y) {
    if(x > y) {return x; }
    else { return y; }
}

bool isPrime(int n, int i) {
    if(n == 0 || n == 1) {
        return false;
    }

    if (n == i) return true;

    if(n % i == 0) return false;

    return isPrime(n, ++i);
}

void findPrimes(int table[], int start, int end, int tableOffset) {
    int primesFound = 0;
    for(int i = start; i < end; i++) {
        if(isPrime(i, 1)) {
            table[i + tableOffset + primesFound] = i;
        }
    }
}

int main() {
    int threadCount = 6;
    int pNumberRangeStart = 0;
    int pNumberRangeEnd = 1040;
    int totalPNumberCount = pNumberRangeEnd - pNumberRangeStart;

    evenNumberDistCount = totalPNumberCount / threadCount;

    double distSum = 0;
    double threadNumberRangeDistribution[threadCount];

    for(int i = 0; i < threadCount; i++) {
        threadNumberRangeDistribution[i] = primeDist(i + 1);
        distSum += threadNumberRangeDistribution[i];
    }

    double sum = 0;
    for(int i = 0; i < threadCount; i++) {
        threadNumberRangeDistribution[i] = max(1, ceil((threadNumberRangeDistribution[i] / distSum) * double(totalPNumberCount)));
        cout << threadNumberRangeDistribution[i] << endl;
        sum += threadNumberRangeDistribution[i];
    }

    int primes[totalPNumberCount];
    int numIndex = pNumberRangeStart;
    for(int numCount : threadNumberRangeDistribution) {
        int start = numIndex;
        int end = (numIndex += numCount);


    }

    return 0;
}
