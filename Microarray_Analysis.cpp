#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "linkedlist.h"
#include <algorithm>

using namespace std;

bool Find(string str, string piece)
{
	int L = piece.size();
	if (str.size() >= piece.size())
	{
		for (int i = 0; i <= str.size() - L; i++)
		{
			string text = str.substr(i, L);
			if (text == piece)
			{
				return true;
			}
		}
	}
	return false;
}

class CSVRow
{
private:
	std::vector<std::string>    m_data;
public:
	std::string const& operator[](std::size_t index) const
	{
		return m_data[index];
	}
	std::size_t size() const
	{
		return m_data.size();
	}
	void readNextRow(std::istream& str)
	{
		std::string         line;
		std::getline(str, line);

		std::stringstream   lineStream(line);
		std::string         cell;

		m_data.clear();
		while (std::getline(lineStream, cell, ','))
		{
			m_data.push_back(cell);
		}
		// This checks for a trailing comma with no data after it.
		if (!lineStream && cell.empty())
		{
			// If there was a trailing comma then add an empty element.
			m_data.push_back("");
		}
	}
};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}

long long ComputeHash(string word)
{
	const int p = 1000003;
	const int x = 12;
	long long hash = 0;
	long long x_powered = 1;
	char *word_array = new char[word.length() + 1];
	std::strcpy(word_array, word.c_str());
	for (int i = 0; i <= word.length(); i++)
	{
		hash = (hash % p) + (word_array[i] % p) * (x_powered % p);
		x_powered = (x_powered % p) * (x % p);
	}
	delete[] word_array;
	return (hash % 100000);
}

int main()
{
	vector <LinkedList> HashTable;
	HashTable.resize(100000);
	vector <string> titles;
	string hold;
	vector <string> names;
	CSVRow row;
	string str;
	vector <string> ColNames;
	vector < vector <int> > Total_Bank;
	vector <int> PathwayBank;
	vector <vector <string> > Data;
	string name;
	cout << "What is the name of your file." << endl;
	cin >> name;
	name += ".csv";
	ifstream Microarray_Genes(name);


	cout << "How many data columns?" << endl;
	int j = 0;
	cin >> j;
	Data.resize(j);
	int count = 0;
	cout << "Start" << endl;
	if (Microarray_Genes.is_open())
	{

		while (Microarray_Genes >> row)
		{
			if (count == 0)
			{
				for (int i = 0; i <= Data.size(); i++)
				{
					ColNames.push_back(row[i]);
				}
			}
			if (count > 0)
			{
				stringstream ss(row[0]);
				getline(ss, hold, ' ');
				transform(hold.begin(), hold.end(), hold.begin(), toupper);
				names.push_back(hold);
				for (int k = 0; k < Data.size(); k++)
				{
					string str = row[1+k];
					Data[k].push_back(str);
				}
			}
			count++;
		}

		Microarray_Genes.close();
	}

	cout << "Done reading" << endl;
	for (int i = 0; i < names.size(); i++)
	{
		long long hash = ComputeHash(names[i]);
		HashTable[hash].push_front(names[i], i);
	}

	//input data from all hsa files
	for (int n = 10; n <= 5300; n++)
	{
		PathwayBank.clear();
		str = "Pathways_HSA_" + to_string(n) + ".txt";
		ifstream Pathways(str);
		if (Pathways.is_open())
		{
			cout << "starting on " << str << "..." << endl;
			int count = 0;
			while (getline(Pathways, hold))
			{
				if (count == 0)
				{
					titles.push_back(hold);
				}
				if (count > 0)
				{
					transform(hold.begin(), hold.end(), hold.begin(), toupper);
					long long hash = ComputeHash(hold);
					if (HashTable[hash].find(hold))
					{
						if (HashTable[hash].name() == hold)
						{
							PathwayBank.push_back(HashTable[hash].top_front());
						}
						else
						{
							LinkedList Holder = HashTable[hash];
							while (Holder.name() != hold && !Holder.empty())
							{
								Holder.pop_front();
							}
							PathwayBank.push_back(Holder.top_front());
						}
					}
				}
				count++;
			}
			Total_Bank.push_back(PathwayBank);
			Pathways.close();
		}
	}
	
	for (int i = 0; i < Total_Bank.size(); i++)
	{
		if (Total_Bank[i].size() < 5)
		{
			Total_Bank.erase(Total_Bank.cbegin() + i);
			titles.erase(titles.cbegin() + i);
			i--;
		}
	}
	//Write into a csv file
	cout << "Done reading all the pathways" << endl;
	cout << "What would you like to name your file?" << endl;
	cin >> name;
	name += ".csv";
	ofstream myfile(name);
	myfile << "Pathway Name,";
	for (int i = 0; i < ColNames.size(); i++)
	{
		if (i < ColNames.size() - 1)
		{
			myfile << ColNames[i] << ",";
		}
		else
		{
			myfile << ColNames[i] << endl;
		}
	}

	for (int i = 0; i < Total_Bank.size(); i++)
	{
		for (int j = 0; j < Total_Bank[i].size(); j++)
		{
			//make lines in .csv file
			myfile << titles[i] << "," << names[Total_Bank[i][j]] << ",";
			for (int k = 0; k < Data.size(); k++)
			{
				if (k != Data.size() - 1)
				{
					myfile << Data[k][Total_Bank[i][j]] << ",";
				}
				else
				{
					myfile << Data[k][Total_Bank[i][j]] << endl;
				}
			}
		}
	}

	myfile.close();
	cout << "Done!" << endl;
	return 0;
}