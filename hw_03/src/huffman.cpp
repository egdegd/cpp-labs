#include "huffman.h"

TreeNode::TreeNode(char ch_, int frequence_) {
    ch = ch_;
    frequence = frequence_;
    left = nullptr;
    right = nullptr;
}

TreeNode::TreeNode(const std::shared_ptr<TreeNode>& min1, const std::shared_ptr<TreeNode>& min2) {
    left =  min1;
    right = min2;
    frequence = min1->frequence + min2->frequence;
    ch = 0;
}

TreeNode::TreeNode(char ch_) {
    ch = ch_;
    frequence = 0;
    left = nullptr;
    right = nullptr;
}

void TreeNode::set_ch(char c) {
    ch = c;
}

char TreeNode::get_ch() {
    return ch;
}

int TreeNode::get_frequence() const {
    return  frequence;
}

std::shared_ptr<TreeNode> TreeNode::get_left() {
    return left;
}

std::shared_ptr<TreeNode> TreeNode::get_right() {
    return right;
}

bool HuffCompare::operator()(const std::shared_ptr<TreeNode>& l, const std::shared_ptr<TreeNode>& r) {
    return l->get_frequence() > r->get_frequence();
}

void HuffTree::init(std::map<char, int> &m) {std::map<char,int>::iterator i;
    for (i = m.begin(); i != m.end(); i++) {
        std::shared_ptr<TreeNode> parent = std::make_shared<TreeNode>(i->first, i->second);
        _tree.push(parent);
    }

}

void HuffTree::build() {
    if (_tree.empty()) {
        throw HuffException("tree is empty");
    }
    while (_tree.size() != 1) {
        std::shared_ptr<TreeNode> min1 = _tree.top();
        _tree.pop();
        std::shared_ptr<TreeNode> min2 = _tree.top();
        _tree.pop();

        std::shared_ptr<TreeNode> parent = std::make_shared<TreeNode>(min1, min2);
        _tree.push(parent);
    }
}

std::shared_ptr<TreeNode> HuffTree::root() {
    return _tree.top();
}