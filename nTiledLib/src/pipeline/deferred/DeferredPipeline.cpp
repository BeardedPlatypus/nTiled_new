#include "pipeline\deferred\DeferredPipeline.h"

// ----------------------------------------------------------------------------
//  nTiled headers
// ----------------------------------------------------------------------------
#include "pipeline\deferred\shaders\DeferredAttenuatedShader.h"
#include "pipeline\deferred\shaders\DeferredTiledShader.h"
#include "pipeline\deferred\shaders\DeferredClusteredShader.h"
#include "pipeline\deferred\shaders\DeferredHashedShader.h"


// Path defines
#define VERT_PATH_GEO std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/lambert_gbuffer.vert")
#define FRAG_PATH_GEO std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/lambert_gbuffer.frag")

#define VERT_PATH_LIGHT std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/lambert_light.vert")

#define FRAG_PATH_LIGHT_ATTENUATED std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/lambert_light_attenuated.frag")
#define FRAG_PATH_LIGHT_TILED std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/lambert_light_tiled.frag")
#define FRAG_PATH_LIGHT_CLUSTERED std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/lambert_light_clustered.frag")
#define FRAG_PATH_LIGHT_HASHED std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/lambert_light_hashed.frag")

#define FRAG_PATH_LIGHT_ATTENUATED_VC std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/visualise_calculations/lambert_light_attenuated.frag")
#define FRAG_PATH_LIGHT_TILED_VC std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/visualise_calculations/lambert_light_tiled.frag")
#define FRAG_PATH_LIGHT_CLUSTERED_VC std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/visualise_calculations/lambert_light_clustered.frag")
#define FRAG_PATH_LIGHT_HASHED_VC std::string("../nTiledLib/src/pipeline/deferred/shaders-glsl/visualise_calculations/lambert_light_hashed.frag")

namespace nTiled {
namespace pipeline {

DeferredPipeline::DeferredPipeline(state::State& state) : Pipeline(state) {
}

DeferredPipeline::~DeferredPipeline() {
  delete this->p_deferred_shader;
}

void DeferredPipeline::initialiseShaders() {
  this->constructShader();
}

void DeferredPipeline::render() {
  this->p_deferred_shader->render();
}

void DeferredPipeline::setOutputBuffer(GLint p_output_buffer) {
  Pipeline::setOutputBuffer(p_output_buffer);
  this->p_deferred_shader->setOutputBuffer(p_output_buffer);
}

void DeferredPipeline::constructShader() {
  DeferredShaderId id = this->state.shading.deferred_shader_id;
  if (!this->state.view.display_light_calculations) {
    if (id == DeferredShaderId::DeferredAttenuated) {
      this->p_deferred_shader = new DeferredAttenuatedShader(
        DeferredShaderId::DeferredAttenuated,
        VERT_PATH_GEO,
        FRAG_PATH_GEO,
        VERT_PATH_LIGHT,
        FRAG_PATH_LIGHT_ATTENUATED,
        *(this->state.p_world),
        this->state.view,
        this->output_buffer);
    } else if (id == DeferredShaderId::DeferredTiled) {
      this->p_deferred_shader = new DeferredTiledShader(
        DeferredShaderId::DeferredTiled,
        VERT_PATH_GEO,
        FRAG_PATH_GEO,
        VERT_PATH_LIGHT,
        FRAG_PATH_LIGHT_TILED,
        *(this->state.p_world),
        this->state.view,
        this->output_buffer,
        this->state.shading.tile_size,
        TiledLightManagerBuilder());
    } else if (id == DeferredShaderId::DeferredClustered) {
      this->p_deferred_shader = new DeferredClusteredShader(
        DeferredShaderId::DeferredClustered,
        VERT_PATH_GEO,
        FRAG_PATH_GEO,
        VERT_PATH_LIGHT,
        FRAG_PATH_LIGHT_CLUSTERED,
        *(this->state.p_world),
        this->state.view,
        this->output_buffer,
        this->state.shading.tile_size,
        ClusteredLightManagerBuilder());
    } else if (id == DeferredShaderId::DeferredHashed) {
      this->p_deferred_shader = new DeferredHashedShader(
        DeferredShaderId::DeferredHashed,
        VERT_PATH_GEO,
        FRAG_PATH_GEO,
        VERT_PATH_LIGHT,
        FRAG_PATH_LIGHT_HASHED,
        *(this->state.p_world),
        this->state.view,
        this->output_buffer,
        hashed::HashedLightManagerBuilder(),
        this->state.shading.hashed_config);
    } else {
      throw std::runtime_error(std::string("Unsupported shader"));
    }
  } else {
    if (id == DeferredShaderId::DeferredAttenuated) {
      this->p_deferred_shader = new DeferredAttenuatedShader(
        DeferredShaderId::DeferredAttenuated,
        VERT_PATH_GEO,
        FRAG_PATH_GEO,
        VERT_PATH_LIGHT,
        FRAG_PATH_LIGHT_ATTENUATED_VC,
        *(this->state.p_world),
        this->state.view,
        this->output_buffer);
    } else if (id == DeferredShaderId::DeferredTiled) {
      this->p_deferred_shader = new DeferredTiledShader(
        DeferredShaderId::DeferredTiled,
        VERT_PATH_GEO,
        FRAG_PATH_GEO,
        VERT_PATH_LIGHT,
        FRAG_PATH_LIGHT_TILED_VC,
        *(this->state.p_world),
        this->state.view,
        this->output_buffer,
        this->state.shading.tile_size,
        TiledLightManagerBuilder());
    } else if (id == DeferredShaderId::DeferredClustered) {
      this->p_deferred_shader = new DeferredClusteredShader(
        DeferredShaderId::DeferredClustered,
        VERT_PATH_GEO,
        FRAG_PATH_GEO,
        VERT_PATH_LIGHT,
        FRAG_PATH_LIGHT_CLUSTERED_VC,
        *(this->state.p_world),
        this->state.view,
        this->output_buffer,
        this->state.shading.tile_size,
        ClusteredLightManagerBuilder());
    } else if (id == DeferredShaderId::DeferredHashed) {
      this->p_deferred_shader = new DeferredHashedShader(
        DeferredShaderId::DeferredHashed,
        VERT_PATH_GEO,
        FRAG_PATH_GEO,
        VERT_PATH_LIGHT,
        FRAG_PATH_LIGHT_HASHED_VC,
        *(this->state.p_world),
        this->state.view,
        this->output_buffer,
        hashed::HashedLightManagerBuilder(),
        this->state.shading.hashed_config);
    } else {
      throw std::runtime_error(std::string("Unsupported shader"));
    }
  }
}

} // pipeline
} // nTiled