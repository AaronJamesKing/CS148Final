#include "common/Rendering/Renderer/Photon/PhotonMappingRenderer.h"
#include "common/Scene/Scene.h"
#include "common/Sampling/ColorSampler.h"
#include "common/Scene/Lights/Light.h"
#include "common/Scene/Geometry/Primitives/Primitive.h"
#include "common/Scene/Geometry/Mesh/MeshObject.h"
#include "common/Rendering/Material/Material.h"
#include "common/Intersection/IntersectionState.h"
#include "common/Scene/SceneObject.h"
#include "common/Scene/Geometry/Mesh/MeshObject.h"
#include "common/Rendering/Material/Material.h"
#include "glm/gtx/component_wise.hpp"

#include <math.h>

#define VISUALIZE_PHOTON_MAPPING 1

PhotonMappingRenderer::PhotonMappingRenderer(std::shared_ptr<class Scene> scene, std::shared_ptr<class ColorSampler> sampler):
    BackwardRenderer(scene, sampler), 
    diffusePhotonNumber(1000000),
    maxPhotonBounces(1000)
{
    srand(static_cast<unsigned int>(time(NULL)));
}

void PhotonMappingRenderer::InitializeRenderer()
{
    // Generate Photon Maps
    GenericPhotonMapGeneration(diffuseMap, diffusePhotonNumber);
    diffuseMap.optimise();
}

void PhotonMappingRenderer::GenericPhotonMapGeneration(PhotonKdtree& photonMap, int totalPhotons)
{
    float totalLightIntensity = 0.f;
    size_t totalLights = storedScene->GetTotalLights();
    for (size_t i = 0; i < totalLights; ++i) {
        const Light* currentLight = storedScene->GetLightObject(i);
        if (!currentLight) {
            continue;
        }
        totalLightIntensity += glm::length(currentLight->GetLightColor());
    }

    // Shoot photons -- number of photons for light is proportional to the light's intensity relative to the total light intensity of the scene.
    for (size_t i = 0; i < totalLights; ++i) {
        const Light* currentLight = storedScene->GetLightObject(i);
        if (!currentLight) {
            continue;
        }

        const float proportion = glm::length(currentLight->GetLightColor()) / totalLightIntensity;
        const int totalPhotonsForLight = static_cast<const int>(proportion * totalPhotons);
        const glm::vec3 photonIntensity = currentLight->GetLightColor() / static_cast<float>(totalPhotonsForLight);
        for (int j = 0; j < totalPhotonsForLight; ++j) {
            Ray photonRay;
            std::vector<char> path;
            path.push_back('L');
            currentLight->GenerateRandomPhotonRay(photonRay);
            TracePhoton(photonMap, &photonRay, photonIntensity, path, 1.f, maxPhotonBounces);
        }
    }
}

void PhotonMappingRenderer::TracePhoton(PhotonKdtree& photonMap, Ray* photonRay, glm::vec3 lightIntensity, std::vector<char>& path, float currentIOR, int remainingBounces)
{
    /*
     * Assignment 8 TODO: Trace a photon into the scene and make it bounce.
     *    
     *    How to insert a 'Photon' struct into the photon map.
     *        Photon myPhoton;
     *        ... set photon properties ...
     *        photonMap.insert(myPhoton);
     */
    
    // REMAINING BOUNCES
    if (remainingBounces < 0) return;

    assert(photonRay);
    IntersectionState state(0, 0);
    state.currentIOR = currentIOR;
    
    // TRACE
    bool didTrace = storedScene->Trace(photonRay, &state);
    if (!didTrace) return;
    
    // STORE OR SCATTER
    if (path.size() > 1){
        // STORE
        Photon photon;
        photon.position = state.intersectionRay.GetRayPosition(state.intersectionT);
        photon.intensity = lightIntensity;
        photon.toLightRay.SetRayDirection(state.intersectionRay.GetRayDirection() * glm::vec3(-1.0f));
        photonMap.insert(photon);
    }
    
    // SCATTER
    const MeshObject* hitMeshObject = state.intersectedPrimitive->GetParentMeshObject();
    const Material* hitMaterial = hitMeshObject->GetMaterial();
    glm::vec3 diff = hitMaterial->GetBaseDiffuseReflection();
    
    // ROULETTE
    float p_r = fmax(fmax(diff.x, diff.y), diff.z);
    float rando = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (rando >= p_r) return;
    
    // HEMISPHERE SAMPLE
    float u1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float u2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    
    float r = std::sqrt(u1);
    float theta = 2.0f * PI * u2;
    
    float x = r * cos(theta);
    float y = r * sin(theta);
    float z = sqrtf(1.0f - u1);
    
    glm::vec3 sampleVector = glm::normalize(glm::vec3(x, y, z));
    
    // HEMISPHERE RAY TRANSFORMATION
    glm::vec3 n = state.ComputeNormal();
    
    glm::vec3 unitVector;
    if (1.0f - fabs(glm::dot(n, glm::vec3(1, 0, 0))) > 0.001f){
        unitVector = glm::vec3(1.f, 0.f, 0.f);
    }
    else if (1.0f - fabs(glm::dot(n, glm::vec3(0, 1, 0))) > 0.001f){
        unitVector = glm::vec3(0.f, 1.f, 0.f);
    }
    else {
        unitVector = glm::vec3(0.f, 0.f, 1.f);
    }
    
    glm::vec3 t = glm::cross(n, unitVector);
    glm::vec3 b = glm::cross(n, t);
    
    glm::mat3 matrix = glm::mat3(t, b, n);
    glm::vec3 direction = matrix * sampleVector;
    
    //state.intersectionRay.SetRayDirection(direction);
    Ray nextRay = Ray(state.intersectionRay.GetRayPosition(state.intersectionT), direction);
    path.push_back(0);
    TracePhoton(photonMap, &nextRay, lightIntensity, path, currentIOR, remainingBounces - 1);
    
}

glm::vec3 PhotonMappingRenderer::ComputeSampleColor(const struct IntersectionState& intersection, const class Ray& fromCameraRay) const
{
    glm::vec3 finalRenderColor = BackwardRenderer::ComputeSampleColor(intersection, fromCameraRay);
#if VISUALIZE_PHOTON_MAPPING
    Photon intersectionVirtualPhoton;
    intersectionVirtualPhoton.position = intersection.intersectionRay.GetRayPosition(intersection.intersectionT);

    std::vector<Photon> foundPhotons;
    diffuseMap.find_within_range(intersectionVirtualPhoton, 0.003f, std::back_inserter(foundPhotons));
    if (!foundPhotons.empty()) {
        finalRenderColor += glm::vec3(1.f, 0.f, 0.f);
    }
#endif
    return finalRenderColor;
}

void PhotonMappingRenderer::SetNumberOfDiffusePhotons(int diffuse)
{
    diffusePhotonNumber = diffuse;
}
