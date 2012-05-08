#ifndef TEST_NODE_IMPL_HPP
#define TEST_NODE_IMPL_HPP

#include <string>
#include <map>

namespace test {



class NodeListImpl;



} // test

namespace test {



class NodeImpl {
  private:
    size_t _handles;
    std::string _ns;
    std::string _name;
    std::string _content;
    std::map<std::string, std::string> _attributes;
    test::NodeListImpl *_children;
    test::NodeImpl *_previousSibling;
    test::NodeImpl *_nextSibling;

    // no copy
    NodeImpl(const test::NodeImpl &copy);
    test::NodeImpl& operator=(const test::NodeImpl &rhs);

  public:
    NodeImpl(const std::string &ns, const std::string &name,
      const std::string &content,
      const std::map<std::string, std::string> &attributes,
      test::NodeListImpl *children);

    std::string str() const;

    void acquire();
    void release();

    const std::string& ns() const;
    const std::string& name() const;
    const std::string& content() const;
    const std::string& getAttribute(const std::string &name) const;
    test::NodeListImpl* children() const;
    void setPreviousSibling(test::NodeImpl *sibling);
    test::NodeImpl* previousSibling() const;
    void setNextSibling(test::NodeImpl *sibling);
    test::NodeImpl* nextSibling() const;
};



} // test

#endif // TEST_NODE_IMPL_HPP
