#include "application_solar.hpp"
#include "window_handler.hpp"

#include "utils.hpp"
#include "shader_loader.hpp"
#include "model_loader.hpp"

#include <glbinding/gl/gl.h>
// use gl definitions from glbinding 
using namespace gl;

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

ApplicationSolar::ApplicationSolar(std::string const& resource_path)
 : Application{resource_path}
 , planet_object{}
 , m_view_transform{glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 4.0f})}
 , m_view_projection_{utils::calculate_projection_matrix(initial_aspect_ratio)}
{
  initializeSceneGraph();
  initializeGeometry();
  initializeShaderPrograms();
}

ApplicationSolar::~ApplicationSolar() {
  glDeleteBuffers(1, &planet_object.vertex_BO);
  glDeleteBuffers(1, &planet_object.element_BO);
  glDeleteVertexArrays(1, &planet_object.vertex_AO);
}

void ApplicationSolar::render() const {

    std::shared_ptr<Node> scene_root = scene_graph_->getRoot();
    std::array<std::string, 11> solar_bodies;
    solar_bodies[0] = "sun_geom";
    solar_bodies[1] = "mercury_geom";
    solar_bodies[2] = "venus_geom";
    solar_bodies[3] = "earth_geom";
    solar_bodies[4] = "moon_geom";
    solar_bodies[5] = "mars_geom";
    solar_bodies[6] = "jupiter_geom";
    solar_bodies[7] = "saturn_geom";
    solar_bodies[8] = "uranus_geom";
    solar_bodies[9] = "neptune_geom";
    solar_bodies[10] = "pluto_geom";

    int random_counter = 0;
    // this should render like all of the solar bodies
    for (auto const& name: solar_bodies){
        random_counter++;
        std::shared_ptr<Node> solar_body = scene_root->getChildren(name);
        glm::mat4x4 parents_local_transform_matrix = solar_body->getParent()->getLocalTransform();
        glm::mat4x4 rotation_matrix = {};
        if (name == "moon_geom"){
            rotation_matrix = glm::rotate(glm::mat4x4{}, 0.0005f, glm::fvec3{0.0f, 1.0f, 0.0f});
        } else {
            rotation_matrix = glm::rotate(glm::mat4x4{}, 0.00005f + (float)(11-random_counter) * 0.00001f, glm::fvec3{0.0f, 1.0f, 0.0f});
        }

        auto test = rotation_matrix * parents_local_transform_matrix;

        // modify transformation matrix of solar body with rotation matrix, responsible for movement around parent node
        solar_body->getParent()->setLocalTransform(rotation_matrix * parents_local_transform_matrix);
        // fetch model matrix from the world transform of the solar body
        glm::mat4x4 model_matrix = solar_body->getWorldTransform();

        // bind shader to upload uniforms
        glUseProgram(m_shaders.at("planet").handle);

        // previous example model_matrix
        //glm::fmat4 model_matrix = glm::rotate(glm::fmat4{}, float(glfwGetTime()), glm::fvec3{0.0f, 1.0f, 0.0f});

        //model_matrix = glm::translate(model_matrix, glm::fvec3{0.0f, 0.0f, -1.0f});
        glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
                           1, GL_FALSE, glm::value_ptr(model_matrix));

        // extra matrix for normal transformation to keep them orthogonal to surface
        glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix);
        glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"),
                           1, GL_FALSE, glm::value_ptr(normal_matrix));

        // bind the VAO to draw
        glBindVertexArray(planet_object.vertex_AO);

        // draw bound vertex array using bound shader
        glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);
    }
}

void ApplicationSolar::uploadView() {
  // vertices are transformed in camera space, so camera transform must be inverted
  glm::fmat4 view_matrix = glm::inverse(m_view_transform);
  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ViewMatrix"),
                     1, GL_FALSE, glm::value_ptr(view_matrix));
}

void ApplicationSolar::uploadProjection() {
  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ProjectionMatrix"),
                     1, GL_FALSE, glm::value_ptr(m_view_projection_));
}

// update uniform locations
void ApplicationSolar::uploadUniforms() { 
  // bind shader to which to upload unforms
  glUseProgram(m_shaders.at("planet").handle);
  // upload uniform values to new locations
  uploadView();
  uploadProjection();
}

///////////////////////////// initialisation functions /////////////////////////
// load shader sources
void ApplicationSolar::initializeShaderPrograms() {
  // store shader program objects in container
  m_shaders.emplace("planet", shader_program{{{GL_VERTEX_SHADER, m_resource_path_ + "shaders/simple.vert"},
                                           {GL_FRAGMENT_SHADER, m_resource_path_ + "shaders/simple.frag"}}});
  // request uniform locations for shader program
  m_shaders.at("planet").u_locs["NormalMatrix"] = -1;
  m_shaders.at("planet").u_locs["ModelMatrix"] = -1;
  m_shaders.at("planet").u_locs["ViewMatrix"] = -1;
  m_shaders.at("planet").u_locs["ProjectionMatrix"] = -1;
}

