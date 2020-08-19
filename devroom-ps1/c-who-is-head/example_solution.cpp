#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
	std::vector<Node*> Child;
	std::vector<std::string> ChildName;
	int Refered = 0;
};

int GetDepth(Node* node);

int main() {
	int p;
	std::cin >> p;

	std::unordered_map<std::string, Node*> nodes;
	for (int i = 0; i < p; ++i) {
		std::string name;
		int c;
		std::cin >> name >> c;

		Node* node = (nodes[name] = new Node);
		for (int j = 0; j < c; ++j) {
			std::cin >> name;
			node->ChildName.push_back(name);
		}
	}

	for (auto node : nodes) {
		for (const std::string& name : node.second->ChildName) {
			Node* const child = nodes[name];
			node.second->Child.push_back(child);
			++child->Refered;
		}
	}

	const auto head = std::find_if(nodes.begin(), nodes.end(), [](const auto& node) {
		return node.second->Refered == 0;
	});
	std::cout << head->first << '\n' << GetDepth(head->second);
}

int GetDepth(Node* node) {
	int max = 0;
	for (Node* c : node->Child) {
		int depth = GetDepth(c);
		if (depth > max) {
			max = depth;
		}
	}
	return max + 1;
}