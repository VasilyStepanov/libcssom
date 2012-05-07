#include "NodeList.hpp"

#include "Node.hpp"
#include "NodeListData.hpp"

#include <utility>



namespace test {



NodeList::NodeList() :
  _data(NULL)
{}



NodeList::NodeList(test::NodeListData *data) :
  _data(data)
{
  _data->acquire();
}



NodeList::NodeList(const test::NodeList &copy) :
  _data(copy._data)
{
  _data->acquire();
}



NodeList::~NodeList() {
  _data->release();
}



test::NodeList& NodeList::operator=(const test::NodeList &rhs) {
  test::NodeList(rhs).swap(*this);
  return *this;
}



bool NodeList::operator==(const test::NodeList &rhs) const {
  return _data == rhs._data;
}



void NodeList::swap(test::NodeList &rhs) {
  std::swap(_data, rhs._data);
}



bool NodeList::empty() const {
  return _data->empty();
}



size_t NodeList::size() const {
  return _data->size();
}



test::Node NodeList::operator[](size_t index) const {
  return test::Node((*_data)[index]);
}



} // test
