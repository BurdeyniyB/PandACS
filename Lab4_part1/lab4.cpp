#include <iostream>
using namespace std;

int main()
{
    int k, i, j;
    cout << "Enter k = ";
    cin >> k;

    double Z = 1, p;
    p = 0;

    for (j = -2; j <= k; j++)
    {
        if (j != 1)
        {
            for (i = j; i <= k; i++)
            {
                p = 0;
                p += i / (i + 5.);
                if (j != 0 && j != 1) {
                    Z *= j / (j - 1.) * p;
                }
            }
        }
    }

    cout << "\nSum = " << Z;
    cin.get();
    cin.get();
    return 0;
}
