#include "SceneGraph.hpp"


/**
 * default constructor
 */
SceneGraph::SceneGraph():
    name_{"SceneGraph"},
    root_(std::make_shared<Node>("root"))
    { }

/**
 * Method which returns the name of the SceneGraph
 * @return
 */
std::string SceneGraph::getName() const {
    return name_;
}

/**
 * Method for setting the name of the SceneGraph
 * @param string
 */
void SceneGraph::setName(std::string const& string) {
    name_ = string;
}

/**
 * Method which returns the root of the SceneGraph
 * @return the root
 */
std::shared_ptr<Node> SceneGraph::getRoot() const {
    return root_;
}

/**
 * Method to set the root of the SceneGraph
 * @param Node the given root
 */
void SceneGraph::setRoot(std::shared_ptr<Node> const& Node) {
    root_ = Node;
}

std::string SceneGraph::printGraph() const {

}