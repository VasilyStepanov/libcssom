#include "NodeListData.hpp"

#include "NodeData.hpp"

#include <assert.h>

namespace test {



NodeListData::NodeListData(std::deque<test::NodeData*> *nodes) :
  _handles(1),
  _nodes(nodes)
{
  if (_nodes->size() > 1) {
    for (
      std::deque<test::NodeData*>::iterator lhs = _nodes->begin(),
        rhs = _nodes->begin() + 1;
      rhs != _nodes->end();
      ++lhs, ++rhs)
    {
      (**lhs).setNextSibling(*rhs);
      (**rhs).setPreviousSibling(*lhs);
    }
  }
}



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



bool NodeListData::empty() const {
  return _nodes->empty();
}



size_t NodeListData::size() const {
  return _nodes->size();
}



test::NodeData* NodeListData::operator[](size_t index) const {
  return (*_nodes)[index];
}



} // test
