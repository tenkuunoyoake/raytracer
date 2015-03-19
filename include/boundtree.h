#ifndef BOUNDTREE_H
#define BOUNDTREE_H
#endif

#include <vector>

#ifndef BOUNDING_H
#include "bounding.h"
#endif

#ifndef RAY_H
#include "ray.h"
#endif

#ifndef SHAPE_H
#include "shape.h"
#endif

//*****************************************************************************
// BoundingTree
//*****************************************************************************

class BoundingTree {

  public:

    // Declarations
    bool leaf;
    Shape* shape;
    BoundingBox bbox;
    BoundingTree* left_child;
    BoundingTree* right_child;

    // Methods
    void create_bounding_box(vector<Shape*> shapes, 
        BoundingBox *last_bbox, int axis, bool left);

    void init_root_bbox(vector<Shape*> shapes);
    void init_child_bbox(BoundingBox* last_bbox);
    void split_left_bbox(BoundingBox* last_bbox, vector<Shape*> shapes, int axis);
    void split_right_bbox(BoundingBox* last_bbox, vector<Shape*> shapes, int axis);

    vector<Shape*> sort_shapes(vector<Shape*> shapes, int axis, 
        bool check_max);

    Shape* intersect_object(Ray ray, Shape* shadow_shape);

    // Constructor
    BoundingTree();
    BoundingTree(vector<Shape*> shapes, BoundingBox* last_bbox, int axis, 
        bool left);

    // Destructor
    void dispose();

};