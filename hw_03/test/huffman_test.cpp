#include "huffman_test.h"
#include "HuffmanArchiver.h"
#define DO_CHECK(EXPR) check(EXPR, __FUNCTION__, __FILE__, __LINE__)

void huffman_test::runAllTests() {
    testTreeNode1();
    testTreeNode2();
    testTreeNode_get_ch();
    testTreeNode_get_frequence();
    testTreeNode_get_left();
    testTreeNode_get_right();
    testHuffTree_init();
    testHuffTree_build();
    testHuffTree_root();
    testReadTable();
    testPrintTable();
    testCreateTable();
    testBuildTable();
    testArchiving_Unzipping();
    testArchiving_Unzipping_empty();
    testArchiving_Unzipping2();
    testArchiving_Unzipping3();
    testArchiving_Unzipping4();
}

void huffman_test::testTreeNode1() {
    char ch = 'a';
    int frequence = 10;
    TreeNode node1(ch, frequence);
    TreeNode node2(ch, 2*frequence);
    DO_CHECK(node1.get_frequence() == frequence);
    DO_CHECK(node1.get_ch() == ch);
    DO_CHECK(node1.get_right() == nullptr);
}

void huffman_test::testTreeNode2() {
    char ch = 'a';
    int frequence = 10;
    auto node1 = std::make_shared<TreeNode>(ch, frequence);
    auto node2 = std::make_shared<TreeNode>(ch, 2*frequence);
    TreeNode new_node(node1, node2);
    DO_CHECK(new_node.get_left() == node1);
    DO_CHECK(new_node.get_frequence() == 3*frequence);
}

void huffman_test::testTreeNode_get_ch() {
    char ch = '1';
    int frequence = 1;
    TreeNode node(ch, frequence);
    DO_CHECK(node.get_ch() == '1');
}

void huffman_test::testTreeNode_get_frequence() {
    char ch = '1';
    int frequence = 1;
    TreeNode node(ch, frequence);
    DO_CHECK(node.get_frequence() == 1);
}

void huffman_test::testTreeNode_get_left() {
    char ch = '2';
    int frequence = 22;
    auto node1 = std::make_shared<TreeNode>(ch, frequence);
    auto node2 = std::make_shared<TreeNode>(ch, 2*frequence);
    TreeNode new_node(node1, node2);
    DO_CHECK(new_node.get_left() == node1);
}

void huffman_test::testTreeNode_get_right() {
    char ch = '2';
    int frequence = 22;
    auto node1 = std::make_shared<TreeNode>(ch, frequence);
    auto node2 = std::make_shared<TreeNode>(ch, 2*frequence);
    TreeNode new_node(node1, node2);
    DO_CHECK(new_node.get_right() == node2);
}

void huffman_test::testHuffTree_init() {
    std::map< char, int > m;
    m['s'] = 3;
    m['p'] = 6;
    m['b'] = 7;
    HuffTree tree;
    tree.init(m);
    DO_CHECK(tree.root()->get_ch() == 's');
}

void huffman_test::testHuffTree_build() {
    std::map< char, int > m;
    m['s'] = 3;
    m['p'] = 6;
    m['b'] = 6;
    HuffTree tree;
    tree.init(m);
    tree.build();
    DO_CHECK(tree.root()->get_frequence() == 15);
}

void huffman_test::testHuffTree_root() {
    std::map< char, int > m;
    m['a'] = 123;
    HuffTree tree;
    tree.init(m);
    DO_CHECK(tree.root()->get_ch() == 'a');
    DO_CHECK(tree.root()->get_frequence() == 123);
}

