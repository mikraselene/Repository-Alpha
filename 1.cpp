#include <iostream>
#define BLACK "\e[30m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"
#define CYAN "\e[36m"
#define WHITE "\e[37m"

#define BLACK_BACKGROUND "\e[40m"
#define RED_BACKGROUND "\e[41m"
#define GREEN_BACKGROUND "\e[42m"
#define YELLOW_BACKGROUND "\e[43m"
#define BLUE_BACKGROUND "\e[44m"
#define PURPLE_BACKGROUND "\e[45m"
#define CYAN_BACKGROUND "\e[46m"
#define WHITE_BACKGROUND "\e[47m"

#define RESET_COLOR "\e[0m"

using namespace std;
int main()
{
	for (int i = 30; i <= 47; i++)
	{
		//printf("\\e[%dm: \e[%dm salve munde!\e[0m\n", i, i);
	}
	cout << WHITE << RED_BACKGROUND << " //// WARNING //// " << RESET_COLOR << endl;
}
