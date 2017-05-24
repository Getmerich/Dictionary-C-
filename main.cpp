//Driver file. Mostly just for testing purposes.
//will change this to a gui if I get moving along
#include "Diction.h"
#include <iostream>

/*

int main(void)
{
	Dictionary List;
	int num;
	char flag;
	std::string check;
	
	//LOAD
	do
	{
		std::cout << "Load current dictionary?(y/n)" << std::endl;
		std::cin >> flag;
	} while (flag != 'y' && flag != 'n');
	if (flag == 'n') List.clear();
	if (flag == 'y') List.loadTxt("List.txt");
	List.print();
	
	//ADD
	std::cout << "How many more words do you want to add?   ";
	std::cin >> num;
	List.makeNew(num);

	//LOOK UP
	do
	{
		std::cout << "Look up a word?(y/n)" << std::endl;
		std::cin >> flag;
	} while (flag != 'y' && flag != 'n');
	if (flag == 'n') std::cout << "Ok!" << std::endl;
	if (flag == 'y')
	{
		std::cout << "What word?       ";
		std::cin >> check;
		bool exist = List.lookUp(check);
		if (exist) std::cout << "Success!" << std::endl;
		if (!exist) std::cout << "Could not find " << check << " in the dictionary." << std::endl;
	}

	//ALPHA
	do
	{
		std::cout << "Alphabetize the new list?(y/n)" << std::endl;
		std::cin >> flag;
	} while (flag != 'y' && flag != 'n');
	if (flag == 'y')
	{
		List.alphabetize();
		std::cout << "Sorted!" << std::endl;
	}
	if (flag == 'n') std::cout << "Not sorted!" << std::endl;

	//SAVE
	do
	{
		std::cout << "Save to file?(y/n)" << std::endl;
		std::cin >> flag;
	} while (flag != 'y' && flag != 'n');
	if (flag == 'y') List.saveTxt("List.txt");
	if (flag == 'n') std::cout << "Didn't save!" << std::endl;
	std::system("PAUSE");
	return (0);
}
*/