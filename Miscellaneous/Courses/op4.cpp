#include <cstring>
#include <iostream>
#include <cmath>
#define MAX_N 10
#define DIMENSION 3
using namespace std;

class Test
{
public:
    Test()
    {
        vec = new int[DIMENSION];
        memset(vec, 0, DIMENSION);
        label = "unnamed";
    }
    Test(const int *A)
    {
        vec = new int[DIMENSION];
        for (int i = 0; i < DIMENSION; i++)
        {
            vec[i] = A[i];
        }
    }
    int &operator[](int i) const
    {
        return vec[i];
    }
    double operator()() const
    {
        int sum = 0;
        for (int i = 0; i < DIMENSION; i++)
        {
            sum += vec[i] * vec[i];
        }
        return sqrt(sum * 1.0);
    }
    bool operator==(const Test &A) const
    {
        bool flag = 1;
        for (int i = 0; i < DIMENSION; i++)
        {
            if (vec[i] != A.vec[i])
            {
                flag = 0;
                break;
            }
        }
        return flag;
    }
    bool operator!=(const Test &A) const
    {
        return !(*this == A);
    }
    Test &operator=(const Test &A)
    {
        for (int i = 0; i < DIMENSION; i++)
        {
            vec[i] = A.vec[i];
        }
        return *this;
    }
    friend Test operator+(const Test &A, const Test &B)
    {
        int T[3];
        for (int i = 0; i < DIMENSION; i++)
        {
            T[i] = A.vec[i] + B.vec[i];
        }
        return Test(T);
    }
    friend Test operator-(const Test &A, const Test &B)
    {
        int T[DIMENSION];
        for (int i = 0; i < DIMENSION; i++)
        {
            T[i] = A.vec[i] - B.vec[i];
        }
        return Test(T);
    }
    friend Test operator*(const Test &A, const Test &B)
    {
        Test T;
        T.vec[0] = A.vec[1] * B.vec[2] - A.vec[2] * B.vec[1];
        T.vec[1] = A.vec[2] * B.vec[0] - A.vec[0] * B.vec[2];
        T.vec[2] = A.vec[0] * B.vec[1] - A.vec[1] * B.vec[0];
        return T;
    }
    friend int operator^(const Test &A, const Test &B)
    {
        int sum = 0;
        for (int i = 0; i < DIMENSION; i++)
        {
            sum += A.vec[i] * B.vec[i];
        }
        return sum;
    }
    friend ostream &operator<<(ostream &output, const Test &A)
    {
        printf("[");
        for (int i = 0; i < DIMENSION - 1; i++)
        {
            printf("%d, ", A.vec[i]);
        }
        printf("%d]", A.vec[DIMENSION - 1]);
        return output;
    }
    friend istream &operator>>(istream &input, Test &A)
    {
        for (int i = 0; i < DIMENSION; i++)
        {
            scanf("%d", &A.vec[i]);
        }
        return input;
    }
    double PNorm(int p)
    {
        int sum = 0;
        for (int i = 0; i < DIMENSION; i++)
        {
            sum += pow(vec[i], p);
        }
        return pow(sum, 1.0 / p);
    }
    void GiveLabel(string lb)
    {
        label = lb;
    }
    string GetLabel()
    {
        return label;
    }

private:
    int *vec;
    string label;
};
Test B[MAX_N];

