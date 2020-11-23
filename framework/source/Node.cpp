#include "Node.hpp"

/**
 * Default constructor (depth is default == 0)
 * @param name the given name
 */
Node::Node(std::string name):
    name_(name),
    path_("/" + name),
    parent_(nullptr)
{ }

/**
 * Constructor with provided parent node
 * @param name the given name
 * @param parent the given parent node
 */
Node::Node(std::string name, std::shared_ptr<Node> parent):
    name_(name),
    path_(getPath()),
    parent_(parent),
    depth_(parent->getDepth() + 1)
{ }

/**
 * Constructor with provided parent node and local transform
 * @param name the given name
 * @param parent the given parent node
 * @param localTransform the local transform which has to be set
 */
Node::Node(std::string name, std::shared_ptr<Node> parent, glm::mat4 localTransform):
        name_(name),
        path_(getPath()),
        parent_(parent),
        localTransform_(localTransform),
        depth_(parent->getDepth() + 1)
{ }

/**
 * Method which returns a pointer for the parent node
 * @return the requested value
 */
std::shared_ptr<Node> Node::getParent() const {
    return parent_;
}

/**
 * Method which sets a given Node as the new parent
 * @param parent the new parent Node
 */
void Node::setParent(std::shared_ptr<Node> parent) {
    parent_ = parent;
}

/**
 * Method which returns the wanted children of the node
 * @param children the children which has to be found
 * @return a pointer to the wanted children
 */
std::shared_ptr<Node> Node::getChildren(const std::string &children) const {
//TODO getChildren
}

/**
 * Method which returns the list of children
 * @return the requested list
 */
std::list<std::shared_ptr<Node>> Node::getChildrenList() const {
    return children_;
}

/**
 * Method for receiving the name od the node
 * @return the name of the node
 */
std::string Node::getName() const {
    return name_;
}

/**
 * Method for getting the path of the node
 * @return the requested path
 */
std::string Node::getPath() const {
    return path_;
}

/**
 * Method which will return the depth
 * @return the depth
 */
int Node::getDepth() const {
    return depth_;
}

/**
 * Method for receiving the local transform
 * @return the requested local transform
 */
glm::mat4 Node::getLocalTransform() const {
    return glm::mat4();
}

/**
 * Method for setting the local Transform
 * @param mat the given and new local Transform
 */
void Node::setLocalTransform(const glm::mat4 &mat) {
//TODO setLocalTransform
}

/**
 * returns the world transform
 * @return the wanted world transform
 */
glm::mat4 Node::getWorldTransform() const {
    return worldTransform_;//TODO
}

/**
 * Method which sets world transform
 * @param mat the given world transform
 */
void Node::setWorldTransform(const glm::mat4 &mat) {
    worldTransform_ = mat;
}

/**
 * Method which adds a new child to the node
 * @param children the new child
 */
void Node::addChildren(std::shared_ptr<Node> children) {
    children_.push_back(children);
}

/**
 * Method for removing a child
 * @param children the child which has to be removed
 */
void Node::removeChildren(const std::string &children) {

}





