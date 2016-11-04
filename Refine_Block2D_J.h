#ifndef REFINE_BLOCK2D_J_H
#define REFINE_BLOCK2D_J_H

#include<cassert>
#include<vector>
#include<cmath>
#include"../Block_2D.h"

namespace knoblauch {

  struct Block2D_Refined_J {

    std::unique_ptr<Block_2D> j_pos;
    std::unique_ptr<Block_2D> j_neg;

  };

  Block2D_Refined_J Refine_Block2D_In_J(const Block_2D& block);

}

#endif 

