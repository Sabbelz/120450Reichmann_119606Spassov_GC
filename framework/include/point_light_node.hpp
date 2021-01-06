#ifndef POINT_LIGHT_NODE_HPP
#define POINT_LIGHT_NODE_HPP

#include "node.hpp"
#include "model.hpp"
#include "light_color.hpp"


class PointLightNode: public Node{

public:
    explicit PointLightNode(std::string const& name);

    PointLightNode(std::string const& name, std::shared_ptr<Node> parent); //TODO still here, because otherwise the solaris node wouldn't be created. Maybe the human race loves to live with some light at the horizon.

    PointLightNode(std::string const& name, double lightIntensity, LightColor lightColor);

    PointLightNode(std::string const& name, std::shared_ptr<Node> parent, double lightIntensity, LightColor lightColor);

    PointLightNode(std::string const& name, std::shared_ptr<Node> parent, glm::mat4 const& localTransform, double lightIntensity, LightColor lightColor);

    void setLightIntensity(double lightIntensity);

    double getLightIntensity();

    void setLightColor(LightColor light_color);

    LightColor getLightColor();

private:
    double lightIntensity_;

    LightColor light_color_;
};

#endif //POINT_LIGHT_NODE_HPP