#ifndef GRIDTREE_NODE_H
#define GRIDTREE_NODE_H

#include<cassert>
#include<vector>
#include<cmath>
#include"Grid_Tree_Base.h"
#include"../Block_2D.h"


namespace knoblauch {

 class Grid_Tree_Node_SingleBlock : public Grid_Tree_Base {

 public:
   virtual Grid_Tree_Base* refine_in_I();
   virtual Grid_Tree_Base* refine_in_J();
   virtual Grid_Tree_Base* refine_in_I_and_J();
 protected:
   std::shared_ptr<Block2D> block;
 };

 Grid_Tree_Node_SingleBlock
 }

#endif
