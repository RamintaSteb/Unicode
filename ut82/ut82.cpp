// ut82.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>




using namespace std;

string DECtoBIN(int dec);
string BINtoUNI(string bin, int dec);
void conv(string bin, int &ilg, string &one);
string BINtoHEX(string uni);
int HEXtoDEC(string baitas);

int main()
{
	
	ifstream F("386intel.txt", ios::binary);
	ifstream Fv("Duomenys.txt");
	ofstream Fr("rezultatas.txt");
	string  Duom[128];
	int dec;
	string bin, uni, hex;
	int i = 0;
	int byte = 0;
	char ch[9];
	while (!Fv.eof())
	{
		Fv >> Duom[i];
		i++;
	}
	//i = 0;
	while (!F.eof())
	{
		F.seekg(i);
		F.read(reinterpret_cast<char*>(&byte), 1);
		if (byte<128) Fr << (char)byte;
		else if (byte>127)
		{
			byte = byte - 128;
			string baitas = Duom[byte];
			dec = HEXtoDEC(baitas); // pasivercia sesioliktaini is lenteles i desimtaini
			bin = DECtoBIN(dec); //Pasivercia turima desimtaini i dvejetaini
			uni = BINtoUNI(bin, dec); //Pasivercia dvejetaini i unikoda
			hex = BINtoHEX(uni); //Pavercia dvejetaini unikoda i desimtaini
			//cout << hex << endl;
			for (int i = 0; i < hex.length(); i += 2)
			{
				int b = 0;
				if (hex[i] >= '0' && hex[i] <= '9')
				{
					b += (hex[i] - '0') * 16;
				}
				else
				{
					b += (hex[i] - 'A' + 10) * 16;
				}
				if (hex[i + 1] >= '0' && hex[i + 1] <= '9')
				{
					b += (hex[i + 1] - '0');
				}
				else
				{
					b += (hex[i + 1] - 'A' + 10);
				}
				char ch = b;
				Fr << ch;
			}
		}
		i++;
	}
	F.close();
	Fr.close();
	Fv.close();

	system("PAUSE");

    return 0;
}

string DECtoBIN(int dec)
{
	string bin;
	for (int i = dec; i > 0; i = i / 2)
	{
		if (i % 2 == 0) bin += '0';
		else if (i % 2 == 1) bin += '1';
	}
	for (int j = 0; j < bin.length() / 2; j++)
		swap(bin[j], bin[bin.length() - j-1]);

	return bin;
}
string BINtoUNI(string bin, int dec)
{
	string uni;
	if (dec < 128)
	{
		uni = bin;
	}
	else if (dec < 2048)
	{
		int ilg = bin.length();
		string one, two;
		conv(bin, ilg, one);

		for (int i = 0; i < 5; i++)
		{
			if (ilg <= 0) two = two + '0';
			else
			{
				two = two + bin[ilg - 1];
				ilg--;
			}
		}
		two = two + "011";
		for (int j = 0; j < two.length() / 2; j++)
			swap(two[j], two[two.length() - j - 1]);

		uni = two + one;
	}
	else if (dec < 65536)
	{
		int ilg = bin.length();
		string one, two, three;
		conv(bin, ilg, one);
		conv(bin, ilg, two);
		one = two + one;

		for (int i = 0; i < 4; i++)
		{
			if (ilg <= 0) three = three + '0';
			else
			{
				three = three + bin[ilg - 1];
				ilg--;
			}
		}
		three = three + "0111";
		for (int j = 0; j < three.length() / 2; j++)
			swap(three[j], three[three.length() - j - 1]);

		uni = three + one;
	}
	else if (dec < 1114112)
	{
		int ilg = bin.length();
		string one, two, three, four;
		conv(bin, ilg, one);
		conv(bin, ilg, two);
		conv(bin, ilg, three);
		one = three + two + one;

		for (int i = 0; i < 3; i++)
		{
			if (ilg <= 0) four = four + '0';
			else
			{
				four = four + bin[ilg - 1];
				ilg--;
			}
		}
		four = four + "01111";
		for (int j = 0; j < four.length() / 2; j++)
			swap(four[j], four[four.length() - j - 1]);

		uni = four + one;
	}

	else cout << "Error" << endl;
	return uni;
}
void conv(string bin, int &ilg, string &one)
{
	for (int i = 0; i < 6; i++)
	{
		if (ilg <= 0) one = one + '0';
		else
		{
			one = one + bin[ilg - 1];
			ilg--;
		}
	}

	one = one + "01";
	for (int j = 0; j < one.length() / 2; j++)
		swap(one[j], one[one.length() - j - 1]);
}
string BINtoHEX(string uni)
{
	string naujas;
	string hex;
	int n = uni.length() / 4;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			naujas += uni[j + i*4];
		}
		
		if (naujas == "0000") hex += '0';
		else if (naujas == "0001") hex += '1';
		else if (naujas == "0010") hex += '2';
		else if (naujas == "0011") hex += '3';
		else if (naujas == "0100") hex += '4';
		else if (naujas == "0101") hex += '5';
		else if (naujas == "0110") hex += '6';
		else if (naujas == "0111") hex += '7';
		else if (naujas == "1000") hex += '8';
		else if (naujas == "1001") hex += '9';
		else if (naujas == "1010") hex += 'A';
		else if (naujas == "1011") hex += 'B';
		else if (naujas == "1100") hex += 'C';
		else if (naujas == "1101") hex += 'D';
		else if (naujas == "1110") hex += 'E';
		else if (naujas == "1111") hex += 'F';
		else cout << "Errror" << endl;
		naujas.clear();
	}
	return hex;
}
int HEXtoDEC(string baitas)
{
	int dec=0;
	for (int i = 0; i < 4; i++)
	{
		if (baitas[i] == '0') dec = dec + 0 * (int)pow(16, 3 - i);
		else if (baitas[i] == '1') dec = dec + 1 * (int)pow(16, 3 - i);
		else if (baitas[i] == '2') dec = dec + 2 * (int)pow(16, 3 - i);
		else if (baitas[i] == '3') dec = dec + 3 * (int)pow(16, 3 - i);
		else if (baitas[i] == '4') dec = dec + 4 * (int)pow(16, 3 - i);
		else if (baitas[i] == '5') dec = dec + 5 * (int)pow(16, 3 - i);
		else if (baitas[i] == '6') dec = dec + 6 * (int)pow(16, 3 - i);
		else if (baitas[i] == '7') dec = dec + 7 * (int)pow(16, 3 - i);
		else if (baitas[i] == '8') dec = dec + 8 * (int)pow(16, 3 - i);
		else if (baitas[i] == '9') dec = dec + 9 * (int)pow(16, 3 - i);
		else if (baitas[i] == 'A') dec = dec + 10 * (int)pow(16, 3 - i);
		else if (baitas[i] == 'B') dec = dec + 11 * (int)pow(16, 3 - i);
		else if (baitas[i] == 'C') dec = dec + 12 * (int)pow(16, 3 - i);
		else if (baitas[i] == 'D') dec = dec + 13 * (int)pow(16, 3 - i);
		else if (baitas[i] == 'E') dec = dec + 14 * (int)pow(16, 3 - i);
		else if (baitas[i] == 'F') dec = dec + 15 * (int)pow(16, 3 - i);
	}
	return dec;
}
