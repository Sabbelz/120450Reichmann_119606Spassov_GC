#include "geometry_node.hpp"

GeometryNode::GeometryNode(std::string const& name, model const& geometry):
        Node(name), geometry_(geometry)
{}

GeometryNode::GeometryNode(std::string const& name, std::shared_ptr<Node> parent, model const& geometry):
        Node(name, parent), geometry_(geometry)
{}

GeometryNode::GeometryNode(std::string const& name, std::shared_ptr<Node> parent, glm::mat4x4 const& localTransform, model const& geometry):
        Node(name, parent, localTransform), geometry_(geometry)
{}

/**
 * Constructor which uses size, distance and speed as values to create a geometry_node with specific features.
 */
GeometryNode::GeometryNode(std::string const& name, std::shared_ptr<Node> parent, glm::mat4x4 const& localTransform, model const& geometry, unsigned int size, unsigned int distance, float speed):
        Node(name, parent, localTransform), geometry_(geometry),
        size_(size),
        distance_(distance),
        speed_(speed)//TODO change float to vec?!
{}
/**
 * Method which returns the geometry
 */
model GeometryNode::getGeometry() const {
    return geometry_;
}

/**
 * Method which sets the geometry model
 * @param new_geometry which is used for setting the geometry
 */
void GeometryNode::setGeometry(model new_geometry) {
    geometry_ = new_geometry;
}