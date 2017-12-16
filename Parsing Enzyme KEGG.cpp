// Parsing Enzyme KEGG.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "linkedlist.h"
using namespace std;

bool Find(string str, string piece)
{
	int L = piece.size();
	for (int i = 0; i < str.size(); i++)
	{
		string text = str.substr(i, i + L);
		if (text == piece)
			return true;
	}
	return false;
}

long long ComputeHash(string word, int m)
{
	const int p = 22543;
	const int x = 26;
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
	return (hash % m);
}

int main()
{
	vector <LinkedList> Hash_Table;
	vector < pair<long long, string> > Gene_Bank;
	vector <string> Enzyme_File;
	vector <string> Gene_Names;
	vector <int> Enzyme_Hash;
	string line;
	string temp;
	string tempone;
	string temptwo;
	string tempthree;
	int count = 0;
	ifstream myfile("ko01000.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			stringstream ss(line);
			getline(ss, temp, ' ');
			if (temp == "E")
			{
				getline(ss, temp, ' ');
				getline(ss, temp, ' ');
				getline(ss, temp, ' ');
				getline(ss, temp, ' ');
				getline(ss, temp, ' ');
				getline(ss, temp, ' ');
				getline(ss, temp, ' ');
				getline(ss, temp, ' ');

				getline(ss, tempone, ' ');
				getline(ss, tempone, ':');

				stringstream sq(tempone);
				getline(sq, temptwo, ';');

				getline(ss, tempthree, ']');

				Enzyme_File.push_back(tempthree);
				Gene_Names.push_back(temptwo);
				count++;
			}
		}
		myfile.close();
	}

	cout << "P0" << endl;

	for (int i = 0; i < Gene_Names.size(); i++)
	{
		string copy = Gene_Names[i];
		stringstream ss(copy);
		getline(ss, temp, ',');
		Gene_Names[i] = temp;
	}

	cout << "P1" << endl;

	Hash_Table.resize(count);
	for (int i = 0; i < Enzyme_File.size(); i++)
	{
		//construct hash table for enzymes using n.m.l.k string as hash value
		if (!Find(Enzyme_File[i], "-"))
		{
			long long hash = ComputeHash(Enzyme_File[i], count);
			Hash_Table[hash].push_front(Gene_Names[i], Enzyme_File[i]);
			Enzyme_Hash.push_back(hash);
		}
	}

	cout << "P1.5" << endl;

	for (int i = 0; i < Enzyme_Hash.size(); i++)
	{
		Gene_Bank.push_back(make_pair(Enzyme_Hash[i], Gene_Names[i]));
	}
	cout << "P2" << endl;
	ofstream output_file("Gene Bank.txt");
	//upload hash table
	if (output_file.is_open())
	{
		for (int i = 0; i < Hash_Table.size(); i++)
		{
			output_file << i << ":";
			for (int j = 0; j < Hash_Table[i].size(); j++)
			{
				output_file << Hash_Table[i].top_front() << " " << Hash_Table[i].name() << ",";
				Hash_Table[i].pop_front();
			}
			output_file << endl;
		}
		output_file.close();
	}

	return 0;
}

