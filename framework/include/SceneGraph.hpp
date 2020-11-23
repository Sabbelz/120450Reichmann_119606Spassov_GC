#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include <string>
#include "Node.hpp"

class SceneGraph { //Singleton -> https://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Entwurfsmuster:_Singleton
public:

    SceneGraph();

    ~SceneGraph();

    static SceneGraph* instance();

    std::string getName() const;

    void setName(std::string const &string);

    std::shared_ptr<Node> getRoot() const;

    void setRoot(std::shared_ptr<Node> const &Node);

    std::string printGraph() const;

private:
    static SceneGraph* instance_;
    std::string name_;
    std::shared_ptr<Node> root_;


};

#endif //SCENEGRAPH_HPP
