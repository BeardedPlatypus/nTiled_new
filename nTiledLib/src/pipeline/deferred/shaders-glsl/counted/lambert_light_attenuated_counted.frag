#version 440

#define NUM_LIGHTS 3

// Fragment Output Buffers
// -----------------------------------------------------------------------------
layout (location=0) out uint light_calculations;

// Variable Definitions
// -----------------------------------------------------------------------------
// Structs
/*! Light Struct
 *
 * position: position of this light
 * intensity: the intensity (colour) with which this light is emitting
 * radius: the radius of the light sphere of this light
 * is_emitting: whether this light is emitting or not
 */
struct Light {
    vec4 position;    // 4
    vec3 intensity;   // 3
    float radius;     // 1
    int is_emitting;  
};

/*! GeometryParam for Lambert Shading.
 *
 *  position: the position at the fragment in the same coordinate system
              as the light
 *  normal  : the normal at the fragment.
 *  colour  : the colour at the fragment.
 */
struct GeometryParam {
    vec4 position;
    vec3 normal;
    vec3 colour;
};

// -----------------------------------------------------------------------------
layout (std140) uniform LightBlock {
    Light lights[NUM_LIGHTS];
};

// -----------------------------------------------------------------------------
// MRT texture samplers
layout(binding = 0) uniform sampler2D diffuse_tex;
layout(binding = 1) uniform sampler2D normal_tex;
layout(binding = 2) uniform sampler2D depth_tex;

// -----------------------------------------------------------------------------
// Position definition
uniform mat4 perspective_matrix;
uniform mat4 inv_perspective_matrix;

uniform vec4 viewport;
uniform vec2 depth_range;

// Function Definitions
// -----------------------------------------------------------------------------
/*!
 * Compute lambert shading for the attenuated light.
 *
 * param:
 *     light (Light): light of this computeLight
 *     param (GeometryParam): struct containing the geometry parameters
 *                            needed for the light computation
 *                            - position: position of the fragment in the
 *                                        same coordinate system as the
 *                                        light position.
 *                            - normal: the normal (normalised) at the
 *                                      fragment.
 *                            - colour: the colour of this fragment
 */ 
vec3 computeLight(Light light,
                  GeometryParam param) {
    vec3 L = vec3(light.position - param.position);
    float d = length(L);

    if (d < light.radius) {
        vec3 light_direction = L / d;

        // compute light attenuation
        float attenuation = clamp(1.0 - ( d / light.radius ),
                                  0.0f,
                                  1.0f);
        attenuation *= attenuation;

        // compute lambert for this light
        float cos_angular_incidence = clamp(dot(param.normal, light_direction),
                                            0.0f,
                                            1.0f);
        return (param.colour *
                light.intensity *
                cos_angular_incidence * attenuation);
    } else {
        return vec3(0.0);
    }
}

/*!
 * Compute the texture coordinates of this fragment.
 */
vec2 calcTextureCoordinates() {
    return gl_FragCoord.xy / viewport.zw;
}

/*!
 * Compute the camera coordinates of this fragment given the texture coordinates
 *
 * param:
 *     tex_coords (vec2): the texture coordinates of this fragment.
 */
vec4 getCameraCoordinates(in vec2 tex_coords) {
    // Define the normalized device coordinates
    vec3 device;
    device.xy = (2.0f * ((gl_FragCoord.xy - vec2(0.5f, 0.5f) - viewport.xy) /
                          viewport.zw)) - 1.0f;
    device.z = 2.0f * texture(depth_tex, tex_coords).x - 1.0f;

    // Calculate actual coordinates
    vec4 raw_coords = inv_perspective_matrix * vec4(device, 1.0f);
    vec4 coords = raw_coords / raw_coords.w;

    return coords;
}


// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------
void main() {
    vec2 tex_coords = calcTextureCoordinates();
    vec3 diffuse_colour = texture(diffuse_tex, tex_coords).xyz;
    
    if (diffuse_colour.rgb == vec3(0.0f)) {
        light_calculations = 0;
    } else {
        light_calculations = NUM_LIGHTS;
    }   
}
