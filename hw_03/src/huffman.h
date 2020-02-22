#ifndef HW_03_HUFFMAN_H
#define HW_03_HUFFMAN_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <memory>

class TreeNode {
public:

    TreeNode(char ch_, int frequence_);

    TreeNode(const std::shared_ptr<TreeNode>& min1, const std::shared_ptr<TreeNode>& min2);
    explicit TreeNode(char ch_);

    void set_ch(char c);
    char get_ch();
    int get_frequence() const;
    std::shared_ptr<TreeNode> get_left();
    std::shared_ptr<TreeNode> get_right();

private:
    int frequence ;
    char ch;
    std::shared_ptr<TreeNode> left, right;
};


class HuffCompare {
public:
    bool operator() (const std::shared_ptr<TreeNode>& l, const std::shared_ptr<TreeNode>& r);
};


class HuffTree {
public:
    void init(std::map< char, int > &m);
    void build();
    std::shared_ptr<TreeNode> root();

private:
    std::priority_queue<std::shared_ptr<TreeNode>, std::vector<std::shared_ptr<TreeNode>>, HuffCompare> _tree;
};

class HuffException {
private:
    std::string message;
public:
    HuffException(const std::string& m) {
        message = m;
    }
    const std::string get() {
        return message;
    }
};

#endif
