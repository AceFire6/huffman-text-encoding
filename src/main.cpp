#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

#include "HuffmanNode.h"
#include "HuffmanTree.h"

using namespace std;

class CompareNode {
public:
    bool operator()(const MLLJET001::HuffmanNode& a, const MLLJET001::HuffmanNode& b) {
        return a < b;
    }
};

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        cout << "Too few arguments. Required: huffmanencode <input_file> <output_file>" << endl;
    }
    string inputFileName = argv[1];
    string outputFileName = argv[2];

    cout << inputFileName << "\t" << outputFileName << endl;

    unordered_map<char, int> charMap;
    ifstream inFile(inputFileName);
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            for (char character: line) {
                if (charMap.find(character) != charMap.end()) {
                    charMap.at(character) += 1;
                } else {
                    charMap.insert({character, 1});
                }
            }
        }
    }

    priority_queue<MLLJET001::HuffmanNode, vector<MLLJET001::HuffmanNode>, CompareNode> nodeQueue;
    for (auto pair: charMap) {
        nodeQueue.push(MLLJET001::HuffmanNode(pair.first, pair.second));
    }

    while (nodeQueue.size() > 1) {
//        cout << "LOOPING" << '\t' << nodeQueue.size() << endl;
        MLLJET001::HuffmanNode small1 = nodeQueue.top();
        nodeQueue.pop();
        MLLJET001::HuffmanNode small2 = nodeQueue.top();
        nodeQueue.pop();

        int totalFrequency = small1.getFrequency() + small2.getFrequency();

        MLLJET001::HuffmanNode * newParent = new MLLJET001::HuffmanNode('\0', totalFrequency);
        newParent->left = make_shared<MLLJET001::HuffmanNode>(small1);
        newParent->right = make_shared<MLLJET001::HuffmanNode>(small2);

        nodeQueue.push(*newParent);
    }

    MLLJET001::HuffmanTree huffmanTree(nodeQueue.top());

    huffmanTree.getCharMap();

    return 0;
}

