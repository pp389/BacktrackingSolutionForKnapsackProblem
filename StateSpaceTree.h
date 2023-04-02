#pragma once

#include "Node.h"
#include <vector>
#include <fstream>

/**
* This class represents the state space tree and operations which are carried out on it.
*/
class StateSpaceTree {
private:
	//pointer to root of the tree
	Node* root;

	//pointer to node which we are currently using to carry out calculations.
	Node* currentNode;
	int best, W;

	//reference to std::vector container which contains all the prices and weights of items in the backpack.
	std::vector<std::pair<int, int>>& backpack;

	//reference to std::vector container which contains all the prices to weight ratios.
	std::vector<double>& pricesToWeightsRatios;

	//std::vector which is helpful in calculating current level in the tree.
	std::vector<int> level;

	//Object of "NodePositionInTree" structure which contains position of node in the tree which contains the result of solved proble.
	NodePositionInTree resultNode;

	//reference to std::fstrem object which handles file to which program output is saved.
	std::fstream& outputFile;

	/**
	* Visits new node.
	*/
	void addNode();
	/**
	* Finds the node on the "k" level. It's a node which will cause overrun of "W" value by sum of the weights.
	* @return integer value of the "k" level.
	*/
	int findKNode();
	/**
	* Returns total weight.
	* @param k - "k" level.
	* @return integer value of total weight.
	*/
	int totalWeight(int k);
	/**
	* Calculates profit.
	* @param k - "k" level.
	* @return integer value of calculated profit.
	*/
	int calculateProfit(int k);
	/**
	* Finds bound value.
	* @param k - "k" level.
	* @param totalWeight - total weight.
	* @return integer value of bound.
	*/
	int findBound(int k, int totalWeight);
	/**
	* Checks child of current node.
	*/
	void checkChild();
public:
	/**
	* Construtor of "StateSpaceTree" class.
	* @param root - pointer to root of the tree.
	* @param backpackVector - reference to std::vector which contains prices and weights of items in the backpack.
	* @param priceToWeightsRatiosVector - reference to std::vector container which contains all the prices to weight ratios.
	* @param W - maximum weight of all items in backpack.
	* @param outputFileHandle - refernce to std::fstream object which handles our output file.
	*/
	StateSpaceTree(Node* root, std::vector<std::pair<int, int>>& backpackVector, std::vector<double>& priceToWeightsRatiosVector, int  W, std::fstream& outputFileHandle);

	~StateSpaceTree() { outputFile.close(); };

	/**
	* Checks all the nodes in the tree starting from "node" value.
	* @param node - pointer to node from which the algorithm starts.
	*/
	void checkNode(Node* node);
	/**
	* Returns "NodePositionInTree" structure object which contains result position of the best node.
	* @return "NodePositionInTree" structure
	*/
	NodePositionInTree getBestNode() const { return resultNode; };
};
