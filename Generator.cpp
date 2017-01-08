#include "Generator.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <fstream>

int Generator::generateFiles()
{
	unsigned long int currentValue = start;
	//conf.txt
	std::fstream confFile;
	confFile.open ("Tests/conf.txt", std::ifstream::out);
	confFile << start << "\n";
	confFile << step << "\n";
	confFile << numberOfSteps << "\n";
	confFile.close();
	
	for(unsigned int i = 0; i < numberOfSteps; ++i)
	{
		std::fstream fileStream;
		fileStream.open ("Tests/" + std::to_string(i) + ".txt", std::ifstream::out);
		unsigned int wordLength = 0;
		for(unsigned int j = 0; j < currentValue;)
		{
			
			std::string partOfString = generatePartOfString();
			if(partOfString == "\n")
			{
				++j;
				wordLength = 0;
			}
			else
			{
				wordLength += 2;
				if(wordLength>50)
				{
					partOfString = "\n";
					++j;
					wordLength = 0;
				}
			}
			fileStream << partOfString;
			if(partOfString == "\n")
			{
				while(partOfString == "\n")
				{
					partOfString = generatePartOfString();
				}
				if(j<currentValue)
					{
						fileStream << partOfString;
						wordLength +=2;
					}
			}
		}
	
		
		fileStream.close();
		currentValue *= step;
	}
	return 0;
}

int Generator::generatePairs()
{
	bool breakLineWasFound = false;
	unsigned int breakLinePosition = 0;
	for(unsigned int i = 0; i < letters.size(); ++i)
	{
		for (unsigned int j = i; j < letters.size(); ++j)
		{
			std::string tempString;
			int tempFrequency = frequences[i]*frequences[j];
			
			if(letters[i] == '\n' || letters[j] == '\n')
			{
				if(breakLineWasFound)
				{
					pairs[breakLinePosition].second += tempFrequency;
				}
				else
				{
					pairs.push_back(std::pair<std::string, int>("\n", tempFrequency));
					breakLineWasFound = true;
					breakLinePosition = pairs.size() - 1;
				}
			}
			else
			{
				tempString.push_back(letters[i]);
				tempString.push_back(letters[j]);
				pairs.push_back(std::pair<std::string, int>(tempString, tempFrequency));
			}
		}
	}
	
	return 0;
}

int Generator::generateVectorToRandom()
{
	for(unsigned int i = 0; i < pairs.size(); ++i)
	{
		for(int j = 0; j < pairs[i].second; ++j)
		{
			vectorToRandom.push_back(pairs[i].first);
		}
	}
	return 0;
}

// http://www.concentric.net/~Ttwang/tech/inthash.htm
unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}


std::string Generator::generatePartOfString()
{
#ifdef _WIN32
	srand(1000);
#else
	srand(mix(clock(), time(NULL), getpid()));
#endif // _Windows

	
	unsigned int randomIndex = rand()%vectorToRandom.size();
	return vectorToRandom[randomIndex];
}
