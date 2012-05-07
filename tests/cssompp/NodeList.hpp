#ifndef TEST_NODE_LIST_HPP
#define TEST_NODE_LIST_HPP

#include <cstddef>

namespace test {



class Node;

class NodeListData;



} // test

namespace test {



class NodeList {
  private:
    test::NodeListData *_data;

  public:
    NodeList();
    explicit NodeList(test::NodeListData *data);
    NodeList(const test::NodeList &copy);
    ~NodeList();
    test::NodeList& operator=(const test::NodeList &rhs);
    bool operator==(const test::NodeList &rhs) const;
    void swap(test::NodeList &rhs);

    bool empty() const;
    size_t size() const;
    test::Node operator[](size_t index) const;
};



} // test

#endif // TEST_NODE_LIST_HPP
