#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    double omega_s = 6.0 / 1;
    double omega_m = 6.0 / 60;
    double omega_h = 30.0 / 3600;

    double rel_omega_ms = omega_s - omega_m;
    double rel_omega_hm = omega_m - omega_h;
    double rel_omega_hs = omega_s - omega_h;

    double T_ms = 360.0 / rel_omega_ms;
    double T_hm = 360.0 / rel_omega_hm;
    double T_hs = 360.0 / rel_omega_hs;

    double day_time = 43200;

    double deg;

    while (scanf("%lf", &deg) && deg >= 0)
    {
        double happy_time = 0.0;

        double out_ms = deg / rel_omega_ms;
        double out_hm = deg / rel_omega_hm;
        double out_hs = deg / rel_omega_hs;

        double in_ms = (360.0 - deg) / rel_omega_ms;
        double in_hm = (360.0 - deg) / rel_omega_hm;
        double in_hs = (360.0 - deg) / rel_omega_hs;

        for (double hs = 0.0; hs <= day_time; hs += T_hs)
        {
            for (double hm = 0.0; hm <= day_time; hm += T_hm)
            {
                if (hm + in_hm < hs + out_hs)
                    continue;
                if (hs + in_hs < hm + out_hm)
                    break;
                for (double ms = 0.0; ms <= day_time; ms += T_ms)
                {
                    if (ms + in_ms < hs + out_hs || ms + in_ms < hm + out_hm)
                        continue;
                    if (hm + in_hm < ms + out_ms || hs + in_hs < ms + out_ms)
                        break;
                    double res1;
                    res1 = max(max(hs + out_hs, hm + out_hm), ms + out_ms);
                    double res2;
                    res2 = min(min(hs + in_hs, hm + in_hm), ms + in_ms);
                    if (res1 < res2)
                        happy_time += res2 - res1;
                }
            }
        }
        printf("%.3lf\n", happy_time / day_time * 100.0); //所占比例的百分比
    }
}
