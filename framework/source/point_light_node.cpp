#include "point_light_node.hpp"

PointLightNode::PointLightNode(const std::string &name):
        Node(name)
{}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> parent): //TODO has to be replaced; application_solar "solaris"
        Node(name)
{}

PointLightNode::PointLightNode(const std::string &name, double lightIntensity, lightColor lightColor):
    Node(name)
{}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> parent, double lightIntensity, lightColor lightColor):
    Node(name, parent)
{}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> parent, const glm::mat4 &localTransform, double lightIntensity, lightColor lightColor):
    Node(name, parent, localTransform)
{}

/**
 * sets the lightIntensity of the lightNode
 * @param lightIntensity the given intensity
 */
void PointLightNode::setLightIntensity(double lightIntensity) {
    lightIntensity_ = lightIntensity;
}

/**
 * receives the lightIntensity
 * @return the wanted intensity
 */
double PointLightNode::getLightIntensity() {
    return lightIntensity_;
}

/**
 * sets the lightColor of the lightNode
 * @param lightColor the given color
 */
void PointLightNode::setLightColor(lightColor lightColor) {
    lightColor_ = lightColor;
}

/**
 * gets the lightColor
 * @return the asked color
 */
lightColor PointLightNode::getLightColor() {
    return lightColor_;
}
