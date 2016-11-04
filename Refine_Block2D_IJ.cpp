#include"Refine_Block2D_IJ.h"
#include"Refine_Block2D_IJ.h"
#include"../Curve2D/Spline2D.h"

knoblauch::Block2D_Refined_IJ knoblauch::Refine_Block2D_In_IJ(const Block_2D& block) {
  
  Block2D_Refined_IJ new_blocks;

  int num_nodes_i = block.get_number_of_nodes_i();
  int num_nodes_j = block.get_number_of_nodes_j();
  int number_of_nodes = num_nodes_i*num_nodes_j;
  int new_number_nodes = (2*num_nodes_i-1)*(2*num_nodes_j-1);
  int new_num_i = num_nodes_i*2-1;
  int new_num_j = num_nodes_j*2-1;
  int new_number_nn = 0;
  int new_number_np = 0;
  int new_number_pn = 0;
  int new_number_pp = 0;
  int current_number = 0;
  float_type s = 0.0;

  std::vector<Vector2D> new_nodes_all(new_number_nodes);
  std::vector<Vector2D> new_nodes_i_neg_j_neg(number_of_nodes);
  std::vector<Vector2D> new_nodes_i_neg_j_pos(number_of_nodes);
  std::vector<Vector2D> new_nodes_i_pos_j_neg(number_of_nodes);
  std::vector<Vector2D> new_nodes_i_pos_j_pos(number_of_nodes);
  std::vector<Vector2D> boundary_nodes_i(new_num_j);
  std::vector<Vector2D> boundary_nodes_j(new_num_i);

  for(int j=0; j<num_nodes_j; j++) {
    for(int i=0; i<num_nodes_i; i++) {
      new_nodes_all[current_number] = block.get_node(i,j);
      current_number++;
      if(i<num_nodes_i-1) {
	new_nodes_all[current_number] = block.get_edge_centre_negative_j(i,j);
	current_number++;
      }
    }  // for i
      if(j<num_nodes_j-1) {
	for(int k=0; k<num_nodes_i-1; k++) {
	  if(k==0) {
	    new_nodes_all[current_number] = block.get_edge_centre_negative_i(k,j);
	    current_number++;
	  }
	  new_nodes_all[current_number] = (block.get_edge_centre_negative_i(k,j)+block.get_edge_centre_positive_i(k,j))/2;
	  current_number++;
	  new_nodes_all[current_number] = block.get_edge_centre_positive_i(k,j);
	  current_number++;
	}  // for k
      }
  }  // for j
  /////////////////////////////////////////////////////  put all the new nodes in the right order 
  std::shared_ptr<Curve2D_Base> boundary_i_neg = block.get_boundary_i_neg();
  std::shared_ptr<Curve2D_Base> boundary_i_pos = block.get_boundary_i_pos();
  std::shared_ptr<Curve2D_Base> boundary_j_neg = block.get_boundary_j_neg();
  std::shared_ptr<Curve2D_Base> boundary_j_pos = block.get_boundary_j_pos();

    for(int i=0; i<num_nodes_i-1; i++) {
      current_number = 2*i+1;
      s = boundary_j_neg->get_s_at_position(new_nodes_all[current_number]);
      new_nodes_all[current_number] = boundary_j_neg->get_position_at_s(s);
    }
  //////////////////////////////   move nodes at j_neg to the boundary

    for(int i=0; i<num_nodes_i-1; i++) {
      current_number = (2*num_nodes_i-1)*(2*num_nodes_j-2)+2*i+1;
      s = boundary_j_pos->get_s_at_position(new_nodes_all[current_number]);
      new_nodes_all[current_number] = boundary_j_pos->get_position_at_s(s);
    }
  //////////////////////////////   move nodes at j_pos to the boundary

    for(int j=0; j<num_nodes_j-1; j++) {
      current_number = (2*num_nodes_i-1)*(2*j+1);
      s = boundary_i_neg->get_s_at_position(new_nodes_all[current_number]);
      new_nodes_all[current_number] = boundary_i_neg->get_position_at_s(s);
    }
  //////////////////////////////   move nodes at i_neg to the boundary

    for(int j=0; j<num_nodes_j-1; j++) {
      current_number = (2*num_nodes_i-1)*(2*j+1)+2*num_nodes_i-2;
     s = boundary_i_pos->get_s_at_position(new_nodes_all[current_number]);
      new_nodes_all[current_number] = boundary_i_pos->get_position_at_s(s);
    }
  //////////////////////////////   move nodes at i_pos to the boundary

  current_number = 0;
  for(int j=0; j<num_nodes_j; j++) {
    for(int i=0; i<num_nodes_i; i++) {
      new_nodes_i_neg_j_neg[new_number_nn] = new_nodes_all[current_number];
      new_number_nn++;
      current_number++;
    }  // for i
    current_number = current_number+num_nodes_i-1;
  }  // for j
  ////////////////////////////////////////////////////   refine i_neg_j_neg

  current_number = num_nodes_i-1;
  for(int j=0; j<num_nodes_j; j++) {
    for(int i=0; i<num_nodes_i; i++) {
      new_nodes_i_pos_j_neg[new_number_pn] = new_nodes_all[current_number];
      new_number_pn++;
      current_number++;
    }  // for i
    current_number = current_number+num_nodes_i-1;
  }  // for j
  ////////////////////////////////////////////////////   refine i_pos_j_neg

  current_number = new_num_i*(num_nodes_j-1);
  for(int j=0; j<num_nodes_j; j++) {
    for(int i=0; i<num_nodes_i;i++) {
      new_nodes_i_neg_j_pos[new_number_np] = new_nodes_all[current_number];
      new_number_np++;
      current_number++;
    }  // for i
    current_number = current_number+num_nodes_i-1;
  }  // for j
  ////////////////////////////////////////////////////   refine i_neg_j_pos

  current_number = new_num_i*(num_nodes_j-1)+num_nodes_i-1;
  for(int j=0; j<num_nodes_j; j++) {
    for(int i=0; i<num_nodes_i;i++) {
      new_nodes_i_pos_j_pos[new_number_pp] = new_nodes_all[current_number];
      new_number_pp++;
      current_number++;
    }  // for i
    current_number = current_number+num_nodes_i-1;
  }  // for j
  ////////////////////////////////////////////////////   refine i_pos_j_pos

  for(int k=0; k<new_num_i; k++) {
    int boundary_number = new_num_i*(num_nodes_j-1)+k;
    boundary_nodes_j[k] = new_nodes_all[boundary_number];
  }

  for(int k=0; k<new_num_j; k++) {
    int boundary_number = new_num_i*k+num_nodes_i-1;
    boundary_nodes_i[k] = new_nodes_all[boundary_number];
  }

  std::shared_ptr<Curve2D_Base> boundary_i_new( new Spline2D(boundary_nodes_i) );
  std::shared_ptr<Curve2D_Base> boundary_j_new( new Spline2D(boundary_nodes_j) );

  ////////////////////////////////////////////////////   Build new boundaries

  new_blocks.i_neg_j_neg = std::unique_ptr<Block_2D>(new Block_2D(num_nodes_i,
  							          num_nodes_j,
  							          new_nodes_i_neg_j_neg,
  								  boundary_i_new,
  							          block.get_boundary_i_neg(),
  								  boundary_j_new,
  							          block.get_boundary_j_neg()
  							          ));
  ////////////////////////////////////////////////   done new block of i_neg_j_neg
  
  new_blocks.i_pos_j_neg = std::unique_ptr<Block_2D>(new Block_2D(num_nodes_i,
							          num_nodes_j,
							          new_nodes_i_pos_j_neg, 
							          block.get_boundary_i_pos(),
							          boundary_i_new,
							          boundary_j_new,
							          block.get_boundary_j_neg()
							          ));
  ////////////////////////////////////////////////   done new block of i_pos_j_neg

  new_blocks.i_neg_j_pos = std::unique_ptr<Block_2D>(new Block_2D(num_nodes_i,
							          num_nodes_j,
							          new_nodes_i_neg_j_pos, 
								  boundary_i_new,
							          block.get_boundary_i_neg(),
							          block.get_boundary_j_pos(),
							          boundary_j_new
							          ));
  ////////////////////////////////////////////////   done new block of i_neg_j_pos

  new_blocks.i_pos_j_pos = std::unique_ptr<Block_2D>(new Block_2D(num_nodes_i,
							          num_nodes_j,
							          new_nodes_i_pos_j_pos, 
							          block.get_boundary_i_pos(),
							          boundary_i_new,
							          block.get_boundary_j_pos(),
							          boundary_j_new
						  	          ));
  ////////////////////////////////////////////////   done new block of i_pos_j_pos

  return std::move(new_blocks);
}
