//This one is the implementation file for Diction.h
//should only contain class "meat"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Diction.h"


std::string Dictionary::getWord(int place)
{
	return Dictionary::list[place].word;
}


void Dictionary::print(void)
{
	for (int i = 0; i < Dictionary::list.size(); i++)
	{
		std::cout << Dictionary::list[i].word << std::endl;
	}
	std::system("PAUSE");	//HELL YEA I LOVE THIS LINE
	return;
}

void Dictionary::makeNew(int N)
{
	Entry temp;
	for (int i = 0; i < N; i++)
	{
		std::cout << "What is the word?     " << std::endl;
		std::cin >> temp.word;
		Dictionary::list.push_back(temp);
	}
	return;
}

void Dictionary::saveTxt(std::string filename)
{
	std::ofstream wFile;				//Write File
	wFile.open(filename);			//should create file if it isn't there
	if (!wFile.is_open()) std::cout << "Unable to open file " << filename << "." << std::endl;
	if (wFile.is_open())
	{
		for (int i = 0; i < list.size(); i++)
		{
			wFile << list[i].word << std::endl;		//now place each word in separated by new line. ends at blank line.
		}
	}
	wFile.close();
	std::cout << "Saved!" << std::endl;
	return;
}


void Dictionary::loadTxt(std::string filename)
{
	Entry temp;
	std::ifstream rFile;
	rFile.open(filename);
	if (rFile.is_open())
	{
		while (getline(rFile, temp.word))		//getline returns true if there is info, false if not.
		{
			Dictionary::list.push_back(temp);
		}
		rFile.close();
	}
	else std::cout << "Unable to open file" << std::endl;
	return;
}

void Dictionary::clear(void)
{
	Dictionary::list.clear();
}



void Dictionary::alphabetize(void)
{
	Entry checker;
	std::vector<Entry> sorted;
	int empty = 0;

	/*  	GOTTA RESEARCH HOW TO CHECK SPELLING OF STRINGS.

	idea: use checker to scan whole list looking for the first that should
	appear, push it onto new temp list. Find next word in alphabetical order,
	push it. continue until old list is empty. only
	requires as many iterations as numWords! (factorial).
	*/

	while (!Dictionary::list.empty())
	{
		checker = Dictionary::list[0];		//set checker for comparisons
		empty = 0;							//reset emptier (shouldn't be needed...)
		for (int i = 0; i<Dictionary::list.size(); i++)
		{
			//case where it is a duplicate
			if (checker.word.compare(Dictionary::list[i].word) == 0  &&  i!=0)
			{
				Dictionary::list.erase(Dictionary::list.begin() + i);
				continue;
			}
			if (checker.word.compare(Dictionary::list[i].word) > 0) 	//handles case where checker is further up the list.
			{
				checker.word = Dictionary::list[i].word;
				empty = i;							//empty tracks which word in the list to remove later
			}
		}	//end of nested for

		sorted.push_back(checker);	//push the foundù word onto the ordered list
		Dictionary::list.erase(Dictionary::list.begin() + empty);	//remove the word you put in ordered list from the original
		//testing step
		//Dictionary::print();
	}	//end of while

	Dictionary::list = sorted;	//swap the now empty fullList with the sorted vector.
	return;
}



bool Dictionary::lookUp(std::string word)
{
	for (int i = 0; i < Dictionary::list.size(); i++)
	{
		if (word.compare(Dictionary::list[i].word) == 0)
		{
			std::cout << std::endl << "Found it!" << std::endl;
			std::cout << Dictionary::list[i].word << std::endl;
			//std::cout << Dictionary::list[i].def << std::endl;
			return true;
		}
	}
	
	return false;
}