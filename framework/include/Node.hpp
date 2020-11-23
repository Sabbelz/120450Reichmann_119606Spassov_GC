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
    Node();

    Node(std::string const& name);

    Node(std::string const& name, std::shared_ptr<Node> parent);

    virtual ~Node() {};

    virtual Node getParent() const;

    virtual void setParent(Node const& parent);

    virtual Node getChildren(std::string const& children) const;

    virtual std::list<Node> getChildrenList() const;

    virtual std::string getName() const;

    virtual std::string getPath() const;

    virtual int getDepth() const;

    virtual glm::mat4 getLocalTransform() const;

    virtual void setLocalTransform(glm::mat4 const& mat);

    virtual glm::mat4 getWorldTransform() const;

    virtual void setWorldTransform(glm::mat4 const& mat);

    virtual void addChildren(Node const& children);

    virtual void removeChildren(std::string const& children);

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
