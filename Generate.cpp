#include "Generator.h"
#include <unistd.h>
#include <fstream>

int Generator::generateFiles()
{
	unsigned long int currentValue = start;
	for(unsigned int i = 0; i < numberOfSteps; ++i)
	{
		std::fstream fileStream;
		fileStream.open ("Tests/" + std::to_string(i) + ".txt", std::ifstream::out);
		
		for(unsigned int j = 0; j < currentValue;++j) //we have to count number of breaklines!!!
		{
			fileStream << generatePartOfString();
		}
		
		fileStream.close();
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
	
	for(unsigned int i = 0; i < pairs.size(); ++i)
	{
		std::cout << pairs[i].first << pairs[i].second << std::endl;
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
	std::cout << vectorToRandom.size();
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
	srand (mix(clock(), time(NULL), getpid()));
	unsigned int randomIndex = rand()%vectorToRandom.size();
	return vectorToRandom[randomIndex];
}

