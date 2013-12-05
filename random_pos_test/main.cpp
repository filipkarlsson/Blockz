#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
srand(time(NULL));
int random;
random = rand() % 1440;
cout << random;
return 0;

}
