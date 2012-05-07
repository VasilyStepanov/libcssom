#include "NodeListData.hpp"

#include <assert.h>

namespace test {



NodeListData::NodeListData(std::deque<test::NodeData*> *nodes) :
  _handles(1),
  _nodes(nodes)
{}



void NodeListData::acquire() {
  if (this == NULL) return;

  ++_handles;
}



void NodeListData::release() {
  if (this == NULL) return;

  assert(_handles > 0);
  --_handles;
  if (_handles > 0) return;

  delete _nodes;
}



size_t NodeListData::size() const {
  return _nodes->size();
}



test::NodeData* NodeListData::operator[](size_t index) const {
  return (*_nodes)[index];
}



} // test
