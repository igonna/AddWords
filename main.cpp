#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string getStrFromFile(std::string fileName)
{
	std::ifstream ifile;
	std::ostringstream ss;
	std::string str;
	
	ifile.open(fileName);
	if(!ifile)
	{
		std::cout << "no such file" << std::endl;
		return std::string("");
	}

	ss << ifile.rdbuf();
	str = ss.str();
	ss.str("");
	ifile.close();
	return str;
}
unsigned int getQuantityWords(std::string str)
{
	int quantityWords = 0;
	for(unsigned int step = 0; step < str.size(); ++step)
		if(str[step] == '\n')
			++quantityWords;
	return quantityWords;
}
void fillStrArray(std::string str, std::string* array, unsigned int quantityWords)
{
	unsigned int wordNumber = 0;
	for(unsigned int step = 0; step < quantityWords; ++step)
	{
		do
		{
			array[wordNumber][step] = str[step];
		}
		while(str[step] != '\n');
		++wordNumber;
	}
}
std::string changeChar(std::string str, char ch_1, char ch_2)
{
	for(unsigned int step = 0; step < str.size(); ++step)
		if(str[step] == ch_1)
			str[step] = ch_2;
	return str;
}
bool isSpecialCharacter(char ch)
{
	const char* special = "\n\t\r\a \0";
	unsigned int size = 5;
	for(unsigned int step = 0; step < size; ++step)
		if(ch == special[step])
			return true;
	return false;
}
std::string delSpecialCharacter(std::string str)
{
//	for(unsigned int step = 0; step < str.size(); ++step)
//		if(str[step] == '\n' || str[step] == '\t')
//			str[step] = ' ';
	while(isSpecialCharacter(str[str.size() - 1]))
		str.erase(str.size() - 1);
	return str;
}
struct StringArray
{
	//you must clean memory after use
	unsigned int QuantityWords;
	std::string* StrArr;
	unsigned int theBiggestWordSize;
};
StringArray fromStringToArray(std::string str)
{
	StringArray sStrArr;
	sStrArr.QuantityWords = 0;
	for(unsigned int numOfChar = 0; numOfChar < str.size(); ++numOfChar)
	{
		if(str[numOfChar] == '\n')
			++sStrArr.QuantityWords;
	}
	++sStrArr.QuantityWords;
	sStrArr.StrArr = new std::string[sStrArr.QuantityWords];
	unsigned int numOfChar = 0;
	unsigned int thisStrChar = 0;
	for(unsigned int numOfWord = 0; numOfWord < sStrArr.QuantityWords; ++numOfWord)
		while(numOfChar < str.size())
		{
			if(str[numOfChar] == '\n')
			{
				++numOfChar;
				thisStrChar = 0;
				break;
			}
			else
			{
				sStrArr.StrArr[numOfWord] += str[numOfChar];
				++numOfChar;
				++thisStrChar;
			}
		}
	return sStrArr;
}
unsigned int theBiggestWordSizeFromArray(std::string* StrArr, unsigned int quantityWords)
{
	unsigned int theBiggestWordSize = 0;
	for(unsigned int step = 0; step < quantityWords - 1; ++step)
		if(StrArr[step].size() > StrArr[step + 1].size())
			theBiggestWordSize = StrArr[step].size();
		else
			theBiggestWordSize = StrArr[step + 1].size();
	return theBiggestWordSize;
}
int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		std::cout << "few files" << std::endl;
		return 1;
	}
	std::ofstream ofile;
	std::string str_1 = getStrFromFile(std::string(argv[1]));
	std::string str_2 = getStrFromFile(std::string(argv[2]));
	

	str_1 = delSpecialCharacter(str_1);
	str_2 = delSpecialCharacter(str_2);

	
	StringArray sStrArr_1 = fromStringToArray(str_1);
	StringArray sStrArr_2 = fromStringToArray(str_2);

	sStrArr_1.theBiggestWordSize = theBiggestWordSizeFromArray(sStrArr_1.StrArr, sStrArr_1.QuantityWords);
	sStrArr_2.theBiggestWordSize = theBiggestWordSizeFromArray(sStrArr_2.StrArr, sStrArr_2.QuantityWords);
	
	unsigned int QuantityWordsOutput = (sStrArr_1.QuantityWords > sStrArr_2.QuantityWords) ? 
		sStrArr_1.QuantityWords : sStrArr_2.QuantityWords;

	ofile.open("out.txt");
	if(sStrArr_1.QuantityWords != sStrArr_2.QuantityWords)
		std::cout << "not equal!" << std::endl;
	for(unsigned int step = 0; step < QuantityWordsOutput; ++step)
		ofile << std::left
                        << std::setw(sStrArr_1.theBiggestWordSize + 4)
                        << sStrArr_1.StrArr[step]
                        << "\t-\t"
                        << sStrArr_2.StrArr[step] << std::endl;

	delete[] sStrArr_1.StrArr;
	delete[] sStrArr_2.StrArr;
	ofile.close();
	return 0;
}
