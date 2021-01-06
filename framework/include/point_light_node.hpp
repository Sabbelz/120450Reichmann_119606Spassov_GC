#ifndef POINT_LIGHT_NODE_HPP
#define POINT_LIGHT_NODE_HPP

#include "node.hpp"
#include "model.hpp"
#include "light_color.hpp"


class PointLightNode: public Node{

public:
    explicit PointLightNode(std::string const& name);

    PointLightNode(std::string const& name, std::shared_ptr<Node> const& parent); //TODO still here, because otherwise the solaris node wouldn't be created. Maybe the human race loves to live with some light at the horizon.

    PointLightNode(std::string const& name, float light_intensity, LightColor light_color);

    PointLightNode(std::string const& name, std::shared_ptr<Node> const& parent, float light_intensity,
                   LightColor light_color);

    PointLightNode(std::string const& name, std::shared_ptr<Node> const& parent, glm::mat4 const& local_transform,
                   float light_intensity, LightColor light_color);

    void setLightIntensity(float lightIntensity);

    float getLightIntensity() const;

    void setLightColor(LightColor const& light_color);

    LightColor getLightColor();

private:
    float light_intensity_;
    LightColor light_color_;
};

#endif //POINT_LIGHT_NODE_HPP