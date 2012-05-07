#ifndef TEST_NODE_DATA_HPP
#define TEST_NODE_DATA_HPP

#include <string>
#include <map>

namespace test {



class NodeListData;



} // test

namespace test {



class NodeData {
  private:
    size_t _handles;
    std::string _name;
    std::string _content;
    std::map<std::string, std::string> _attributes;
    test::NodeListData *_children;

    // no copy
    NodeData(const test::NodeData &copy);
    test::NodeData& operator=(const test::NodeData &rhs);

  public:
    NodeData(const std::string &name, const std::string &content,
      const std::map<std::string, std::string> &attributes,
      test::NodeListData *children);

    std::string str() const;

    void acquire();
    void release();

    const std::string& name() const;
    const std::string& content() const;
    const std::string& getAttribute(const std::string &name) const;
    test::NodeListData* children() const;
};



} // test

#endif // TEST_NODE_DATA_HPP
