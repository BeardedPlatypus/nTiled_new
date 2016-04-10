#pragma once

// ----------------------------------------------------------------------------
//  nTiled headers
// ----------------------------------------------------------------------------
#include "ForwardShader.h"
#include "pipeline\light-management\tiled\TiledLightManager.h"
#include "pipeline\light-management\tiled\BoxProjector.h"

namespace nTiled {
namespace pipeline {

class ForwardTiledShader : public ForwardShader {
public:
  ForwardTiledShader(ForwardShaderId shader_id,
                     const std::string& path_vertex_shader,
                     const std::string& path_fragment_shader,
                     const world::World& world,
                     const state::View& view,
                     glm::uvec2 tile_size);

  virtual void render() override;

protected:
  // --------------------------------------------------------------------------
  // LightManagement Functions
  // --------------------------------------------------------------------------
  /*! Sphere projector of this ForwardTiledShader */
  const BoxProjector projector;
  /*! TiledLightManager of this ForwardTiledShader */
  TiledLightManager light_manager;

  // --------------------------------------------------------------------------
  //  openGL LightManagement datastructures
  // --------------------------------------------------------------------------
  /*!
  GLuint pointer to the Shader Storage Buffer Object storing
  the light grid of this ForwardTiledShader
  */
  GLuint light_grid_buffer;
  /*!
  GLuint pointer to the Shader Storage Buffer Object storing
  the light index of this ForwardTiledShader
  */
  GLuint light_index_buffer;
};

} // pipeline
} // nTiled