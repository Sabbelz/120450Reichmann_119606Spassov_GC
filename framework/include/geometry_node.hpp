
#ifndef GEOMETRY_NODE_HPP
#define GEOMETRY_NODE_HPP

#include "model.hpp"
#include "node.hpp"

class GeometryNode : public Node {
public:

    GeometryNode(std::string const& name, model const& geometry);

    GeometryNode(std::string const& name, std::shared_ptr<Node> parent, model const& geometry);

    GeometryNode(std::string const& name, std::shared_ptr<Node> parent, glm::mat4x4 const& localTransform, model const& geometry);

    GeometryNode(std::string const& name, std::shared_ptr<Node> parent, glm::mat4x4 const& localTransform, model const& geometry, unsigned int size, unsigned int distance, float speed);

    model getGeometry() const;

    void setGeometry(model new_geometry);

private:
    model geometry_;

    unsigned int size_;

    unsigned int distance_;

    float speed_;
};
#endif //GEOMETRY_NODE_HPP
