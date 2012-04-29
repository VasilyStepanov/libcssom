#include "Errors.hpp"

namespace test {



int errorHandler(void *userData, const CSSOM_Error *error) {
  Errors *errors = static_cast<Errors*>(userData);

  switch (error->code) {
    case CSSOM_ERROR_NOT_SUPPORTED:
      break;
    case CSSOM_ERROR_SYNTAX:
      ++errors->syntaxErrors;
      break;
    case CSSOM_ERROR_INDEX_SIZE_ERR:
      ++errors->indexSizeErrors;
      break;
    case CSSOM_ERROR_INVALID_MODIFICATION_ERR:
      ++errors->invalidModificationErrors;
      break;
    case CSSOM_ERROR_HIERARCHY_REQUEST_ERR:
      ++errors->hierarchyRequestErrors;
      break;
  }

  return 0;
}



} // test
