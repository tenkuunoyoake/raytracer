#include <limits>
#include "boundtree.h"

using namespace std;

//*****************************************************************************
// BoundingTree
//*****************************************************************************

// Quicksort algorithm that sorts shape by a certain axis
vector<Shape*> BoundingTree::sort_shapes(vector<Shape*> shapes, int axis, 
    bool check_max) {

  vector<Shape*> result(shapes);

  // Base case
  if (shapes.size() <= 1) {
    return result;
  }

  vector<Shape*> left_list;
  vector<Shape*> right_list;

  // Choose a pivot item v from I

  unsigned pivot_i = rand() % shapes.size();
  Shape* pivot = shapes[pivot_i];

  for (unsigned i = 0; i < shapes.size(); i++) {

    if (i == pivot_i) {
      continue;
    }

    // Partition I into two unsorted lists I1 and I2.

    switch(axis) {

      // X-axis
      case 0:

        if (check_max) {

          if (shapes[i]->bbox.x_max < pivot->bbox.x_max) {
            left_list.push_back(shapes[i]);
          } else {
            right_list.push_back(shapes[i]);
          }

        } else {

          if (shapes[i]->bbox.x_min < pivot->bbox.x_min) {
            left_list.push_back(shapes[i]);
          } else {
            right_list.push_back(shapes[i]);
          }

        }

        break;

      // Y-axis
      case 1:

        if (check_max) {

          if (shapes[i]->bbox.y_max < pivot->bbox.y_max) {
            left_list.push_back(shapes[i]);
          } else {
            right_list.push_back(shapes[i]);
          }

        } else {

          if (shapes[i]->bbox.y_min < pivot->bbox.y_min) {
            left_list.push_back(shapes[i]);
          } else {
            right_list.push_back(shapes[i]);
          }

        }

        break;

      // Z-axis
      case 2:

        if (check_max) {

          if (shapes[i]->bbox.z_max < pivot->bbox.z_max) {
            left_list.push_back(shapes[i]);
          } else {
            right_list.push_back(shapes[i]);
          }

        } else {

          if (shapes[i]->bbox.z_min < pivot->bbox.z_min) {
            left_list.push_back(shapes[i]);
          } else {
            right_list.push_back(shapes[i]);
          }

        }

        break;

    }

  }

  // Sort left and right lists recursively

  left_list = sort_shapes(left_list, axis, check_max);
  right_list = sort_shapes(right_list, axis, check_max);

  // Concatenate S1, v, and S2 together, yielding a sorted list S.

  for (unsigned i = 0; i < shapes.size(); i++) {
    if (i < left_list.size()) {
      result[i] = left_list[i];
    } else if (i == left_list.size()) {
      result[i] = pivot;
    } else {
      result[i] = right_list[i - left_list.size() - 1];
    }
  }

  return result;

}

Shape* BoundingTree::intersect_object(Ray ray, Shape* shadow_shape) {

  // Return the shape that has the lowest t value and is intersected
  Shape* temp;
  Shape* closest_shape = NULL;
  float best_t_value; 

  // If there's only one shape, return it if it intersects
  if (leaf) {

    if (shape->intersect(ray)) {
      closest_shape = shape;
    }

  } else {

    // If the ray actually intersects the box
    if (bbox.intersect(ray)) {
      // If there's an object in the left child that the ray intersects
      if ((temp = left_child->intersect_object(ray, shadow_shape))) {

        // You can't hit yourself
        if (temp != shadow_shape) {
          // Explicitly avoid two recursive calls
          closest_shape = temp;
          best_t_value = closest_shape->intersectT(ray);
        }

      } 

      // If there's an object in the right child that the ray intersects
      if ((temp = right_child->intersect_object(ray, shadow_shape))) {

        // Only if nothing hit on the left side closest shape, or the t_value
        // here is better than the one on the left side
        if (closest_shape == NULL || temp->intersectT(ray) <= best_t_value) {

          // You can't hit yourself
          if (temp != shadow_shape) {
            closest_shape = temp;
          }

        }
   
      }
    } 

  }

  return closest_shape;

}

