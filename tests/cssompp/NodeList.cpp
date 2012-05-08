#include "NodeList.hpp"

#include "Node.hpp"
#include "NodeListImpl.hpp"

#include <utility>



namespace test {



NodeList::NodeList() :
  _impl(NULL)
{}



NodeList::NodeList(test::NodeListImpl *impl) :
  _impl(impl)
{
  _impl->acquire();
}



NodeList::NodeList(const test::NodeList &copy) :
  _impl(copy._impl)
{
  _impl->acquire();
}



NodeList::~NodeList() {
  _impl->release();
}



test::NodeList& NodeList::operator=(const test::NodeList &rhs) {
  test::NodeList(rhs).swap(*this);
  return *this;
}



bool NodeList::operator==(const test::NodeList &rhs) const {
  return _impl == rhs._impl;
}



void NodeList::swap(test::NodeList &rhs) {
  std::swap(_impl, rhs._impl);
}



test::NodeListImpl* NodeList::impl() const {
  return _impl;
}



bool NodeList::empty() const {
  return _impl->empty();
}



size_t NodeList::size() const {
  return _impl->size();
}



test::Node NodeList::operator[](size_t index) const {
  return test::Node((*_impl)[index]);
}



} // test
