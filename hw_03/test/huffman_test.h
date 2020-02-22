#ifndef HW_03_HUFFMAN_TEST_H
#define HW_03_HUFFMAN_TEST_H

#include "autotest.h"

class huffman_test: public autotest {
    void testTreeNode1();
    void testTreeNode2();
    void testTreeNode_get_ch();
    void testTreeNode_get_frequence();
    void testTreeNode_get_left();
    void testTreeNode_get_right();
    void testHuffTree_init();
    void testHuffTree_build();
    void testHuffTree_root();
    void testReadTable();
    void testPrintTable();
    void testCreateTable();
    void testBuildTable();
    void testArchiving_Unzipping();
    void testArchiving_Unzipping_empty();
    void testArchiving_Unzipping2();
    void testArchiving_Unzipping3();
    void testArchiving_Unzipping4();

public:
    void runAllTests() override;
};


#endif //HW_03_HUFFMAN_TEST_H
