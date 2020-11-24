#include "scene_graph.hpp"


// static member pre-initialization:
// bool for checking if initialization occurred (needs to be static so it can be called without existing instance)
bool SceneGraph::initialization_status_ = false;
// uninitialized scene graph points to nullptr
SceneGraph* SceneGraph::instance_ = nullptr;

/**
 * default constructor
 */
SceneGraph::SceneGraph():
    name_("SceneGraph"),
    root_(std::make_shared<Node>("root"))
    { }

/**
 * THis method provides the singleton for the scene graph
 * @return the instance of the scene graph
 */
SceneGraph* SceneGraph::getSceneGraphInstance() {
    if(!initialization_status_){
        initialization_status_ = true;
        instance_ = new SceneGraph();
        return instance_;
    } else {
        return instance_;
    }
}
/**
 * Method which returns the name of the SceneGraph
 * @return the requested name
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

/**
 * Method for printing the graph
 * @return the graph as a string
 */
std::string SceneGraph::printGraph() const {
    std::string printValue = "Root";
    for (auto const& child : root_ ->getChildrenList()){
        printValue += child->getName();
    }
    return printValue;
}