// load models
void ApplicationSolar::initializeGeometry() {
  model planet_model = model_loader::obj(m_resource_path_ + "models/sphere.obj", model::NORMAL);

  // generate vertex array object
  glGenVertexArrays(1, &planet_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(planet_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &planet_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, planet_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planet_model.data.size(), planet_model.data.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
  // activate second attribute on gpu
  glEnableVertexAttribArray(1);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::NORMAL]);

   // generate generic buffer
  glGenBuffers(1, &planet_object.element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * planet_model.indices.size(), planet_model.indices.data(), GL_STATIC_DRAW);

  // store type of primitive to draw
  planet_object.draw_mode = GL_TRIANGLES;
  // transfer number of indices to model object 
  planet_object.num_elements = GLsizei(planet_model.indices.size());
}

void ApplicationSolar::initializeSceneGraph(){
    /* TODO LIST:
     * - initialize all planets, the moon and the sun
     * - think how to position the camera
     * - decide on some good local transformation parameters for the different bodies
     * - root -> body -> body_geom (exception moon)
     * */

    // link scene graph singleton to the application
    scene_graph_ = SceneGraph::getSceneGraphInstance();
    //scene_graph_->setName("hi");

    // resource_path_ is assigned in the read_resource_path() function in utils.cpp as "/../../resources/"
    std::string sphere_object_path = m_resource_path_ + "models/sphere.obj";
    // load sphere.obj, this model is the base for all solar bodies which are spherical
    model sphere_model = model_loader::obj(sphere_object_path, model::NORMAL);
    // get a pointer to the scene root, which will be the parent node of the solar system
    std::shared_ptr<Node> scene_root = scene_graph_->getRoot();

    ////////// Sun //////////
    std::shared_ptr<PointLightNode> solaris = std::make_shared<PointLightNode>("solaris", scene_root);
    std::shared_ptr<GeometryNode> sun_geom = std::make_shared<GeometryNode>("sun_geom", solaris,
                                                                            glm::scale({}, glm::fvec3{0.5f, 0.5f, 0.5f}),
                                                                            sphere_model);
    scene_root->addChildren(solaris);
    solaris->addChildren(sun_geom);

    ////////// Mercury //////////
    std::shared_ptr<Node> hermes = std::make_shared<Node>("hermes", scene_root,
                                                          glm::translate({}, glm::fvec3{1.0f, 0.0f, 0.0f}));
    std::shared_ptr<GeometryNode> mercury_geom = std::make_shared<GeometryNode>("mercury_geom", hermes,
                                                                                glm::scale({}, glm::fvec3{ 0.03f,0.03f,0.03f }),
                                                                                sphere_model);
    scene_root->addChildren(hermes);
    hermes->addChildren(mercury_geom);

    ////////// Venus //////////
    std::shared_ptr<Node> aphrodite = std::make_shared<Node>("aphrodite", scene_root,
                                                          glm::translate({}, glm::fvec3{1.2f, 0.0f, 0.0f}));
    std::shared_ptr<GeometryNode> venus_geom = std::make_shared<GeometryNode>("venus_geom", aphrodite,
                                                                                glm::scale({}, glm::fvec3{ 0.04f,0.04f,0.04f }),
                                                                                sphere_model);
    scene_root->addChildren(hermes);
    hermes->addChildren(venus_geom);

    ////////// Earth //////////
    std::shared_ptr<Node> terra = std::make_shared<Node>("terra", scene_root,
                                                             glm::translate({}, glm::fvec3{1.4f, 0.0f, 0.0f}));
    std::shared_ptr<GeometryNode> earth_geom = std::make_shared<GeometryNode>("earth_geom", terra,
                                                                              glm::scale({}, glm::fvec3{ 0.05f, 0.05f, 0.05f }),
                                                                              sphere_model);
    scene_root->addChildren(terra);
    terra->addChildren(earth_geom);

    ////////// Moon //////////
    std::shared_ptr<Node> artemis = std::make_shared<Node>("artemis", terra,
                                                         glm::translate({}, glm::fvec3{0.1f, 0.0f, 0.0f}));
    std::shared_ptr<GeometryNode> moon_geom = std::make_shared<GeometryNode>("moon_geom", artemis,
                                                                              glm::scale({}, glm::fvec3{0.0125f, 0.0125f, 0.0125f }),
                                                                              sphere_model);
    terra->addChildren(artemis);
    artemis->addChildren(moon_geom);

    ////////// Mars //////////
    std::shared_ptr<Node> ares = std::make_shared<Node>("ares", scene_root,
                                                           glm::translate({}, glm::fvec3{2.0f, 0.0f, 0.0f}));
    std::shared_ptr<GeometryNode> mars_geom = std::make_shared<GeometryNode>("mars_geom", ares,
                                                                             glm::scale({}, glm::fvec3{0.04f,0.04f,0.04f }),
                                                                             sphere_model);
    scene_root->addChildren(ares);
    ares->addChildren(mars_geom);

    ////////// Jupiter //////////
    std::shared_ptr<Node> zeus = std::make_shared<Node>("zeus", scene_root,
                                                        glm::translate({}, glm::fvec3{2.5f,0.0f,0.0f}));
    std::shared_ptr<GeometryNode> jupiter_geom = std::make_shared<GeometryNode>("jupiter_geom", zeus,
                                                                             glm::scale({}, glm::fvec3{0.2f,0.2f,0.2f }),
                                                                             sphere_model);
    scene_root->addChildren(zeus);
    zeus->addChildren(jupiter_geom);

    ////////// Saturn //////////
    std::shared_ptr<Node> cronos = std::make_shared<Node>("cronos", scene_root,
                                                        glm::translate({}, glm::fvec3{2.7f,0.0f,0.0f}));
    std::shared_ptr<GeometryNode> saturn_geom = std::make_shared<GeometryNode>("saturn_geom", cronos,
                                                                                glm::scale({}, glm::fvec3{0.15f,0.15f,0.15f }),
                                                                                sphere_model);
    scene_root->addChildren(cronos);
    cronos->addChildren(saturn_geom);

    ////////// Uranus //////////
    std::shared_ptr<Node> uranos = std::make_shared<Node>("uranos", scene_root,
                                                          glm::translate({}, glm::fvec3{3.0f,0.0f,0.0f}));
    std::shared_ptr<GeometryNode> uranus_geom = std::make_shared<GeometryNode>("uranus_geom", uranos,
                                                                               glm::scale({}, glm::fvec3{0.1f,0.1f,0.1f }),
                                                                               sphere_model);
    scene_root->addChildren(uranos);
    uranos->addChildren(uranus_geom);

    ////////// Neptune //////////
    std::shared_ptr<Node> poseidon = std::make_shared<Node>("poseidon", scene_root,
                                                           glm::translate({}, glm::fvec3{3.2f,0.0f,0.0f}));
    std::shared_ptr<GeometryNode> neptune_geom = std::make_shared<GeometryNode>("neptune_geom", poseidon,
                                                                               glm::scale({}, glm::fvec3{0.1f,0.1f,0.1f}),
                                                                               sphere_model);
    scene_root->addChildren(poseidon);
    poseidon->addChildren(neptune_geom);

    ////////// Pluto //////////
    std::shared_ptr<Node> hades = std::make_shared<Node>("hades", scene_root,
                                                            glm::translate({}, glm::fvec3{3.5f,0.0f,0.0f}));
    std::shared_ptr<GeometryNode> pluto_geom = std::make_shared<GeometryNode>("pluto_geom", hades,
                                                                                glm::scale({}, glm::fvec3{0.012f,0.012f,0.012f}),
                                                                                sphere_model);
    scene_root->addChildren(hades);
    hades->addChildren(pluto_geom);

    ////////// Dionysus(Camera) ////////// (god of theater, so he kinda fits the camera job)
    std::shared_ptr<CameraNode> dionysus = std::make_shared<CameraNode>("dionysus", true, true,
                                                                      m_view_projection_, scene_root);
    scene_root->addChildren(dionysus);

}

