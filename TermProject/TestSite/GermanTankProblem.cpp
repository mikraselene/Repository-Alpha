#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <numeric>

using namespace std;

const int REAL_NUM = 10000;

vector<double> M1;
vector<double> M2;
vector<double> M3;
vector<double> M4;
vector<double> M5;
vector<double> M6;

class MeanValue
{
public:
    MeanValue(vector<int> sample)
    {
        mean = accumulate(sample.begin(), sample.end(), 0) * 1.0 / sample.size();
        result = 2 * mean - 1;
        relativeError = abs(result - REAL_NUM) * 1.0 / REAL_NUM;
        M1.push_back(relativeError);
        //cout << "result 1 = " << result << ", " << relativeError * 100 << "%" << endl;
    }

private:
    double mean;
    int result;
    double relativeError;
};

class MedianValue
{
public:
    MedianValue(vector<int> sample)
    {
        median = sample[sample.size() / 2];
        result = 2 * median - 1;
        relativeError = abs(result - REAL_NUM) * 1.0 / REAL_NUM;
        M2.push_back(relativeError);
        //cout << "result 2 = " << result << ", " << relativeError * 100 << "%" << endl;
    }

private:
    int median;
    int result;
    double relativeError;
};

class SymmetricInterval
{
public:
    SymmetricInterval(vector<int> sample)
    {
        min = sample[0];
        max = sample[sample.size() - 1];
        result = min + max - 1;
        relativeError = abs(result - REAL_NUM) * 1.0 / REAL_NUM;
        M3.push_back(relativeError);
        // cout << "result 3 = " << result << ", " << relativeError * 100 << "%" << endl;
    }

private:
    int min;
    int max;
    int result;
    double relativeError;
};

class MeanInterval
{
public:
    MeanInterval(vector<int> sample)
    {
        size = sample.size();
        max = sample[sample.size() - 1];
        result = (1 + 1.0 / size) * max - 1;
        relativeError = abs(result - REAL_NUM) * 1.0 / REAL_NUM;
        M4.push_back(relativeError);
        //cout << "result 4 = " << result << ", " << relativeError * 100 << "%" << endl;
    }

private:
    int size;
    int max;
    int result;
    double relativeError;
};

class Split
{
public:
    Split(vector<int> sample)
    {
        size = sample.size();
        max = sample[sample.size() - 1];
        result = (1 + 1.0 / (2 * size - 1)) * (max - 1.0 / (2 * size));
        relativeError = abs(result - REAL_NUM) * 1.0 / REAL_NUM;
        M5.push_back(relativeError);
        //cout << "result 5 = " << result << ", " << relativeError * 100 << "%" << endl;
    }

private:
    int size;
    int max;
    int result;
    double relativeError;
};

class Bayes
{
public:
    Bayes(vector<int> sample)
    {
        size = sample.size();
        max = sample[sample.size() - 1];
        result = (max - 1) * (size - 1) / (size - 2);
        relativeError = abs(result - REAL_NUM) * 1.0 / REAL_NUM;
        M6.push_back(relativeError);
        //cout << "result 6 = " << result << ", " << relativeError * 100 << "%" << endl;
    }

private:
    int size;
    int max;
    int result;
    double relativeError;
};

class Stats
{
public:
    Stats(int realNum)
    {
        vector<int> sample(realNum / 100);
        int seed = time(0);

        for (auto it = sample.begin(); it != sample.end(); it++)
        {
            srand(seed);
            int random = rand() % realNum + 1;
            while (find(sample.begin(), sample.end(), random) != sample.end())
            {
                random = rand() % realNum + 1;
            }
            *it = random;
        }
        sort(sample.begin(), sample.end());
        MeanValue a(sample);
        MedianValue b(sample);
        SymmetricInterval c(sample);
        MeanInterval d(sample);
        Split e(sample);
        Bayes f(sample);
    }
};

double Avg(vector<double> temp)
{
    double sum = 0;
    for (auto it : temp)
    {
        sum += it;
    }
    return sum / temp.size();
}

int main()
{
    for (int i = 1; i <= 1000; i++)
    {
        Stats k(10000);
    }
    cout << Avg(M1) << endl;
    cout << Avg(M2) << endl;
    cout << Avg(M3) << endl;
    cout << Avg(M4) << endl;
    cout << Avg(M5) << endl;
    cout << Avg(M6) << endl;
}