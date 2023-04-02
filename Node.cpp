#include "Node.h"

Node::Node(Node* parent) {
	this->parent = parent;
	profit = weight = bound = maxProfit = position.level = position.direction = 0;
	wasItemAddedInNode = true;
};

bool Node::isPromising(int W, int numberOfItems) const {
	if ((weight >= W) || (bound <= maxProfit) || (position.level == numberOfItems - 1))
		return false;
	return true;
}