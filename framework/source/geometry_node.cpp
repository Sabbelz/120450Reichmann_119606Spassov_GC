#include "geometry_node.hpp"

/**
 * Default Constructor
 * @param name the given name
 * @param geometry the given geometry
 */
GeometryNode::GeometryNode(std::string const& name, model const& geometry):
        Node(name), geometry_(geometry),
        size_(0),
        distance_(0),
        rotation_angle_(0.0f)
{}

/**
 * Constructor
 * @param name the given name
 * @param parent the given parent
 * @param geometry the given geometry
 */
GeometryNode::GeometryNode(std::string const& name, std::shared_ptr<Node> parent, model const& geometry):
        Node(name, parent), geometry_(geometry),
        size_(0),
        distance_(0),
        rotation_angle_(0.0f)
{}

/**
 * Constructor
 * @param name the given name
 * @param parent the given parent
 * @param localTransform the given local transform
 * @param geometry the given geometry
 */
GeometryNode::GeometryNode(std::string const& name, std::shared_ptr<Node> parent, glm::mat4x4 const& localTransform,
                           model const& geometry):
        Node(name, parent, localTransform), geometry_(geometry),
        size_(0),
        distance_(0),
        rotation_angle_(0.0f)
{}

/**
 * Constructor which uses size, distance and speed as values to create a geometry_node with specific features.
 * @param name the given name
 * @param parent the given parent
 * @param localTransform the given local Transform
 * @param geometry the geometry
 * @param size the size of the object
 * @param distance the distance of the object to the root
 * @param speed the speed at which the objects rotates around the centre
 */
GeometryNode::GeometryNode(std::string const& name, std::shared_ptr<Node> parent, glm::mat4x4 const& localTransform,
                           model const& geometry, unsigned int size, unsigned int distance, float speed):
        Node(name, parent, localTransform), geometry_(geometry),
        size_(size),
        distance_(distance),
        rotation_angle_(speed)
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

/**
 * Method which returns the size of the geometry_node
 * @return the requested size
 */
unsigned int GeometryNode::getSize() {
    return size_;
}

/**
 * Method which sets the size of the geometry_node
 * @param size the given size
 */
void GeometryNode::setSize(unsigned int size) {
    size_ = size;
}

/**
 * Method which gets the Distance of the geometry_node
 * @return the asked distance
 */
unsigned int GeometryNode::getDistance() {
    return distance_;
}

/**
 * Method which sets the distance of the geometry_node
 * @param distance the given distance
 */
void GeometryNode::setDistance(unsigned int distance) {
    distance_ = distance;
}

/**
 * Method which returns the speed
 * @return the requested speed value
 */
float GeometryNode::getRotationAngle() {
    return rotation_angle_;
}

/**
 * Sets the speed of the geometry_node
 * @param speed the given value
 */
void GeometryNode::setRotationAngle(float speed) {
    rotation_angle_ = speed;
}

/**
 * Method which returns the rotation matrix
 * @return the rotation matrix
 */
glm::mat4x4 GeometryNode::getRotationMatrix() const{
    glm::mat4x4 rotation_matrix = glm::rotate(glm::mat4x4{}, rotation_angle_, glm::fvec3{0.0f, 1.0f, 0.0f});
    return rotation_matrix;
}