void BoundingTree::init_root_bbox(vector<Shape*> shapes) {

  bbox.x_min = numeric_limits<float>::infinity();
  bbox.x_max = -1 * numeric_limits<float>::infinity();
  bbox.y_min = numeric_limits<float>::infinity();
  bbox.y_max = -1 * numeric_limits<float>::infinity();
  bbox.z_min = numeric_limits<float>::infinity();
  bbox.z_max = -1 * numeric_limits<float>::infinity();

  for (unsigned i = 0; i < shapes.size(); i++) {
    bbox.x_min = min(bbox.x_min, shapes[i]->bbox.x_min);
    bbox.x_max = max(bbox.x_max, shapes[i]->bbox.x_max);
    bbox.y_min = min(bbox.y_min, shapes[i]->bbox.y_min);
    bbox.y_max = max(bbox.y_max, shapes[i]->bbox.y_max);
    bbox.z_min = min(bbox.z_min, shapes[i]->bbox.z_min);
    bbox.z_max = max(bbox.z_max, shapes[i]->bbox.z_max);
  }

}

void BoundingTree::init_child_bbox(BoundingBox* last_bbox) {

  bbox.x_min = last_bbox->x_min;
  bbox.y_min = last_bbox->y_min;
  bbox.z_min = last_bbox->z_min;
  bbox.x_max = last_bbox->x_max;
  bbox.y_max = last_bbox->y_max;
  bbox.z_max = last_bbox->z_max;

}

void BoundingTree::split_left_bbox(BoundingBox* last_bbox, 
    vector<Shape*> shapes, int axis) {

  switch(axis) {
    case 0:
      bbox.x_max = shapes.back()->bbox.x_max;
      break;

    case 1:
      bbox.y_max = shapes.back()->bbox.y_max;
      break;

    case 2:
      bbox.z_max = shapes.back()->bbox.z_max;
      break;
  }

}

void BoundingTree::split_right_bbox(BoundingBox* last_bbox, 
    vector<Shape*> shapes, int axis) {

  vector<Shape*> sorted = sort_shapes(shapes, axis, false);

  switch(axis) {
    case 0:
      bbox.x_min = sorted.front()->bbox.x_min;
      break;

    case 1:
      bbox.y_min = sorted.front()->bbox.y_min;
      break;

    case 2:
      bbox.z_min = sorted.front()->bbox.z_min;
      break;
  }

}

void BoundingTree::create_bounding_box(vector<Shape*> shapes, 
    BoundingBox *last_bbox, int axis, bool left) {

  if (last_bbox) {

    init_child_bbox(last_bbox);

    // Use the old axis to create the bounding box
    if (left) {
      split_left_bbox(last_bbox, shapes, axis);
    } else {
      split_right_bbox(last_bbox, shapes, axis);
    }

  } else {

    init_root_bbox(shapes);

  }

}

BoundingTree::BoundingTree() {

  leaf = false;
  shape = NULL;
  left_child = NULL;
  right_child = NULL;

}

BoundingTree::BoundingTree(vector<Shape*> shapes, BoundingBox* last_bbox, 
    int axis, bool left) {

  /* Base cases */

  // In the rare case that nothing is being traced at all
  if (shapes.size() == 0) {
    shape = NULL;
    leaf = true;
    return;
  }

  // Base case (only one shape)
  if (shapes.size() == 1) {
    shape = shapes[0];
    leaf = true;
    return;
  }

  /* Declarations */

  vector<Shape*> sorted_shapes;
  vector<Shape*> left_shapes;
  vector<Shape*> right_shapes;

  leaf = false;
  shape = NULL;

  // Create the bounding box for the node (use the previous axis);
  create_bounding_box(shapes, last_bbox, (axis + 2) % 3, left);

  sorted_shapes = sort_shapes(shapes, axis, true);

  // Left children contains half of the shapes
  for (unsigned i = 0; i < shapes.size() / 2; i++) {
    left_shapes.push_back(sorted_shapes[i]);
  }

  // Right child contains the other half of the shapes
  for (unsigned i = shapes.size() / 2; i < shapes.size(); i++) {
    right_shapes.push_back(sorted_shapes[i]);
  }

  // Increment axes
  axis = (axis + 1) % 3;

  // Construct Left Child
  left_child = new BoundingTree(left_shapes, &bbox, axis, true);

  // Construct Right Child
  right_child = new BoundingTree(right_shapes, &bbox, axis, false); 

}

void BoundingTree::dispose() {

  if (!leaf) {
    left_child->dispose();
    right_child->dispose();
  }

  delete this;

}