#include "StateSpaceTree.h"
#include <iostream>

StateSpaceTree::StateSpaceTree(Node* root, std::vector<std::pair<int, int>>& backpackVector, std::vector<double>& priceToWeightsRatiosVector, int  W, std::fstream& outputFileHandle)
	: backpack(backpackVector), pricesToWeightsRatios(priceToWeightsRatiosVector), outputFile(outputFileHandle)
{
	this->root = root; 
	currentNode = root;
	this->W = W; 
	level.push_back(0);
	resultNode.direction = resultNode.level = best = 0;
};

int StateSpaceTree::findKNode() {
	std::vector<int> tmpVector;
	Node* nodePointer = currentNode;

	while (nodePointer->getParent() != nullptr) {
		if (!nodePointer->CheckIfItemWasAddedInNode())
			tmpVector.push_back(nodePointer->getLevel() - 1);
		nodePointer = nodePointer->getParent();
	}

	int weight = 0, k = backpack.size() + 1;
	for (int i = 0; i < backpack.size(); i++) {
		bool isPresent = true;
		for (int value : tmpVector)
			if (value == i)
				isPresent = false;
		if (isPresent)
			weight += backpack[i].second;
		if (weight > W) {
			k = i + 1;
			break;
		}
	}
	return k;
}

int StateSpaceTree::totalWeight(int k) {
	int totalWeight = currentNode->getWeight();
	for (int i = currentNode->getLevel(); i < k - 1; i++)
		totalWeight += backpack[i].second;
	return totalWeight;
}

int StateSpaceTree::calculateProfit(int k) {
	int totalProfit = currentNode->getProfit();
	for (int i = currentNode->getLevel(); i< k - 1; i++)
		totalProfit += backpack[i].first;
	return totalProfit;
}

int StateSpaceTree::findBound(int k, int totalWeight) {
	double ratio;
	int sum = 0, profit = calculateProfit(k);

	if (k <= backpack.size())
		ratio = pricesToWeightsRatios[k - 1];
	else
		ratio = 0;

	return profit + sum + (W - totalWeight) * ratio;
}

void StateSpaceTree::checkChild() {
	Node* child = new Node(currentNode);
	child->setProfit(currentNode->getProfit());
	child->setWeight(currentNode->getWeight());
	currentNode->addChild(child);
	if (level.size() - 1 == currentNode->getLevel())
		level.push_back(1);
	else
		level[currentNode->getLevel() + 1]++;
	child->setPosition(currentNode->getLevel() + 1, level[currentNode->getDirection() + 1]);
	currentNode = child;
}

void StateSpaceTree::addNode() {
	outputFile << "Currently in node: (" << currentNode->getLevel() << ", " << currentNode->getDirection() << ")" << std::endl;
	if (currentNode->getDirection() % 2 == 0)
		currentNode->itemAddedInNode(true);
	else {
		currentNode->setProfit(currentNode->getProfit() + backpack[currentNode->getLevel() - 1].first);
		currentNode->setWeight(currentNode->getWeight() + backpack[currentNode->getLevel() - 1].second);
		currentNode->itemAddedInNode(false);
	}
	int k = findKNode();
	int totalW = totalWeight(k);
	currentNode->setBound(findBound(k, totalW));
	outputFile << "Bound: " << currentNode->getBound() << std::endl;
	
	if (currentNode->getWeight() < W)
		currentNode->setMaxProfit(currentNode->getProfit());

	if (best >= currentNode->getMaxProfit())
		currentNode->setMaxProfit(best);
	outputFile << "Maxprofit: " << currentNode->getMaxProfit() << std::endl;
}

void StateSpaceTree::checkNode(Node* node) {
	Node* nodePointer = currentNode;
	addNode();

	do {
		if (nodePointer->getMaxProfit() > best) {
			best = nodePointer->getMaxProfit();
			resultNode = currentNode->getPosition();
		}
		if (nodePointer->isPromising(W, backpack.size()) && nodePointer->getNumberOfChildren() != 2) {
			outputFile << "Profit: " << currentNode->getProfit() << std::endl
				<< "Weight: " << currentNode->getWeight() << std::endl << "Node is promising" << std::endl;

			checkChild();
			nodePointer = currentNode;
			addNode();
		}
		else {
			outputFile << "Node isn't promising. We're getting back to its parent" << std::endl;
			currentNode = currentNode->getParent();
			nodePointer = currentNode;
		} 
	} while (nodePointer->getParent() != nullptr);
}