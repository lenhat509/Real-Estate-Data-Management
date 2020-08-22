#pragma once
#include <string>

class Parser
{
	protected:
		std::string** data;     // array of array of strings, where each inner array represents 1 data entry
		std::string delimiter;
		int numField;
		int numData;
		int curLine;

		/*
			std::string* splitToArr(const std::string str, std::string delimiter, int arrLength);

			Splits the string into multiple strings, stored in an array.
			If the amount of fields extracted is lower than expected, fill the remaining
			fields as empty strings.
			If the amount of fields extracted is higher than expected, ignore excess
			fields.

			Pre:	const std::string str - The string to split.
					std::string delimiter - Splitting points of the string.
					int arrLength - Number of splits.
			Post:	None.
			Return:	An array of splitted string from the input string.
		*/
		std::string* splitToArr(const std::string str, std::string delimiter, int arrLength);

	public:
		Parser(int numData, int numField, std::string delimiter = ",");
		~Parser();

		/*
			void clearData();

			Clears all stored data by de-allocating them.

			Pre:	None.
			Post:	All data arrays are de-allocated.
			Return:	None.
		*/
		void clearData();

		/*
			int getNumData();

			Get number of expected data.

			Pre:	None.
			Post:	None.
			Return:	Number of expected data.
		*/
		int getNumData();

		/*
			int getNumField();

			Get number of expected fields in each data.

			Pre:	None.
			Post:	None.
			Return:	Number of expected fields in each data.
		*/
		int getNumField();

		/*
			int getCurLinePos();

			Get the current position of the inserter.
			The inserter is defined as the line number at
			which the data will be inserted when append()
			is called.

			Pre:	None.
			Post:	None.
			Return:	The current position of the inserter.
		*/
		int getCurLinePos();

		/*
			void setCurLinePos(const int lineNum);

			Set the current position of the inserter.
			The inserter is defined as the line number at
			which the data will be inserted when append()
			is called.

			Pre:	const int lineNum - The new position of the inserter
			Post:	The position of the inserter is changed.
					If lineNum < 0, inserter is set at the beginning.
					If lineNum > numData, inserter is set at the end (numData),
					meaning no data can be further appended.
			Return:	None.
		*/
		void setCurLinePos(const int lineNum);

		/*
			std::string getDelimiter();

			Get the delimiter.

			Pre:	None.
			Post:	None.
			Return:	The current delimiter.
		*/
		std::string getDelimiter();

		/*
			void setDelimiter(const std::string newDelimiter)

			Change the delimiter.

			Pre:	None.
			Post:	None.
			Return:	The current delimiter.
		*/
		void setDelimiter(const std::string newDelimiter);

		/*
			std::string* getData(const int lineNum);

			Gets the data array from a specified line.

			Pre:	const int lineNum - The specified line.
			Post:	Nothing
			Return:	The data array at the specified line.
					nullptr if lineNum is out of bounds or
					data is not yet allocated at the specified line.
		*/
		std::string* getData(const int lineNum);

		/*
			bool setData(const int lineNum, const std::string input);

			Parse the input string as a data array and allocate it to
			the specified line number.

			Pre:	const int lineNum - The position to allocate the data array.
					const std::string input - The input string to parse.
			Post:	The input string is parsed to a data array and allocated
					to the specified line. If lineNum is out of bounds, do nothing.
			Return:	True - Operation is successful.
					False- Operation is not successful.
		*/
		bool setData(const int lineNum, const std::string input);

		/*
			bool append(const std::string input);

			Parse the input string as a data array and allocate it to
			the inserter.

			Pre:	const std::string input - The input string to parse.
			Post:	The input string is parsed to a data array and allocated
					to the line number specified by the inserter. If the inserter
					is at end, do nothing.
			Return:	True - Operation is successful.
					False- Operation is not successful.
		*/
		bool append(const std::string input);
};

Parser::Parser(int numData, int numField, std::string delimiter)
{
	this->numField = numField;
	this->numData = numData;
	this->delimiter = delimiter;

	data = new std::string*[numData];
	for (int i = 0; i < numData; i++)
	{
		data[i] = nullptr;
	}

	curLine = 0;
}

Parser::~Parser()
{
	clearData();
	delete [] data;
}

void Parser::clearData()
{
	for (int i = 0; i < numData; i++)
	{
		delete[] data[i];
	}
}

std::string* Parser::splitToArr(const std::string str, std::string delimiter, int arrLength)
{
	std::string* arr = new std::string[arrLength];
	long unsigned int startLoc = 0;
	int delimLoc = str.find(delimiter, startLoc);
	for (int i = 0; i < arrLength; i++)
	{
		if (delimLoc == std::string::npos)
		{
			if (startLoc != std::string::npos)
			{
				arr[i] = str.substr(startLoc, str.length() - startLoc);
				startLoc = std::string::npos;
			}
			else
			{
				arr[i] = "";
			}
		}
		else
		{
			arr[i] = str.substr(startLoc, delimLoc - startLoc);
			startLoc = delimLoc + 1;
			delimLoc = str.find(delimiter, startLoc);
		}
	}

	return arr;
}

int Parser::getNumData()
{
	return numData;
}

int Parser::getNumField()
{
	return numField;
}

int Parser::getCurLinePos()
{
	return curLine;
}

void Parser::setCurLinePos(const int lineNum)
{
	if (lineNum < 0)
	{
		curLine = 0;
	}
	else if (lineNum > numData)
	{
		curLine = numData;
	}
	else
	{
		curLine = lineNum;
	}
}

std::string Parser::getDelimiter()
{
	return delimiter;
}

void Parser::setDelimiter(const std::string newDelimiter)
{
	delimiter = newDelimiter;
}

std::string* Parser::getData(const int lineNum)
{
	if (lineNum < 0 || lineNum >= numData)
	{
		return nullptr;
	}
	return data[lineNum];
}

bool Parser::setData(const int lineNum, const std::string input)
{
	if (lineNum < 0 || lineNum >= numData)
	{
		return false;
	}
    
    // original data at position deleted
    try {
        delete [] data[lineNum];
    } catch (...) {
        std::cout << "ERROR: Already deleted" << std::endl;
    }
	data[lineNum] = splitToArr(input, delimiter, numField);

	return true;
}

bool Parser::append(const std::string input)
{
	if (setData(curLine, input))
	{
		curLine++;
		return true;
	}
	return false;
}
