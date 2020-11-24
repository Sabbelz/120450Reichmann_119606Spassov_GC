#include "geometry_node.hpp"

/**
 * Method which returns the geometry
 */
model GeometryNode::getGeometry() const {
    return geometry_;
}

/**
 * Method which sets the geometry model
 * @param model which is used for setting the geometry
 */
void GeometryNode::setGeometry(model model) {
    geometry_ = model;
}