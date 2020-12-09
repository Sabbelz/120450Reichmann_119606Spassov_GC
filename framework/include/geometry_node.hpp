
#ifndef GEOMETRY_NODE_HPP
#define GEOMETRY_NODE_HPP

#include "model.hpp"
#include "node.hpp"

#include <glm/gtc/matrix_transform.hpp>

class GeometryNode : public Node {
public:

    GeometryNode(std::string const& name, model const& geometry);

    GeometryNode(std::string const& name, std::shared_ptr<Node> parent, model const& geometry);

    GeometryNode(std::string const& name, std::shared_ptr<Node> parent, glm::mat4x4 const& localTransform, model const& geometry);

    GeometryNode(std::string const& name, std::shared_ptr<Node> parent, glm::mat4x4 const& localTransform, model const& geometry, unsigned int size, unsigned int distance, float speed);

    model getGeometry() const;

    void setGeometry(model new_geometry);

    unsigned int getSize();

    void setSize(unsigned int size);

    unsigned int getDistance();

    void setDistance(unsigned int distance);

    float getRotationAngle();

    void setRotationAngle(float speed);

    glm::mat4x4 getRotationMatrix() const;

private:
    model geometry_;

    unsigned int size_;

    unsigned int distance_;

    float rotation_angle_;

};
#endif //GEOMETRY_NODE_HPP