void huffman_test::testReadTable() {

    char tmpname[256];
    strcpy(tmpname, "/tmp/Myfile");
    mkstemp(tmpname);

    std::ofstream outfile(tmpname);
    std::map<char, int> m;
    m['a'] = 3;
    m['b'] = 7;
    m['c'] = 9;
    int size = m.size();
    outfile.write((char*)&size, sizeof(int));
    std::map<char, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
        outfile.write((char*)&it->first, sizeof(char));
        outfile.write((char*)&it->second, sizeof(int));
    }
    outfile.close();

    std::ifstream infile(tmpname);
    HuffmanArchiver archiver;
    archiver.readtable(infile);
    infile.close();
    DO_CHECK(archiver.get_map().size() == 3);
    DO_CHECK(archiver.get_map() == m);
}

void huffman_test::testPrintTable() {

    char tmpname[256];
    strcpy(tmpname, "/tmp/Myfile");
    mkstemp(tmpname);

    std::map<char, int> m;
    m['a'] = 3;
    m['b'] = 7;
    m['c'] = 9;
    HuffmanArchiver archiver(m);

    std::ofstream outfile(tmpname);

    archiver.printtable(outfile);
    outfile.close();
    std::ifstream infile(tmpname);
    std::map<char, int> new_m;
    int size_table = 0;
    infile.read((char*)&size_table, sizeof(int));
    for (int i = 0; i < size_table; i++) {
        char c;
        infile.read((char*)&c, sizeof(char));
        int frequence;
        infile.read((char*)&frequence, sizeof(int));
        new_m[c] = frequence;
    }
    infile.close();
    DO_CHECK(new_m == m);
}

void huffman_test::testCreateTable() {
    char tmpname[256];
    strcpy(tmpname, "/tmp/Myfile");
    mkstemp(tmpname);
    std::ofstream outfile(tmpname);
    outfile << "abcabcabccccb";
    outfile.close();
    HuffmanArchiver archiver(tmpname, tmpname);
    archiver.createtable();
    DO_CHECK(archiver.get_map().size() == 3);
    DO_CHECK(archiver.get_map()['a'] == 3);
    DO_CHECK(archiver.get_map()['b'] == 4);
    DO_CHECK(archiver.get_map()['c'] == 6);

}

void huffman_test::testBuildTable() {
    std::map<char, int> m;
    m['a'] = 3;
    m['b'] = 7;
    m['c'] = 9;
    m[' '] = 123;
    HuffTree tree;
    tree.init(m);
    tree.build();
    std::shared_ptr<TreeNode> root = tree.root();
    HuffmanArchiver archiver;
    std::vector<bool> code;
    archiver.buildtable(root, code);
    DO_CHECK(archiver.get_table().size() == 4);
    std::vector<bool> code1 = {0, 1, 0};
    std::vector<bool> code2 = {0, 1, 1};
    std::vector<bool> code3 = {0, 0};
    std::vector<bool> code4 = {1};
    DO_CHECK(archiver.get_table()['a'] == code1);
    DO_CHECK(archiver.get_table()['b'] == code2);
    DO_CHECK(archiver.get_table()['c'] == code3);
    DO_CHECK(archiver.get_table()[' '] == code4);
}

void huffman_test::testArchiving_Unzipping() {
    char tmpname1[256];
    strcpy(tmpname1, "/tmp/Myfile.txt");
    mkstemp(tmpname1);
    std::ofstream outfile(tmpname1);
    char buf[] = "ta";
    outfile.write((char *)&buf, sizeof(char) * 2);
    outfile.close();

    char tmpname2[256];
    strcpy(tmpname2, "/tmp/result.bin");
    mkstemp(tmpname2);

    HuffmanArchiver archiver(tmpname1, tmpname2);
    archiver.archiving();

    char tmpname3[256];
    strcpy(tmpname3, "/tmp/Myfile_new.txt");
    mkstemp(tmpname3);

    HuffmanArchiver archiver2(tmpname2, tmpname3);
    archiver2.unzipping();
    std::ifstream infile_new(tmpname3);
    char text[256];
    char c;
    infile_new >> text;
    DO_CHECK(text[0] == 't');
    DO_CHECK(text[1] == 'a');
    infile_new.close();
}

