#ifndef TEST_NODE_LIST_DATA_HPP
#define TEST_NODE_LIST_DATA_HPP

#include <deque>

namespace test {



class NodeData;



} // test

namespace test {



class NodeListData {
  private:
    size_t _handles;
    std::deque<test::NodeData*> *_nodes;

    // no copy
    NodeListData(const test::NodeListData &copy);
    test::NodeListData& operator=(const test::NodeListData &rhs);

  public:
    NodeListData(std::deque<test::NodeData*> *nodes);

    void acquire();
    void release();

    size_t size() const;
    test::NodeData* operator[](size_t index) const;

};



} // test

#endif // TEST_NODE_LIST_DATA_HPP
