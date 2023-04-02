#include <iostream>
#include "LibFiles.h"
#include "StateSpaceTree.h"
#include "Exceptions.h"

int main() {
	try {
		int W;
		std::fstream inputFile, outputFile;
		std::string inputFileName, outputFileName;

		std::cout << "Input file name: ";
		std::cin >> inputFileName;
		openFile(inputFile, inputFileName);

		std::cout << "Output file name: ";
		std::cin >> outputFileName;
		openFile(outputFile, outputFileName);

		std::vector<std::pair<int, int>> backpack;
		std::vector<double> pricesToWeightsRatios;

		inputFile >> W;

		int price, weight, ratio;
		while (inputFile >> price >> weight >> ratio) {
			if (price < 0 || weight < 0 || ratio < 0)
				throw Exceptions::InvalidInputValueException();

			backpack.push_back(std::make_pair(price, weight));
			pricesToWeightsRatios.push_back(ratio);
		}

		Node* root = new Node(nullptr);
		StateSpaceTree tree(root, backpack, pricesToWeightsRatios, W, outputFile);
		tree.checkNode(root);
		outputFile << "Result is: (" << tree.getBestNode().level << ", " << tree.getBestNode().direction << ")" << std::endl;
		outputFile.close();
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}

	return 0;
}