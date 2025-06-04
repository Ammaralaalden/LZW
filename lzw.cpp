#include "lzw.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<int> encoding(string s1) 
{
	if (s1.empty()) 
	{
		return vector<int>();
	}

	// словарь ASCII
	map<string, int> dictionary;
	for (int i = 0; i < 256; i++) 
	{
		string ch(1, static_cast<char>(i));
		dictionary[ch] = i;
	}

	string current_string = "";
	vector<int> output;
	int code = 256;

	cout << "Encoding\nString\tOutput_Code\tAddition" << endl;

	for (char c : s1) 
	{
		string next_string = current_string + c;
		if (dictionary.find(next_string) != dictionary.end()) 
		{
			current_string = next_string;
		} 
		else 
		{
			cout << current_string << "\t" << dictionary[current_string] << "\t\t";

			if (code < 4096) 
			{
 				dictionary[next_string] = code;
				cout << next_string << "\t" << code;
				code++;
			}
			cout << endl;

			output.push_back(dictionary[current_string]);
			current_string = string(1, c);
		}
	}

	if (!current_string.empty()) 
	{
		cout << current_string << "\t" << dictionary[current_string] << endl;
		output.push_back(dictionary[current_string]);
	}

	cout << "Output Codes are:";
	for (int i = 0; i < output.size(); i++) 
	{
		cout << " " << output[i];
	}
	cout << endl;

	return output;
}

void decoding(vector<int> op) 
{
	if (op.empty()) 
	{
		return;
	}

	map<int, string> dictionary;
	for (int i = 0; i < 256; i++) 
	{
		string ch(1, static_cast<char>(i));
		dictionary[i] = ch;
	}

	int code = 256;
	string s = dictionary[op[0]];
	string result = s;

	cout << "Decoding" << endl;

	for (size_t i = 1; i < op.size(); i++) 
	{
		int new_code = op[i];
		string str;

		if (dictionary.find(new_code) != dictionary.end()) 
		{
			str = dictionary[new_code];
		} 
		else 
		{
			str = s + str[0];
		}

		result += str;

		if (code < 4096) 
		{
			dictionary[code] = s + str[0];
			code++;
		}

		s = str;
	}

	cout << result << endl;
}


int main()
{
	vector<int> ss = encoding("WYS*WYGWYS*WYSWYSG");
	decoding(ss);
}

