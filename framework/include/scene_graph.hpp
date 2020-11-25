#ifndef SCENE_GRAPH_HPP
#define SCENE_GRAPH_HPP

#include <string>
#include "node.hpp"
#include "camera_node.hpp"
#include "geometry_node.hpp"
#include "point_light_node.hpp"

class SceneGraph { //Singleton -> https://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Entwurfsmuster:_Singleton
public:

    SceneGraph();

    ~SceneGraph();

    static SceneGraph* getSceneGraphInstance();

    std::string getName() const;

    void setName(std::string const &string);

    std::shared_ptr<Node> getRoot() const;

    void setRoot(std::shared_ptr<Node> const &Node);

    std::string printGraph() const;

private:
    static SceneGraph* instance_;
    std::string name_;
    std::shared_ptr<Node> root_;
    static bool initialization_status_;


};

#endif //SCENE_GRAPH_HPP