void huffman_test::testArchiving_Unzipping_empty() {
    char tmpname1[256];
    strcpy(tmpname1, "/tmp/Myfile.txt");
    mkstemp(tmpname1);
    std::ofstream outfile(tmpname1);
    outfile.close();

    char tmpname2[256];
    strcpy(tmpname2, "/tmp/result.bin");
    mkstemp(tmpname2);

    HuffmanArchiver archiver(tmpname1, tmpname2);
    archiver.archiving();

    char tmpname3[256];
    strcpy(tmpname3, "/tmp/Myfile_new.txt");
    mkstemp(tmpname3);

    HuffmanArchiver archiver2(tmpname2, tmpname3);
    archiver2.unzipping();
    std::ifstream infile_new(tmpname3);
    char c;
    infile_new.read((char *)&c, sizeof(char));
    DO_CHECK(infile_new.eof());
    infile_new.close();
}

void huffman_test::testArchiving_Unzipping2() {
    char tmpname1[256];
    strcpy(tmpname1, "/tmp/Myfile.txt");
    mkstemp(tmpname1);
    std::ofstream outfile(tmpname1);
    char buf[] = "aaaaaaa";
    outfile.write((char *)&buf, sizeof(char) * 7);
    outfile.close();

    char tmpname2[256];
    strcpy(tmpname2, "/tmp/result.bin");
    mkstemp(tmpname2);

    HuffmanArchiver archiver(tmpname1, tmpname2);
    archiver.archiving();

    char tmpname3[256];
    strcpy(tmpname3, "/tmp/Myfile_new.txt");
    mkstemp(tmpname3);

    HuffmanArchiver archiver2(tmpname2, tmpname3);
    archiver2.unzipping();
    std::ifstream infile_new(tmpname3);
    char text[256];
    infile_new >> text;
    for (int i = 0; i < 7; i++) {
        DO_CHECK(text[i] == 'a');
    }
    infile_new.close();
}

void huffman_test::testArchiving_Unzipping3() {
    char tmpname1[256];
    strcpy(tmpname1, "/tmp/Myfile.txt");
    mkstemp(tmpname1);
    std::ofstream outfile(tmpname1);
    char buf[] = "abcdefghij";
    outfile.write((char *)&buf, sizeof(char) * 10);
    outfile.close();

    char tmpname2[256];
    strcpy(tmpname2, "/tmp/result.bin");
    mkstemp(tmpname2);

    HuffmanArchiver archiver(tmpname1, tmpname2);
    archiver.archiving();

    char tmpname3[256];
    strcpy(tmpname3, "/tmp/Myfile_new.txt");
    mkstemp(tmpname3);

    HuffmanArchiver archiver2(tmpname2, tmpname3);
    archiver2.unzipping();
    std::ifstream infile_new(tmpname3);
    char text[256];
    infile_new >> text;
    for (int i = 0; i < 10; i++) {
        DO_CHECK(buf[i] == text[i]);
    }
    infile_new.close();
}

void huffman_test::testArchiving_Unzipping4() {
    char tmpname1[256];
    strcpy(tmpname1, "/tmp/Myfile.txt");
    mkstemp(tmpname1);
    std::ofstream outfile(tmpname1);
    char buf[] = "Iamtired";
    outfile.write((char *)&buf, sizeof(char) * 8);
    outfile.close();

    char tmpname2[256];
    strcpy(tmpname2, "/tmp/result.bin");
    mkstemp(tmpname2);

    HuffmanArchiver archiver(tmpname1, tmpname2);
    archiver.archiving();

    char tmpname3[256];
    strcpy(tmpname3, "/tmp/Myfile_new.txt");
    mkstemp(tmpname3);

    HuffmanArchiver archiver2(tmpname2, tmpname3);
    archiver2.unzipping();
    std::ifstream infile_new(tmpname3);
    char text[256];
    infile_new >> text;
    for (int i = 0; i < 8; i++) {
        DO_CHECK(buf[i] == text[i]);
    }
    infile_new.close();
}