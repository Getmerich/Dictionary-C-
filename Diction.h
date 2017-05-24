//should contain simply the class (struct too)
#include <string>
#include <vector>

struct Entry {
	std::string word;
};

class Dictionary {
public:
	std::vector<Entry> list;
	std::string getWord(int);
	void print(void);
	void makeNew(int);
	void saveTxt(std::string);		//makes new file. doesn't amend to old one.
	void loadTxt(std::string);
	void clear(void);				//empties list to allow for multiple different .txt files
	void alphabetize(void);
	bool lookUp(std::string);		//returns true or false if found, also prints to screen for now
};