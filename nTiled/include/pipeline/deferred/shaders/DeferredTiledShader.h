/*! @file DeferredTiledShader.h
 *  @brief DeferredTiledShader.h contains the definition of the 
 *         DeferredTiledShader which implements a Deferred rendering 
 *         approach in combination with Tiled shading.
 */
#pragma once

// ----------------------------------------------------------------------------
//  nTiled headers
// ----------------------------------------------------------------------------
#include "DeferredShader.h"
#include "pipeline\light-management\tiled\TiledLightManager.h"
#include "pipeline\light-management\tiled\BoxProjector.h"

namespace nTiled {
namespace pipeline {

/*! @brief DeferrerdTiledShader implements the Tiled Shading algorithm 
 *         within a Deferred pipeline.
 *         It inherits from the DeferredShader.
 */
class DeferredTiledShader : public DeferredShader {
public:
  /*! @brief Construct a new DeferredTiledShader with the given parameters
   * 
   * @param shader_id The DeferredShaderId of this new DeferredShader
   * @param path_geometry_pass_vertex_shader Path to the geometry pass 
   *                                         vertex shader file.
   * @param path_geometry_pass_fragment_shader Path to the  geometry pass 
   *                                           fragment shader file.
   * @param path_light_pass_vertex_shader Path to the light pass vertex 
   *                                      shader file.
   * @param path_light_pass_fragment_shader Path to the light pass 
   *                                        fragment shader file.
   * @param world Reference to the world containing the objects and lights this 
   *              Shader observes
   * @param view Reference to the View and Camera this shader uses to shade.
   * @param p_output_buffer openGL pointer to the output buffer to which
   *                        this DeferredTiledShader should render.
   * @param tile_size The tilesize in pixels the Tiled Shading algorithm
   *                  will use.
   * @param light_manager_builder Reference to the TiledLightManagerBuilder
   *                              this DeferredTiledShader will use to 
   *                              obtain a TiledLightManager.
   */
  DeferredTiledShader(DeferredShaderId shader_id,
                      const std::string& path_geometry_pass_vertex_shader,
                      const std::string& path_geometry_pass_fragment_shader,
                      const std::string& path_light_pass_vertex_shader,
                      const std::string& path_light_pass_fragment_shader,
                      const world::World& world,
                      const state::View& view,
                      GLint p_output_buffer,
                      glm::uvec2 tile_size,
                      const TiledLightManagerBuilder& light_manager_builder);

  virtual void renderGeometryPass() override;
  virtual void renderLightPass() override;

protected:
  // --------------------------------------------------------------------------
  // render sub-functions
  // --------------------------------------------------------------------------
  /*! @brief Load the light grid for this DeferredTiledShader. */
  virtual void loadLightGrid();

  // --------------------------------------------------------------------------
  // LightManagement Functions
  // --------------------------------------------------------------------------
  /*! @brief Sphere projector of this DeferredTiledShader */
  const BoxProjector projector;
  /*! @brief TiledLightManager of this DeferredTiledShader */
  TiledLightManager* p_light_manager;

  // --------------------------------------------------------------------------
  //  openGL LightManagement datastructures
  // --------------------------------------------------------------------------
  /*! @brief GLuint pointer to the Shader Storage Buffer Object storing
   *         the light grid of this DeferredTiledShader
   */
  GLuint light_grid_buffer;

  /*! @brief GLuint pointer to the Shader Storage Buffer Object storing
   *         the light index of this DeferredTiledShader
   */
  GLuint light_index_buffer;
};

}
}
