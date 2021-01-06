#include "point_light_node.hpp"

PointLightNode::PointLightNode(const std::string &name):
        Node(name)
{
    light_intensity_ = 0.5f;
    light_color_ = LightColor{255, 255, 255};
}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> const& parent): //TODO has to be replaced; application_solar "solaris" / WADUHECK?
        Node(name, parent)
{
    light_intensity_ = 0.5f;
    light_color_ = LightColor{255, 255, 255};
}

PointLightNode::PointLightNode(const std::string &name, float light_intensity, LightColor light_color):
        Node(name)
{
    light_intensity_ = light_intensity;
    light_color_ = light_color;
}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> const& parent, float light_intensity,
                               LightColor light_color):
        Node(name, parent)
{
    light_intensity_ = light_intensity;
    light_color_ = light_color;
}

PointLightNode::PointLightNode(const std::string &name, std::shared_ptr<Node> const& parent,
                               const glm::mat4 &local_transform, float light_intensity, LightColor light_color):
        Node(name, parent, local_transform)
{
    light_intensity_ = light_intensity;
    light_color_ = light_color;
}

/**
 * sets the lightIntensity of the lightNode
 * @param lightIntensity the given intensity
 */
void PointLightNode::setLightIntensity(float lightIntensity) {
    light_intensity_ = lightIntensity;
}

/**
 * receives the lightIntensity
 * @return the wanted intensity
 */
float PointLightNode::getLightIntensity() const {
    return light_intensity_;
}

/**
 * sets the LightColor of the lightNode
 * @param light_color the given color
 */
void PointLightNode::setLightColor(LightColor const& light_color) {
    light_color_ = light_color;
}

/**
 * gets the LightColor
 * @return the asked color
 */
LightColor PointLightNode::getLightColor() {
    return light_color_;
}
