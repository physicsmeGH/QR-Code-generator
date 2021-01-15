#include <fstream>
#include <iostream>
#include "QrCode.hpp"
#include <vector>
#include <cstring>
#include <string>
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

void Modules_to_string(std::vector<std::vector<bool>> in, std::string& out) {
	out = "";
	for (int i = 0; i < in.size(); i++) {
		for (int j = 0; j < in.at(i).size(); j++) {
			if (in.at(i).at(j)) {
				//true is black
				out.append("0,");
			}
			else {
				//false id white
				out.append("255,");
			}
		}
	}
}

int main() {
	int mat_width = 4;
	int mat_height = 3;
	/*QrCode q = QrCode::encodeText("1", QrCode::Ecc::HIGH);
	std::cout << q.getSize();
	std::cin >> mat_width;*/
	int dist = 30;
	std::ofstream file = std::ofstream("C:\\Dev\\CVData\\image\\qr\\qr_test.txt");
	file << "1,21" << std::endl;
	for (int i = 0; i < mat_width; i++) {
		for (int j = 0; j < mat_height; j++) {
			std::string text = "row: ";
			text.append(std::to_string(j));
			text.append(" col: ");
			text.append(std::to_string(i));
			QrCode q_code = QrCode::encodeText(text.c_str(), QrCode::Ecc::MEDIUM);
			file << dist * i << "," << dist * j <<",";
			std::string qr_string;
			Modules_to_string(q_code.getModules(), qr_string);
			file << qr_string << std::endl;
		}
		
	}

}