int Find(Test &v1, Test &v2, string label1, string label2)
{
    bool flag1 = 0;
    bool flag2 = 0;
    for (int i = 0; i < MAX_N; i++)
    {
        if (B[i].GetLabel() == label1)
        {
            v1 = B[i];
            flag1 = 1;
        }
        if (B[i].GetLabel() == label2)
        {
            v2 = B[i];
            flag2 = 1;
        }
    }
    return (int)flag2 * 2 + (int)flag1;
}
void Input(string label, int &t)
{
    bool flag = 0;
    printf("%s = ", label.c_str());
    for (int i = 0; i <= t; i++)
    {
        if (B[i].GetLabel() == label)
        {
            cin >> B[i];
            cout << label << " = " << B[i] << endl;
            flag = 1;
        }
    }
    if (!flag)
    {
        cin >> B[t];
        B[t].GiveLabel(label);
        cout << label << " = " << B[t] << endl;
        t++;
    }
}
void Output(string label)
{
    bool flag = 0;
    for (int i = 0; i < MAX_N; i++)
    {
        if (B[i].GetLabel() == label)
        {
            cout << label << " = " << B[i] << endl;
            flag = 1;
        }
    }
    if (!flag)
    {
        printf("%s: label not found\n", label.c_str());
    }
}
void Add(string label1, string label2)
{
    Test v1;
    Test v2;
    int r = Find(v1, v2, label1, label2);
    if (r == 3)
    {
        printf("%s + %s = ", label1.c_str(), label2.c_str());
        cout << v1 << " + " << v2 << endl;
        for (int i = 1; i <= label1.length() + label2.length() + 3; i++)
        {
            printf(" ");
        }
        Test v3;
        v3 = v1 + v2;
        cout << " = " << v3 << endl;
    }
    else if (r == 2)
    {
        printf("%s: label not found\n", label1.c_str());
    }
    else if (r == 1)
    {
        printf("%s: label not found\n", label2.c_str());
    }
    else
    {
        printf("%s, %s: label not found\n", label1.c_str(), label2.c_str());
    }
}
void Subtract(string label1, string label2)
{
    Test v1;
    Test v2;
    int r = Find(v1, v2, label1, label2);
    if (r == 3)
    {
        printf("%s - %s = ", label1.c_str(), label2.c_str());
        cout << v1 << " - " << v2 << endl;
        for (int i = 1; i <= label1.length() + label2.length() + 3; i++)
        {
            printf(" ");
        }
        Test v3;
        v3 = v1 - v2;
        cout << " = " << v3 << endl;
    }
    else if (r == 2)
    {
        printf("%s: label not found\n", label1.c_str());
    }
    else if (r == 1)
    {
        printf("%s: label not found\n", label2.c_str());
    }
    else
    {
        printf("%s, %s: label not found\n", label1.c_str(), label2.c_str());
    }
}
void Dot(string label1, string label2)
{
    Test v1;
    Test v2;
    int r = Find(v1, v2, label1, label2);
    if (r == 3)
    {
        printf("%s .* %s = ", label1.c_str(), label2.c_str());
        cout << v1 << " .* " << v2 << endl;
        for (int i = 1; i <= label1.length() + label2.length() + 4; i++)
        {
            printf(" ");
        }
        int s = v1 ^ v2;
        cout << " = " << s << endl;
    }
    else if (r == 2)
    {
        printf("%s: label not found\n", label1.c_str());
    }
    else if (r == 1)
    {
        printf("%s: label not found\n", label2.c_str());
    }
    else
    {
        printf("%s, %s: label not found\n", label1.c_str(), label2.c_str());
    }
}
void Cross(string label1, string label2)
{
    Test v1;
    Test v2;
    int r = Find(v1, v2, label1, label2);
    if (r == 3)
    {
        printf("%s * %s = ", label1.c_str(), label2.c_str());
        cout << v1 << " * " << v2 << endl;
        for (int i = 1; i <= label1.length() + label2.length() + 3; i++)
        {
            printf(" ");
        }
        Test v3;
        v3 = v1 * v2;
        cout << " = " << v3 << endl;
    }
    else if (r == 2)
    {
        printf("%s: label not found\n", label1.c_str());
    }
    else if (r == 1)
    {
        printf("%s: label not found\n", label2.c_str());
    }
    else
    {
        printf("%s, %s: label not found\n", label1.c_str(), label2.c_str());
    }
}
void Norm(string label, int p)
{
    bool flag = 0;
    for (int i = 0; i < MAX_N; i++)
    {
        if (B[i].GetLabel() == label)
        {
            Test v = B[i];
            printf("||%s||%d = %g\n", label.c_str(), p, v.PNorm(p));
            flag = 1;
        }
    }
    if (!flag)
    {
        printf("%s: label not found\n", label.c_str());
    }
}
void Mod(string label)
{
    bool flag = 0;
    for (int i = 0; i < MAX_N; i++)
    {
        if (B[i].GetLabel() == label)
        {
            printf("|%s| = %g\n", label.c_str(), B[i]());
            flag = 1;
        }
    }
    if (!flag)
    {
        printf("%s: label not found\n", label.c_str());
    }
}
void IsEqual(string label1, string label2, bool pos)
{
    Test v1;
    Test v2;
    int r = Find(v1, v2, label1, label2);
    if (r == 3)
    {
        if ((v1 == v2) ^ pos)
        {
            printf("N\n");
        }
        else
        {
            printf("Y\n");
        }
    }
    else if (r == 2)
    {
        printf("%s: label not found\n", label1.c_str());
    }
    else if (r == 1)
    {
        printf("%s: label not found\n", label2.c_str());
    }
    else
    {
        printf("%s, %s: label not found\n", label1.c_str(), label2.c_str());
    }
}
int main()
{
    int t = 0;
    while (1)
    {
        printf(">>");
        string command;
        cin >> command;
        if (command == "in")
        {
            string label;
            cin >> label;
            Input(label, t);
        }
        else if (command == "out")
        {
            string label;
            cin >> label;
            Output(label);
        }
        else if (command == "add")
        {
            string label1;
            string label2;
            cin >> label1 >> label2;
            Add(label1, label2);
        }
        else if (command == "sub")
        {
            string label1;
            string label2;
            cin >> label1 >> label2;
            Subtract(label1, label2);
        }
        else if (command == "dot")
        {
            string label1;
            string label2;
            cin >> label1 >> label2;
            Dot(label1, label2);
        }
        else if (command == "cross")
        {
            string label1;
            string label2;
            cin >> label1 >> label2;
            Cross(label1, label2);
        }
        else if (command == "norm")
        {
            string label;
            int p;
            cin >> label >> p;
            Norm(label, p);
        }
        else if (command == "mod")
        {
            string label;
            cin >> label;
            Mod(label);
        }
        else if (command == "==?")
        {
            string label1;
            string label2;
            cin >> label1 >> label2;
            IsEqual(label1, label2, 1);
        }
        else if (command == "!=?")
        {
            string label1;
            string label2;
            cin >> label1 >> label2;
            IsEqual(label1, label2, 0);
        }
        else if (command == "exit")
        {
            return 0;
        }
        else if (command == "help")
        {
            printf("in x         >> x\n");
            printf("out x        << x\n");
            printf("add x y      x + y\n");
            printf("sub x y      x - y\n");
            printf("dot x y      x .* y\n");
            printf("cross x y    x * y\n");
            printf("norm x p     ||x||p\n");
            printf("mod x        |x|\n");
            printf("==? x y      x == y\n");
            printf("!=? x y      x != y\n");
            printf("exit         exit\n");
        }
        else
        {
            printf("%s: command not found\n", command.c_str());
        }
        printf("\n");
    }
}
