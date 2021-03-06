#include "node.hpp"

/**
 * Default constructor (depth is default == 0)
 * @param name: the given name
 */
Node::Node(std::string const& name):
    parent_(nullptr),
    name_(name),
    path_("/" + name),
    depth_(0)
{ }

/**
 * Constructor with provided parent node
 * @param name: the given name
 * @param parent: the given parent node
 */
Node::Node(std::string const& name, std::shared_ptr<Node> const& parent):
    parent_(parent),
    name_(name),
    depth_(parent->getDepth() + 1)
{
    std::string copy_helper = parent->path_;
    path_ = copy_helper + "/" + name_;
}

/**
 * Constructor with provided parent node and local transform
 * @param name: the given name
 * @param parent: the given parent node
 * @param localTransform: the local transform which has to be set
 */
Node::Node(std::string const& name, std::shared_ptr<Node> const& parent, glm::mat4 const& localTransform):
        parent_(parent),
        name_(name),
        depth_(parent->getDepth() + 1),
        local_transform_(localTransform)
{
    std::string copy_helper = parent->path_;
    path_ = copy_helper + "/" + name_;
}

/**
 * Method which returns a pointer for the parent node
 * @return the requested value
 */
std::shared_ptr<Node> Node::getParent() const {
    return parent_;
}

/**
 * Method which sets a given Node as the new parent
 * @param parent: the new parent Node
 */
void Node::setParent(std::shared_ptr<Node> const& parent) {
    parent_ = parent;
    depth_ = parent_->getDepth() + 1;
    path_ = std::string(parent_->getPath()) + "/" + name_;
}

/**
 * Method which returns the first found child found in its children tree with matching name.
 * It will do so recursively.
 * @param child_name: the child which has to be found
 * @return a pointer: to the wanted children or nullptr in case of no success
 */
std::shared_ptr<Node> Node::getChildren(std::string const& child_name) const {
    for (auto const& child: children_){
        if (child->name_ == child_name){
            return child;
        } else {
            auto next_level_search = child->getChildren(child_name);
            if (next_level_search != nullptr) {
                return next_level_search;
            }
        }
    }
    // attention of behaviour in case of no success: nullptr will be returned
    return nullptr;
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
std::string Node::getPath() {
    if (parent_ == nullptr){
        return path_;
    } else {
        path_ = parent_->getPath() + path_;
        return path_;
    }
}

/**
 * Method which will return the depth
 * @return the depth
 */
int Node::getDepth() {
    if(parent_ == nullptr){
        return 0;
    } else {
        depth_ = parent_->getDepth() + 1;
        return depth_;
    }
}

/**
 * Method for receiving the local transform
 * @return the requested local transform
 */
glm::mat4x4 Node::getLocalTransform() const {
    return local_transform_;
}

/**
 * Method for setting the local Transform
 * @param mat the given and new local Transform
 */
void Node::setLocalTransform(glm::mat4x4 const& new_local_transform) {
    local_transform_ = new_local_transform;
}

/**
 * Method for getting the world transformation matrix of the node.
 * In the case of the node being the root, its local matrix is considered the matrix of the world.
 * Otherwise the world matrix of the parent will be multiplied with the local matrix,
 * creating the world matrix for this node.
 * @return the wanted matrix
 */
glm::mat4x4 Node::getWorldTransform() const {
    if (parent_ == nullptr){
        return local_transform_;
    } else {
        return parent_->getWorldTransform() * local_transform_;
    }
}

/**
 * Method which sets world transform
 * @param mat the given world transform
 */
void Node::setWorldTransform(glm::mat4x4 const& mat) {
    world_transform_ = mat;
}

/**
 * Method which adds a new child to the node
 * @param children the new child
 */
void Node::addChildren(std::shared_ptr<Node> child) {
    children_.push_back(child);
}

/**
 * Method for removing a child
 * @param children the child which has to be removed
 */
void Node::removeChildren(const std::string &children) {
    for(auto const& it: children_){
        if(it->getName()==children){
            children_.remove(it);
        }
    }
}





