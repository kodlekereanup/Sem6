#include "pch.h"
#include <iostream>
#include <vector>
#include <conio.h>

enum  CODE { BIT_ERROR, LEN_ERROR };
CODE C;

bool allZeros(const std::vector<bool>& ans) {
	for (bool i : ans) if (i != 0) return false;
	return true;
}

std::vector<bool> performXOR(const std::vector<bool>& l, const std::vector<bool>& r) {
	std::vector<bool> ans(r.size());
	for (int i = 0; i < r.size(); i++) ans.at(i) = l.at(i) xor r.at(i);
	return ans;
}

std::vector<bool> sender(std::vector<bool> data, std::vector<bool> gen, int o) {

	std::vector<bool> ans(gen.size());
	int current = gen.size();

	for (int i = 0; i < gen.size(); i++) ans.at(i) = data.at(i);

	while (current < data.size()) {
		ans = performXOR(ans, gen); 

		// remove pre zeros
		while (!ans.empty() && ans.at(0) == 0) ans.erase(ans.begin());

		// append next n digits such that length of ans = length of gen
		int diff = gen.size() - ans.size();
		
		for (int i = 0; i < diff && current < data.size(); i++) {
			ans.push_back(data.at(current));
			current++;
		}

		// last condition
		if (current >= data.size() && ans.size() == gen.size()) ans = performXOR(ans, gen);
	} 
	
	// ans format
	if (ans.size() != gen.size()) ans.insert(ans.begin(), 0);
	 
	for (int i = ans.size() - (gen.size() - 1); i < ans.size(); i++)
		data.at(o + i) = ans.at(i);
	
	return data;
	// consider last gen.size() - 1 digits after xor, append current
}

bool receiver(std::vector<bool> code, std::vector<bool> gen, int o) {
	std::vector<bool> ans(gen.size());
	int current = gen.size();
	bool valid = false;

	if (code.size() < o) {
		C = LEN_ERROR;
		return false;
	}
	
	for (int i = 0; i < gen.size(); i++) ans.at(i) = code.at(i);

	while (current < code.size()) {
		ans = performXOR(ans, gen);

		// remove pre zeros
		while (!ans.empty() && ans.at(0) == 0) ans.erase(ans.begin()); 

		// append next n digits such that length of ans = length of gen
		int diff = gen.size() - ans.size();

		for (int i = 0; i < diff && current < code.size(); i++) {
			ans.push_back(code.at(current));
			current++;
		}

		// last condition
		if (current >= code.size() && ans.size() == gen.size()) ans = performXOR(ans, gen);

		if (current >= code.size() && allZeros(ans)) {
			valid = true;
			break;
		} else C = BIT_ERROR;
	}

	return valid;
	
}

int main() {

	int choice;
	int inLen, genLen;
	std::cout << "\n Enter length of input data:";
	std::cin >> inLen;
	std::cout << "\n Enter the length of generator:";
	std::cin >> genLen;

	std::vector<bool> data;
	std::vector<bool> gen;

	std::cout << "\n Enter data:";
	for (int i = 0; i < inLen; i++) {
		int temp;
		std::cin >> temp;
		data.push_back(temp);
	}

	std::cout << "\n Enter generator:";
	for (int i = 0; i < genLen; i++) {
		int temp;
		std::cin >> temp;
		gen.push_back(temp);

	}

	std::cout << "Data:";
	for (bool i : data) std::cout << i << " ";
	std::cout << "\n";

	std::cout << "Gen:";
	for (bool i : gen) std::cout << i << " ";
	std::cout << "\n";

	// append genLen - 1 zeros to data
	for (int i = 0; i < genLen - 1; i++) data.push_back(0);

	// sender function generates and returns the codeword
	std::vector<bool> code = sender(data, gen, inLen - 1);

	std::cout << "\n Generated Codeword is: ";
	for (bool i : code) std::cout << i << " ";

	//TODO: 
	// 1. Send code as is
	// 2. Random (Introduce a bit flip in any random position or change the length)

	std::vector<bool> re;
	int temp;
	std::cout << "\n Enter received data:";
	while(std::cin >> temp) re.push_back(temp);

	bool val = receiver(re, gen, code.size());

	if(val) std::cout << "No error in message";
	else {
		if (C == LEN_ERROR) std::cout << "Error, full message not received";
		else std::cout << "\n Error, one or more bit(s) flipped";
	}

	_getch();
	return 0;
}