///////////////////////////// callback functions for window events /////////////////////////////////////////////////////
// handling key input, press key once for single step, keep key pressed for lasting movement
void ApplicationSolar::keyCallback(int key, int action, int mods) {

    // moving camera forward or moving camera backwards (W,S)
    if (key == GLFW_KEY_W  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, -0.1f});
      uploadView();
    }
    else if (key == GLFW_KEY_S  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, 0.1f});
      uploadView();
    }

    // moving camera to the right or left handside (A,D)
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{-0.1f,0.0f,0.0f});
        uploadView();
    } else if(key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.1f,0.0f,0.0f});
        uploadView();
    }

    // moving camera up and down (C,V)
    if (key == GLFW_KEY_V && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f,0.1f,0.0f});
        uploadView();
    } else if(key == GLFW_KEY_C && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f,-0.1f,0.0f});
        uploadView();
    }

    // rotate camera in the right or left handside
    if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        m_view_transform = glm::rotate(m_view_transform, glm::radians(0.5f), glm::vec3{0.0f, 1.0f, 0.0f});
        uploadView();
    } else if(key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        m_view_transform = glm::rotate(m_view_transform, glm::radians(-0.5f), glm::vec3{0.0f, 1.0f, 0.0f});
        uploadView();
    }
}

//handle delta mouse movement input
void ApplicationSolar::mouseCallback(double pos_x, double pos_y) {
    // mouse handling
    m_view_transform = glm::rotate(m_view_transform, glm::radians(-(float) pos_x / 50), glm::vec3{0.0f, 1.0f, 0.0f});
    m_view_transform = glm::rotate(m_view_transform, glm::radians(-(float) pos_y / 50), glm::vec3{1.0f, 0.0f, 0.0f});
    uploadView();
}

//handle resizing
void ApplicationSolar::resizeCallback(unsigned width, unsigned height) {
  // recalculate projection matrix for new aspect ration
  m_view_projection_ = utils::calculate_projection_matrix(float(width) / float(height));
  // upload new projection matrix
  uploadProjection();
}


// exe entry point
int main(int argc, char* argv[]) {
  Application::run<ApplicationSolar>(argc, argv, 3, 2);
}