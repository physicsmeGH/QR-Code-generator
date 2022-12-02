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

int gen_coordinate_qr_strings(
	int columns_of_qr, int rows_of_qr, double qr_distance, double qr_square_size, 
	double column_coord_start,  double row_coord_start, 
	std::vector<std::string>& out_strings,
	double row_coord_step = -1, int column_coord_step = -1

) {
	out_strings = std::vector<std::string>();
	if (column_coord_step < 0) {
		column_coord_step = qr_distance;
	}
	if (row_coord_step < 0) {
		row_coord_step = qr_distance;
	}

	for (int col = 0; col < columns_of_qr; col++) {
		for (int row = 0; row < rows_of_qr; row++) {
			int column_text = col * column_coord_step + column_coord_start;
			int row_text = row * row_coord_step + row_coord_start;
			std::string qr_text = "";
			qr_text.append(std::to_string(column_text));
			qr_text.append(",");
			qr_text.append(std::to_string(row_text));
			QrCode qr_code = QrCode::encodeText(qr_text.c_str(), QrCode::Ecc::MEDIUM);
			std::string qr_string_out = "";
			qr_string_out.append(std::to_string(column_text));
			qr_string_out.append(",");
			qr_string_out.append(std::to_string(row_text));
			qr_string_out.append(",");
			std::string qr_string;
			Modules_to_string(qr_code.getModules(), qr_string);
			qr_string_out.append(qr_string);
			qr_string_out.append("\n");
			out_strings.push_back(qr_string_out);
		}
	}
	return 0;
}


int main() {
	std::vector<std::string> out_strings;
	gen_coordinate_qr_strings(2, 4, 10, 0.08, 10, 10, out_strings);
	std::ofstream file = std::ofstream("D:\\Dev\\CAD\\qr_test.txt");
	file << "0.08, 21" << std::endl;
	for (int i = 0; i < out_strings.size(); i++) {
		file << out_strings[i];
	}
	file.close();
	return 0;
}

int test() {
	int mat_width = 11;
	int mat_height = 9;
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
	return 0;

}
