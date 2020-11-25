#ifndef POINT_LIGHT_NODE_HPP
#define POINT_LIGHT_NODE_HPP

#include "node.hpp"

// TODO: think of some stuff unique for this node, like maybe light intensity or light colour
class PointLightNode: public Node{

public:

    explicit PointLightNode(std::string const& name);

    PointLightNode(std::string const& name, std::shared_ptr<Node> parent);

    PointLightNode(std::string const& name, std::shared_ptr<Node> parent, glm::mat4 const& localTransform);
};

#endif //POINT_LIGHT_NODE_HPP