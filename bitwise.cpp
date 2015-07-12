#include <iostream>

void swap(int& a, int& b)
{
	//X xor X = 0
	if (a != b)
	{
		//1 parallelism?
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;

		//2 overflow?
		a = a + b;
		b = a - b;
		a = a - b;
	}

	//3
	int tmp = a;
	a = b;
	b = tmp;
}

int isPower2(int num)
{
	return !((num - 1) & num);
}

int main()
{
	int item_1 = 0x001000;
	int item_2 = 0x002000;
	int item_3 = 0x003000;
	int item_4 = 0x004000;

	int flag = 0;

	flag = (item_1 | item_2);

	if (flag & item_1 && flag & item_2)
		std::cout << "item_1 and item_2 turned on" << std::endl;

	int a = 5;
	int b = 7;

	swap(a, b);

	std::cout << "a = " << a << " b = " << b << std::endl;

	std::cout << isPower2(1024) << std::endl;

	std::cin.get();

	return 0;
}