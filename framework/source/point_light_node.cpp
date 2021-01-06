#include "point_light_node.hpp"

PointLightNode::PointLightNode(const std::string &name):
        Node(name)
{}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> parent): //TODO has to be replaced; application_solar "solaris"
        Node(name)
{}

PointLightNode::PointLightNode(const std::string &name, double lightIntensity, LightColor lightColor):
    Node(name)
{}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> parent, double lightIntensity, LightColor lightColor):
    Node(name, parent)
{}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> parent, const glm::mat4 &localTransform, double lightIntensity, LightColor lightColor):
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
 * sets the LightColor of the lightNode
 * @param light_color the given color
 */
void PointLightNode::setLightColor(LightColor light_color) {
    light_color_ = light_color;
}

/**
 * gets the LightColor
 * @return the asked color
 */
LightColor PointLightNode::getLightColor() {
    return light_color_;
}
