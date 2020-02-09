#pragma once
#include <vector>
class Node
{
	std::vector<std::vector<int>> matrix;
	std::vector<int> children;
	int vertex;
	int nodeId;
	int lowerBound;
	bool visited;
	int parentNode;
	int parentNodeId;


	int getMinWeight(std::vector<int> row);

public:
	Node(std::vector<std::vector<int>> matrix, int vertex, int nodeId, int parentNode, int parentNodeId);

	void setVisited(bool visited);
	bool getVisited();

	int getVertex();
	void setVertex(int vertex);
	int getParentNode();
	void setParentNode(int parentNode);
	int getParentNodeId();
	int getNodeId();
	void setNodeId(int nodeId);
	int getLowerBound();
	void setLowerBound(int lowerBound);
	void setMatrix(std::vector<std::vector<int>> matrix);
	std::vector<std::vector<int>> getMatrix();

	std::vector<int> getChildren();
	void setChildren(std::vector<int> children);

	void firstReduction();
	void reduceMatrix(int parentNodeCost);
};

