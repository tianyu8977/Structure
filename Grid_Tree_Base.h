#ifndef GRIDTREE_H
#define GRIDTREE_H

#include<cassert>
#include<vector>
#include<cmath>
#include<exception>

namespace knoblauch {

  class Grid_Tree_Base {

    virtual Grid_Tree_Base* refine_in_I()=0;
    virtual Grid_Tree_Base* refine_in_J()=0;
    virtual Grid_Tree_Base* refine_in_I_and_J()=0;

  };

}

#endif
