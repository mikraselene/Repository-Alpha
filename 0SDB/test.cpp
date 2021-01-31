#include <iostream>
#include <vector>
using namespace std;
int main()
{
    string s = "James Cummings and Ernest Schimmerling, editors. Lecture Note Series of the London Mathematical Society, vol. 406. Cambridge University Press, New York, xi + 419 pp. - Paul B. Larson, Peter Lumsdaine, and Yimu Yin. An introduction to Pmax forcing. pp. 5-23. - Simon Thomas and Scott Schneider. Countable Borel equivalence relations. pp. 25-62. - Ilijas Farah and Eric Wofsey. Set theory and operator algebras. pp. 63-119. - Justin Moore and David Milovich. A tutorial on set mapping reflection. pp. 121-144. - Vladimir G. Pestov and Aleksandra Kwiatkowska. An introduction to hyperlinear and sofic groups. pp. 145-185. - Itay Neeman and Spencer Unger. Aronszajn trees and the SCH. pp. 187-206. - Todd Eisworth, Justin Tatch Moore, and David Milovich. Iterated forcing and the Continuum Hypothesis. pp. 207-244. - Moti Gitik and Spencer Unger. Short extender forcing. pp. 245-263. - Alexander S. Kechris and Robin D. Tucker-Drob. The complexity of classification problems in ergodic theory. pp. 265-299. - Menachem Magidor and Chris Lambie-Ha";
    vector<string> vec;
    while (s.find(" - ") != s.npos)
    {
        vec.push_back(s.substr(0, s.find(" - ")));
        s.erase(0, s.find(" - ") + 3);
    }
    for (auto it : vec)
    {
        cout << it << endl;
    }
}