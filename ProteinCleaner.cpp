// ProteinCleaner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



using namespace std;

bool Find(string str, string piece)
{
	int L = piece.size();
	if (str.size() > piece.size())
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

int main()
{
	vector <string> titles;
	string hold;
	vector <string> names;
	vector <string> ColNames;
	CSVRow row;
	string str;
	vector <int> PathwayBank;
	vector <vector <double> > Data;
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
				string s = "GN=";
				cout << count << endl;
				int i = 0;
				while (!Find(row[i], s))
				{
					i++;
				}

				stringstream ss(row[i]);
				getline(ss, hold, '=');
				getline(ss, hold, '=');
				getline(ss, hold, ' ');
				transform(hold.begin(), hold.end(), hold.begin(), toupper);
				names.push_back(hold);
				for (int k = 0; k < Data.size(); k++)
				{
					Data[k].push_back(stod(row[i + 1 + k]));
				}
			}
			count++;
		}

		Microarray_Genes.close();
	}

	//Write into a csv file
	cout << "What would you like to name your file?" << endl;
	cin >> name;
	name += ".csv";

	ofstream myfile(name);

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
	for (int i = 0; i < names.size(); i++)
	{
		myfile << names[i] << ",";
		for (int j = 0; j < Data.size(); j++)
		{
				myfile << Data[j][i] << ",";
		}
		myfile << endl;
	}


	myfile.close();
	cout << "Done!" << endl;
	return 0;
}