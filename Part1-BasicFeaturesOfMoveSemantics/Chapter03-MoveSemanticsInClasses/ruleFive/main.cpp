#include "../../../util/print.h"

/*
 * Six operations as special member functions:
 * Default constructor
 * Copy constructor
 * Copy assignment operator
 * Move constructor(since C++11)
 * Move assignment operator(since C++11)
 * Destructor
 */

/*
 * There are few basic rules
 *
 * A default constructor is only declared automatically if no other constructor is user-declared(no copy/move constructor)
 *
 * The special copy member functions(copy/copy assignment) and the destructor disable move support, The automatic generation
 * of special move member functions is disabled(unless the moveing operation are also declared). However, still a request
 * to move an object usually works because the copy member functions are used a fallback(unless the special move member
 * are explicitly deleted)
 *
 *
 * The special move member functions disable the normal copying and assignment, The copying and other moving special member
 * functions are deleted so that you can only move(assign) but not copy(assign) an object(unless the other operations
 * are also declared)
 */

#include "default_cp_mv.h"
#include "declare_cp_disable_mv.h"
#include "declare_mv_dsiable_cp.h"
#include "delete_mv_no_sence.h"

int main()
{

    default_copy_move::execute();
    declare_copy_disable_move::execute();
    declare_move_disable_copy::execute();
    delete_move_make_no_sense::execute();
    return 0;
}
