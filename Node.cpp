#include "Node.h"

int Node::getMinWeight(std::vector<int> row)
{
	int k = INT_MAX;
	int index;
	for (int i = 0; i < row.size(); i++) {
		if (row[i] < k && row[i] >= 0) {
			k = row[i];
			index = i;
		}
	}
	return index;
}

Node::Node(std::vector<std::vector<int>> matrix, int vertex, int nodeId, int parentNode, int parentNodeId)
{
	this->matrix = matrix;
	this->vertex = vertex;
	this->nodeId = nodeId;
	this->parentNode = parentNode;
	this->visited = false;
	this->parentNodeId = parentNodeId;
}

void Node::setVisited(bool visited)
{
	this->visited = visited;
}

bool Node::getVisited()
{
	return visited;
}

int Node::getVertex()
{
	return vertex;
}

void Node::setVertex(int vertex)
{
	this->vertex = vertex;
}

int Node::getParentNode()
{
	return parentNode;
}

void Node::setParentNode(int parentNode)
{
	this->parentNode = parentNode;
}

int Node::getParentNodeId()
{
	return parentNodeId;
}

int Node::getNodeId()
{
	return nodeId;
}

void Node::setNodeId(int nodeId)
{
	this->nodeId = nodeId;
}

int Node::getLowerBound()
{
	return lowerBound;
}

void Node::setLowerBound(int lowerBound)
{
	this->lowerBound = lowerBound;
}

void Node::setMatrix(std::vector<std::vector<int>> matrix)
{
	this->matrix = matrix;
}

std::vector<std::vector<int>> Node::getMatrix()
{
	return matrix;
}

std::vector<int> Node::getChildren()
{
	return children;
}

void Node::setChildren(std::vector<int> children)
{
	this->children = children;
}

void Node::firstReduction()
{
	int totalCost = 0;
	for (int i = 0; i < matrix.size(); i++) {
		int reducingValue = matrix[i][getMinWeight(matrix[i])];
		totalCost += reducingValue;

		for (int j = 0; j < matrix.size(); j++) {
			if (matrix[i][j] > 0)
				matrix[i][j] -= reducingValue;
		}
	}

	for (int j = 0; j < matrix.size(); j++) {
		std::vector<int> column;
		for (int i = 0; i < matrix.size(); i++)
			column.push_back(matrix[i][j]);

		int reducingValue = matrix[getMinWeight(column)][j];
		totalCost += reducingValue;

		for (int i = 0; i < matrix.size(); i++) {
			if (matrix[i][j] > 0)
				matrix[i][j] -= reducingValue;
		}
	}

	this->lowerBound = totalCost;
	this->vertex = 0;
	this->nodeId = 0;
	this->visited = true;
}

void Node::reduceMatrix(int parentNodeCost)
{
	int totalCost = 0;
	totalCost += matrix[parentNode][vertex];
	totalCost += parentNodeCost;

	for (int i = 0; i < matrix.size(); i++) {
		matrix[parentNode][i] = -1;
		matrix[i][vertex] = -1;
	}
	matrix[vertex][0] = -1;

	for (int i = 0; i < matrix.size(); i++) {
		bool hasZero = false;
		int infCount = 0;
		for (int j = 0; j < matrix.size(); j++) {
			if (matrix[i][j] == 0)
				hasZero = true;
			if (matrix[i][j] == -1)
				infCount++;
		}

		if (!hasZero && infCount < matrix.size()) {
			int reducingValue = matrix[i][getMinWeight(matrix[i])];
			totalCost += reducingValue;

			for (int j = 0; j < matrix.size(); j++) {
				if (matrix[i][j] > 0)
					matrix[i][j] -= reducingValue;
			}
		}
	}

	for (int j = 0; j < matrix.size(); j++) {
		bool hasZero = false;
		int infCount = 0;
		std::vector<int> column;
		for (int i = 0; i < matrix.size(); i++) {
			column.push_back(matrix[i][j]);
			if (matrix[i][j] == 0)
				hasZero = true;
			if (matrix[i][j] == -1)
				infCount++;
		}

		if (!hasZero && infCount < matrix.size()) {
			int reducingValue = matrix[getMinWeight(column)][j];
			totalCost += reducingValue;

			for (int i = 0; i < matrix.size(); i++) {
				if (matrix[i][j] > 0)
					matrix[i][j] -= reducingValue;
			}
		}
	}

	this->lowerBound = totalCost;
	//this->visited = true;
}
