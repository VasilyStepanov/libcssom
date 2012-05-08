#include "NodeListImpl.hpp"

#include "NodeImpl.hpp"

#include <assert.h>

namespace test {



NodeListImpl::NodeListImpl(std::deque<test::NodeImpl*> *nodes) :
  _handles(1),
  _nodes(nodes)
{
  if (_nodes->size() > 1) {
    for (
      std::deque<test::NodeImpl*>::iterator lhs = _nodes->begin(),
        rhs = _nodes->begin() + 1;
      rhs != _nodes->end();
      ++lhs, ++rhs)
    {
      (**lhs).setNextSibling(*rhs);
      (**rhs).setPreviousSibling(*lhs);
    }
  }
}



void NodeListImpl::acquire() {
  if (this == NULL) return;

  ++_handles;
}



void NodeListImpl::release() {
  if (this == NULL) return;

  assert(_handles > 0);
  --_handles;
  if (_handles > 0) return;

  delete _nodes;
}



bool NodeListImpl::empty() const {
  return _nodes->empty();
}



size_t NodeListImpl::size() const {
  return _nodes->size();
}



test::NodeImpl* NodeListImpl::operator[](size_t index) const {
  return (*_nodes)[index];
}



} // test
