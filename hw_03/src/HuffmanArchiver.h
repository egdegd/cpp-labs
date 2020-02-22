#ifndef HW_03_HUFFMANARCHIVER_H
#define HW_03_HUFFMANARCHIVER_H

#include "huffman.h"

class HuffmanArchiver {
public:
    HuffmanArchiver(const char* infile, const char* outfile);
    HuffmanArchiver() = default;
    explicit HuffmanArchiver(std::map<char, int> &m);
    void encode();
    void printtable(std::ofstream &outfile);
    void readtable(std::ifstream &infile);
    void decode(const std::shared_ptr<TreeNode>& root, std::ifstream &infile, std::ofstream &outfile);
    void createtable();
    void buildtable(std::shared_ptr<TreeNode> root, std::vector<bool> &code);
    void archiving();
    void unzipping();
    void get_stat();
    std::map<char, int> get_map();
    std::map<char,std::vector<bool>> get_table();

private:
    const char* infile{};
    const char* outfile{};
    std::map<char, int> map;
    std::map<char,std::vector<bool>> table;
    int size_infile = 0;
    int size_outfile = 0;
    int size_table = 0;
};


#endif