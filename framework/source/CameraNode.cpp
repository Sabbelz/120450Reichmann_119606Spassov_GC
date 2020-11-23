#include "CameraNode.hpp"

/**
 * One of three constructors for the camera node
 * @param name the given name for the node
 * @param isPerspective the given bool, if the node is perspective
 * @param isEnabled the given bool, if it is enabled
 * @param projectionMatrix given projection matrix
 */
CameraNode::CameraNode(std::string name, bool isPerspective, bool isEnabled, glm::mat4 projectionMatrix):
    Node(name),
    isPerspective_(isPerspective),
    isEnabled_(isEnabled),
    projectionMatrix_(projectionMatrix)
{ }

/**
 * One of three constructors for the camera node
 * @param name the given name for the node
 * @param isPerspective the given bool, if the node is perspective
 * @param isEnabled the given bool, if it is enabled
 * @param projectionMatrix given projection matrix
 * @param parent the given parent node
 */
CameraNode::CameraNode(std::string name, bool isPerspective, bool isEnabled, glm::mat4 projectionMatrix, std::shared_ptr<Node> parent):
        Node(name, parent),
        isPerspective_(isPerspective),
        isEnabled_(isEnabled),
        projectionMatrix_(projectionMatrix)
{ }

/**
 * One of three constructors for the camera node
 * @param name the given name for the node
 * @param isPerspective the given bool, if the node is perspective
 * @param isEnabled the given bool, if it is enabled
 * @param projectionMatrix given projection matrix
 * @param parent the given parent node
 * @param localTransform the given local transform
 */
CameraNode::CameraNode(std::string name, bool isPerspective, bool isEnabled, glm::mat4 projectionMatrix, std::shared_ptr<Node> parent, glm::mat4 localTransform):
        Node(name, parent, localTransform),
        isPerspective_(isPerspective),
        isEnabled_(isEnabled),
        projectionMatrix_(projectionMatrix)
{ }

/**
 * Method which get the perspective of the camera node
 * @return true or false
 */
bool CameraNode::getPerspective() const {
    return isPerspective_;
}

/**
 * Method for the knowledge if the Node is enabled
 * @return true or false
 */
bool CameraNode::getEnabled() const {
    return isEnabled_;
}

/**
 * Method which changes the status of enable
 * @param enable the new given status
 */
void CameraNode::setEnabled(const bool &enable) {
    isEnabled_ = enable;
}

/**
 * gets the projection matrix
 * @return the wanted projection matrix
 */
glm::mat4 CameraNode::getProjectionMatrix() const {
    return projectionMatrix_;
}

/**
 * sets the new projection matrix
 * @param prmat the new projection matrix
 */
void CameraNode::setProjectionMatrix(const glm::mat4 &prmat) {
    projectionMatrix_ = prmat;
}