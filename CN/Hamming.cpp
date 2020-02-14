#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>

int calRedBits(const std::vector<bool>& data) {
	int i = 1;
	while (true) {
		if (pow(2, i) >= data.size() + i + 1) return i;
		i++;
	}
}

std::vector<bool> findBits(int count, std::vector<bool> data) {
	int i = 0;
	while (count != 0) {
		data.insert(data.begin() + pow(2, i) - 1, 0);
		count--; i++;
	}
	return data;
}

bool evenParity(const std::vector<bool>& ans) {
	int c = 0;
	for (bool i : ans) if (i == 1) c++;
	return (c % 2 == 0) ? true : false;
}

std::vector<bool> findParity(std::vector<bool> data, int count) {

	std::vector<bool> ans, par;
	int p = 0;

	while (p < count) {
		int start = pow(2, p) - 1;
		while (start < data.size()) {
			int step = 0;
			for (int i = start; i < data.size() && step < pow(2, p); i++) {
				ans.push_back(data.at(i));
				step++;
			}
			start += pow(2, p + 1);
		}
		
		// one round answer is found
		// find if even parity is satisfied.
		if (!evenParity(ans)) par.push_back(1);
		else par.push_back(0);
		
		ans.clear();
		p++;
	}
	return par;
}

std::vector<bool> emplaceBack(std::vector<bool> rBits, std::vector<bool> parity) {
	for (int i = 0; i < parity.size(); i++) rBits.at(pow(2, i) - 1) = parity.at(i);
	return rBits;
}

std::vector<bool> sender(std::vector<bool> data, int r) {
	
	// insert zeros in their respective positions
	std::vector<bool> rBits = findBits(r, data);

	// find correct parity bits
	std::vector<bool> parity = findParity(rBits, r);

	std::cout << "\n";
	for (int i = 0; i < r; i++)	std::cout << "P" << pow(2, i) << ": " << parity.at(i) << "\n";
	std::cout << "\n";

	// replace zeros with correct parity
	std::vector<bool> hammingCode = emplaceBack(rBits, parity);
	return hammingCode;
}

bool allZeros(const std::vector<bool>& v) {
	for (bool i : v) if (i != 0) return false;
	return true;
}

auto convertToDecimal(const std::vector<bool>& par) {
	auto integer = 0; int n = 0;

	for (auto i : par) {
		if (i == 1) integer += pow(2, n);
		n++;
	}
	std::cout << "\n Dec:" << integer;
	return integer;
}

void findAndCorrectError(std::vector<bool>& rec, const std::vector<bool>& par) {
	auto errorPos = convertToDecimal(par);

	std::cout << "\n Error found at position: " << errorPos;
	if (rec.at(errorPos - 1)) rec.at(errorPos - 1) = 0;
	else rec.at(errorPos - 1) = 1;

}

int main() {

	int choice;

	do {

		std::cout << "\n 1. Sender  2. Receiver  3. Exit \n";
		std::cin >> choice;
		std::vector<bool> data, hammingCode, received, par;
		
		switch (choice) {
		case 1:

			int size, r;
			std::cout << "\n Enter the length of data:";
			std::cin >> size;

			std::cout << "\n Enter data:";
			for (int i = 0; i < size; i++) {
				int temp;
				std::cin >> temp;
				data.push_back(temp);
			}

			// find the number of redundant bits to be added
			r = calRedBits(data);

			hammingCode = sender(data, r);

			std::cout << "\n Hamming Code Generated: ";
			for (bool i : hammingCode) std::cout << i << " ";

			break;
		case 2:

			std::cout << "\n Enter received data. Press -1 to stop insertion:\n";
			int val;
			while (std::cin >> val) {
				if (val == -1) break;
				received.push_back(val);
			}
			

			par = findParity(received, r);
			std::cout << par.size() << std::endl;


			if (allZeros(par)) std::cout << "\n Received data has no errors";
			else {
				std::cout << "\n Received data has error. ";
				findAndCorrectError(received, par);
				std::cout << "\n Corrected Data is:";
				for (bool i : received) std::cout << i << " ";
			}

			break;
		case 3:
			exit(0);
		default: std::cout << "\n Invalid option";
		}


	} while (choice != 3);

	_getch();
	return 0;
}
