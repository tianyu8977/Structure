#include<memory>
#include"Refine_Block2D_J.h"
#include"../Curve2D/Spline2D.h"


knoblauch::Block2D_Refined_J knoblauch:: Refine_Block2D_In_J(const Block_2D& block) {
 Block2D_Refined_J new_blocks;

  int num_nodes_i = block.get_number_of_nodes_i();
  int num_nodes_j = block.get_number_of_nodes_j();
  int number_of_nodes = num_nodes_i*num_nodes_j;
  int new_number_nodes = num_nodes_i*num_nodes_j+num_nodes_i*(num_nodes_j-1);
  int new_number_j_neg = 0;
  int new_number_j_pos = 0;
  int current_number = 0;
  float_type s = 0.0;

  std::vector<Vector2D> new_nodes_all(new_number_nodes);
  std::vector<Vector2D> new_nodes_j_pos(number_of_nodes);
  std::vector<Vector2D> new_nodes_j_neg(number_of_nodes);
  std::vector<Vector2D> boundary_nodes(num_nodes_i);

  for(int j=0; j<num_nodes_j; j++) {
    for(int i=0; i<num_nodes_i; i++) {
      new_nodes_all[current_number] = block.get_node(i,j);
      current_number++;
    }
    if(j<num_nodes_j-1) {
      for(int i=0; i<num_nodes_i-1; i++) {
	if(i==0) {
	  new_nodes_all[current_number] = block.get_edge_centre_negative_i(i,j);
	  current_number++;
	}
	new_nodes_all[current_number] = block.get_edge_centre_positive_i(i,j);
	current_number++;
      }
    }  // for i
  }  // for j
  ////////////////////////////////////  put all the new nodes in the right order

  std::shared_ptr<Curve2D_Base> boundary_i_neg = block.get_boundary_i_neg();
  std::shared_ptr<Curve2D_Base> boundary_i_pos = block.get_boundary_i_pos();

  for(int j=0; j<num_nodes_j-1; j++) {
    current_number = num_nodes_i*(2*j+1);
    s = boundary_i_neg->get_s_at_position(new_nodes_all[current_number]);
    new_nodes_all[current_number] = boundary_i_neg->get_position_at_s(s);
  }
  //////////////////////////////   move nodes at i_neg to the boundary

  for(int j=0; j<num_nodes_j-1; j++) {
    current_number = num_nodes_i*(2*j+1)+num_nodes_i-1;
    s = boundary_i_pos->get_s_at_position(new_nodes_all[current_number]);
    new_nodes_all[current_number] = boundary_i_pos->get_position_at_s(s);
  }
  //////////////////////////////   move nodes at i_pos to the boundary

  current_number = 0;
  for(int j=0; j<num_nodes_j; j++) {
    for(int i=0; i<num_nodes_i; i++) {
      new_nodes_j_neg[new_number_j_neg] = new_nodes_all[current_number];
      new_number_j_neg++;
      current_number++;
    }  // for i
  }  // for j
  //////////////////////////////////  refine j_neg

  current_number = number_of_nodes-num_nodes_i;
  for(int j=0; j<num_nodes_j; j++) {
    for(int i=0; i<num_nodes_i; i++) {
      new_nodes_j_pos[new_number_j_pos] = new_nodes_all[current_number];
      new_number_j_pos++;
      current_number++;
    }  // for i
  }  // for j
  ////////////////////////////////// refine j_pos

  for(int k=0; k<num_nodes_i; k++) {
    int boundary_number = num_nodes_i*(num_nodes_j-1)+k;
    boundary_nodes[k] = new_nodes_j_neg[boundary_number];
  }

  std::shared_ptr<Curve2D_Base> boundary_j_new( new Spline2D(boundary_nodes) );
  /////////////////////////////////////  build boundary j_new

  new_blocks.j_neg = std::unique_ptr<Block_2D>(new Block_2D(num_nodes_i,
							    num_nodes_j,
							    new_nodes_j_neg, 
							    block.get_boundary_i_pos(),
							    block.get_boundary_i_neg(),
							    boundary_j_new,
							    block.get_boundary_j_neg()
							    ));

  //////////////////////////////////////////////////////  done new block of j neg




  new_blocks.j_pos = std::unique_ptr<Block_2D>(new Block_2D(num_nodes_i,
							    num_nodes_j,
							    new_nodes_j_pos,
							    block.get_boundary_i_pos(),
							    block.get_boundary_i_neg(),
							    block.get_boundary_j_pos(),
							    boundary_j_new
							    ));
  //////////////////////////////////////////////////// done new block of j pos


  return std::move(new_blocks);

}
