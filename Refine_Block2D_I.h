#ifndef REFINE_BLOCK2D_I_H
#define REFINE_BLOCK2D_I_H

#include<cassert>
#include<vector>
#include<cmath>
#include"../Block_2D.h"

namespace knoblauch {

  struct Block2D_Refined_I {

    std::unique_ptr<Block_2D> i_pos;
    std::unique_ptr<Block_2D> i_neg;

  };

  Block2D_Refined_I Refine_Block2D_In_I(const Block_2D& block);

}

#endif 

