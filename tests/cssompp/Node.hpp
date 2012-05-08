#ifndef TEST_NODE_HPP
#define TEST_NODE_HPP

#include <string>
#include <deque>

namespace test {



class NodeImpl;

class NodeList;



} // test

namespace test {



class Node {
  public:
    typedef test::NodeImpl Impl;

  private:
    test::Node::Impl *_impl;

  public:
    static test::Node parse(const std::string &html);

    Node();
    explicit Node(test::Node::Impl *impl);
    Node(const test::Node &copy);
    ~Node();
    test::Node& operator=(const test::Node &rhs);
    bool operator==(const test::Node &rhs) const;
    std::string str() const;
    void swap(test::Node &rhs);
    bool isNull() const;
    test::Node::Impl* impl() const;

    const std::string& name() const;
    const std::string& getAttribute(const std::string &name) const;
    test::NodeList children() const;
    test::Node previousSibling() const;
    test::Node nextSibling() const;

};



} // test

#endif // TEST_NODE_HPP
