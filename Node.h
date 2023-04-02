#pragma once
#include <vector>

/**
* This structure specifies position of the node in the tree. "level" is the x position and "direction" is the y position.
*/
struct NodePositionInTree {
	int level;
	int direction;
};

/**
* This class defines node of the tree. It contanins values specific to it and methods to manage them.
*/
class Node {
private:
	//pointer to the parent node
	Node* parent;
	//std::vector container which contains all children of node (if they are present)
	std::vector<Node*> children;

	//values which are specific to node
	int profit, weight, bound, maxProfit;

	//posiotion of the node in tree
	NodePositionInTree position;
	//specifies if item from backpack was added when node was constructed
	bool wasItemAddedInNode;
public:
	/**
	* Constructor of the class "Node". It constructs node with given parent and all other values equal to zero except "wasItemAddedInNode".
	* @param parent - pointer to parent of node which we are creating
	*/
	Node(Node* parent);

	/**
	* Returns pointer to parent of node.
	* @return pointer of type Node* which contains memory address of node's parent.
	*/
	Node* getParent() const { return parent; };
	/**
	* Adds child to node.
	* @param child - pointer to node which we want to add as a child
	*/
	void addChild(Node* child) { children.push_back(child); };
	/**
	* Returns all children of node.
	* @return std::vector with pointers to node's children.
	*/
	std::vector<Node*> getChildren() { return children; }
	/**
	* Returns the number of children which has node.
	* @return integer value which represents number of children.
	*/
	int getNumberOfChildren() const { return children.size(); }

	/**
	* Returns profit stored in node.
	* @return integer value which represents profit stored in node.
	*/
	int getProfit() const { return profit; };
	/**
	* Changes the profit value.
	* @param profit - profit value which we want to set.
	*/
	void setProfit(int profit) { this->profit = profit; };

	/**
	* Returns weight stored in node.
	* @return integer value which represents weight stored in node.
	*/
	int getWeight() const { return weight; };
	/**
	* Changes the weight value.
	* @param weight - weight value which we want to set.
	*/
	void setWeight(int weight) { this->weight = weight; };

	/**
	* Returns bound stored in node.
	* @return integer value which represents bound stored in node.
	*/
	int getBound() const { return bound; }
	/**
	* Changes the bound value.
	* @param weight - bound value which we want to set.
	*/
	void setBound(int bound) { this->bound = bound; }

	/**
	* Returns max profit stored in node.
	* @return integer value which represents max profit stored in node.
	*/
	int getMaxProfit() const { return maxProfit; }
	/**
	* Changes max profit stored in node.
	* @param maxProfit - new max profit value.
	*/
	void setMaxProfit(int maxProfit) { this->maxProfit = maxProfit; }

	/**
	* Returns level on which is node in the tree.
	* @return integer value which represents level.
	*/
	int getLevel() const { return position.level; };
	/**
	* Returns direction on which is node in the tree.
	* @return integer value which represents direction.
	*/
	int getDirection() const { return position.direction; };
	/**
	* Returns "NodePositionInTree" structure which contains level and direction of node in the tree.
	* @return "NodePositionInTree" structure of node.
	*/
	NodePositionInTree getPosition() const { return position; };
	/**
	* Sets position values in "NodePositionInTree" structure.
	* @param level - new level value
	* @param direction - new direction value
	*/
	void setPosition(int level, int direction) { position.level = level; position.direction = direction; };

	/**
	* Changes if node is promising. Conditions when it is promising or not are in function's code.
	* @param W - maximum weight of items which can be stored in backpack.
	*/
	bool isPromising(int W, int numberOfItems) const;

	/**
	* Sets the "wasItemAddedInNode" variable.
	* @param added - new "wasItemAddedInNode" value.
	*/
	void itemAddedInNode(bool added) { wasItemAddedInNode = added; }
	/**
	* Returns the value of "wasItemAddedInNode" variable.
	* @return boolean value of "wasItemAddedInNode" variable.
	*/
	bool CheckIfItemWasAddedInNode() const { return wasItemAddedInNode; };
};
