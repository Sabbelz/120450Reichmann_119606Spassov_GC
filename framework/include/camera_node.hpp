#ifndef CAMERA_NODE_HPP
#define CAMERA_NODE_HPP

#include <glm/glm.hpp>
#include <string>
#include "node.hpp"

class CameraNode : public Node{
public:
    CameraNode(std::string name, bool isPerspective, bool isEnabled, glm::mat4 projectionMatrix);

    CameraNode(std::string name, bool isPerspective, bool isEnabled, glm::mat4 projectionMatrix, std::shared_ptr<Node> parent);

    CameraNode(std::string name, bool isPerspective, bool isEnabled, glm::mat4 projectionMatrix, std::shared_ptr<Node> parent, glm::mat4 localTransform);

    bool getPerspective() const;

    bool getEnabled() const;

    void setEnabled(bool const& enable);

    glm::mat4 getProjectionMatrix() const;

    void setProjectionMatrix(glm::mat4 const& prmat);

private:
    bool isPerspective_;

    bool isEnabled_;

    glm::mat4 projectionMatrix_;
};

#endif //CAMERA_NODE_HPP
