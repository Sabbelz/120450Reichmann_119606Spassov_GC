#include "point_light_node.hpp"

PointLightNode::PointLightNode(const std::string &name):
    Node(name)
{}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> parent):
    Node(name, parent)
{}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> parent, const glm::mat4 &localTransform):
    Node(name, parent, localTransform)
{}