#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include <string>
#include "Node.hpp"

class SceneGraph { //TODO Singleton -> https://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Entwurfsmuster:_Singleton
public:

    SceneGraph();

    SceneGraph(std::string name);

    SceneGraph(std::string name, std::shared_ptr<Node> root);

    ~SceneGraph();

    std::string getName() const;

    void setName(std::string const &string);

    std::shared_ptr<Node> getRoot() const;

    void setRoot(std::shared_ptr<Node> const &Node);

    std::string printGraph() const;

private:

    std::string name_;
    std::shared_ptr<Node> root_;


};

#endif //SCENEGRAPH_HPP
