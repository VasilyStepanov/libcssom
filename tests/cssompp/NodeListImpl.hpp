#ifndef TEST_NODE_LIST_IMPL_HPP
#define TEST_NODE_LIST_IMPL_HPP

#include <deque>

namespace test {



class NodeImpl;



} // test

namespace test {



class NodeListImpl {
  private:
    size_t _handles;
    std::deque<test::NodeImpl*> *_nodes;

    // no copy
    NodeListImpl(const test::NodeListImpl &copy);
    test::NodeListImpl& operator=(const test::NodeListImpl &rhs);

  public:
    NodeListImpl(std::deque<test::NodeImpl*> *nodes);

    void acquire();
    void release();

    bool empty() const;
    size_t size() const;
    test::NodeImpl* operator[](size_t index) const;

};



} // test

#endif // TEST_NODE_LIST_IMPL_HPP
