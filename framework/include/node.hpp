#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <glm/glm.hpp>
#include <memory>

class Node {
public:
    explicit Node(std::string const& name);

    Node(std::string const& name, std::shared_ptr<Node> parent);

    Node(std::string const& name, std::shared_ptr<Node> parent, glm::mat4 const& localTransform);

    ~Node() {};

    std::shared_ptr<Node> getParent() const;

    void setParent(std::shared_ptr<Node> parent);

    std::shared_ptr<Node> getChildren(std::string const& children) const;

    std::list<std::shared_ptr<Node>> getChildrenList() const;

    std::string getName() const;

    std::string getPath() const;

    int getDepth() const;

    glm::mat4 getLocalTransform() const;

    void setLocalTransform(glm::mat4 const& mat);

    glm::mat4 getWorldTransform() const;

    void setWorldTransform(glm::mat4 const& mat);

    void addChildren(std::shared_ptr<Node> children);

    void removeChildren(std::string const& children);

protected:
    std::shared_ptr<Node> parent_;
    std::list<std::shared_ptr<Node>> children_;
    std::string name_;
    std::string path_;

    int depth_ = 0;
    glm::mat4 localTransform_;
    glm::mat4 worldTransform_;


};

#endif //NODE_HPP
