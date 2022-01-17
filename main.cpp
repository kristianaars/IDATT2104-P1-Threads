#include <iostream>
#include <cmath>
#include <thread>
#include <vector>

using namespace std;

int evenNumberDistCount = 0;

static double primeDist(int x) {
    return log(x * evenNumberDistCount);
}

static int max(int x, int y) {
    if(x > y) {return x; }
    else { return y; }
}

bool isPrime(int &n, int &i) {
    if(n == 0 || n == 1) {
        return true;
    }

    if(n == i) return true;

    if(n % i == 0) return false;

    return isPrime(n, ++i);
}

bool isPrime(int n) {
    int i = 2;
    return isPrime(n, i);
}

void findPrimes(vector<int> &bar, int start, int end) {
    for(int i = start; i < end; i++) {
        if(isPrime(i)) {
            bar.push_back(i);
        }
    }

    sort(bar.begin(), bar.end());
}

int main() {
    int threadCount = 1;
    int pNumberRangeStart = 432;
    int pNumberRangeEnd = 455;

    int totalPNumberCount = pNumberRangeEnd - pNumberRangeStart;
    evenNumberDistCount = totalPNumberCount / threadCount;

    double distSum = 0;
    double threadNumberRangeDistribution[threadCount];

    for(int i = 0; i < threadCount; i++) {
        threadNumberRangeDistribution[i] = primeDist(i + 1);
        distSum += threadNumberRangeDistribution[i];
    }

    //Creates a vector for each worker-thread to store it's result with primenumbers
    vector<vector<int>> primeSubTables(threadCount);
    vector<thread> workerThreads;

    for(int i = 0; i < threadCount; i++) { primeSubTables.emplace_back(); }
    int numIndex = pNumberRangeStart;

    for(int i = 0; i < threadCount; i++) {
        int numCount = max(1, ceil((threadNumberRangeDistribution[i] / distSum) * double(totalPNumberCount)));
        cout << "Running thread " << i << " with " << numCount << " numbers" << endl;

        int start = numIndex;
        int end = (numIndex += numCount);

        workerThreads.emplace_back(findPrimes, ref(primeSubTables[i]), start, end);
    }

    //Combine subvectors into one vector.
    vector<int> sortedPrimes;
    for(int i = 0; i < threadCount; i++) {
        workerThreads[i].join();
        auto subTable = primeSubTables[i];
        sortedPrimes.insert(sortedPrimes.end(), subTable.begin(), subTable.end());
    }

    for(int p : sortedPrimes) {
        cout << p << endl;
    }

    return 0;
}
