#ifndef APPLICATION_SOLAR_HPP
#define APPLICATION_SOLAR_HPP

#include "application.hpp"
#include "model.hpp"
#include "structs.hpp"
#include "scene_graph.hpp"

// gpu representation of model
class ApplicationSolar : public Application {

public:

    // allocate and initialize objects
    ApplicationSolar(std::string const& resource_path);
    // free allocated objects
    ~ApplicationSolar();

    // react to key input
    void keyCallback(int key, int action, int mods);
    //handle delta mouse movement input
    void mouseCallback(double pos_x, double pos_y);
    //handle resizing
    void resizeCallback(unsigned width, unsigned height);

    // draw all objects
    void render() const;

protected:

    void initializeShaderPrograms();
    void initializeGeometry();
    void initializeSceneGraph();
    // subfunctions for initializeSceneGraph
    void initializeStars(unsigned int const star_amount);
    void initializeOrbits();
    void initializeSkybox();


    // update uniform values
    void uploadUniforms();
    // upload projection matrix
    void uploadProjection();
    // upload view matrix
    void uploadView();

    // scene graph, a pointer since the scene graph is designed as a singleton
    SceneGraph* scene_graph_;

    // cpu representation of model
    model_object planet_object_;
    model_object star_object_;
    model_object orbit_object_;
    model_object skybox_object_;

    // camera transform matrix
    glm::fmat4 m_view_transform;
    // camera projection matrix
    glm::fmat4 m_view_projection_;

    //skybox
    GLenum active_skymap_texture;
    texture_object skymap_texture;

    // GeometryNode names of all solar bodies
    std::array<std::string, 11> solar_bodies_geom_names_;

    // name of currently used shader
    std::string shader_name_;

    //bool for the renderer to pause
    static bool paused_;

};

#endif