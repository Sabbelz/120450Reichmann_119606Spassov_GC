#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <glm/glm.hpp>
#include <memory>
#include "light_color.hpp"

class Node {
public:
    explicit Node(std::string const& name);

    Node(std::string const& name, std::shared_ptr<Node> const& parent);

    Node(std::string const& name, std::shared_ptr<Node> const& parent, glm::mat4 const& localTransform);

    ~Node() {};

    std::shared_ptr<Node> getParent() const;

    void setParent(std::shared_ptr<Node> const& parent);

    std::shared_ptr<Node> getChildren(std::string const& child_name) const;

    std::list<std::shared_ptr<Node>> getChildrenList() const;

    std::string getName() const;

    std::string getPath();

    int getDepth();

    glm::mat4x4 getLocalTransform() const;

    void setLocalTransform(glm::mat4x4 const& mat);

    glm::mat4x4 getWorldTransform() const;

    void setWorldTransform(glm::mat4x4 const& mat);

    void addChildren(std::shared_ptr<Node> children);

    void removeChildren(std::string const& children);

    void setBaseColour(LightColor const& new_base_color){
        base_colour_ = new_base_color;
    }

    LightColor getBaseColour(){
        return base_colour_;
    }

protected:
    std::shared_ptr<Node> parent_;
    std::list<std::shared_ptr<Node>> children_;
    std::string name_;
    std::string path_;
    int depth_ = 0;
    glm::mat4x4 local_transform_;
    glm::mat4x4 world_transform_;
    LightColor base_colour_ = LightColor{0, 0, 0};

};

#endif //NODE_HPP
