#include <iostream>
using namespace std;
int main()
{
  int i, j, k;
  cout << "Enter k = ";
  cin >> k;
  double Z = 1,p;
  for (j = -2; j <= k; j++)
  {
    if (j != 1)
    {
      for (i = j; i <= k; i++) 
      {
      p += i / (i + 5.);
      Z *= j / (j - 1.) * p;
      }
    }
  }
  cout << "\nSum = " << Z;
  cin.get();
  cin.get();
  return 0;
}