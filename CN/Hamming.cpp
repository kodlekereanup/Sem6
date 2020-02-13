#include "pch.h"
#include <iostream>
#include <vector>
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

int main() {

	int size;
	std::cout << "\n Enter the length of data:";
	std::cin >> size;

	std::vector<bool> data;

	std::cout << "\n Enter data:";
	for (int i = 0; i < size; i++) {
		int temp;
		std::cin >> temp;
		data.push_back(temp);
	}

	// find the number of redundant bits to be added
	int r = calRedBits(data);

	// insert zeros in their respective positions
	std::vector<bool> rBits = findBits(r, data);

	// find correct parity bits
	std::vector<bool> hammingCode = findParity(rBits, r);

	std::cout << "\n";
	for (int i = 0; i < r; i++)
		std::cout << "P" << pow(2, i) << ": " << hammingCode.at(i) << "\n";
	std::cout << "\n";

	// replace zeros with correct parity


	_getch();
	return 0;
}
