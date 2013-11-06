//
//  ScreenPickExample.h
//  ExampleApp
//

#ifndef __ExampleApp__ScreenPickExample__
#define __ExampleApp__ScreenPickExample__

#include "IExample.h"
#include "Rendering.h"
#include "Terrain.h"
#include "Camera.h"
#include "DebugRendering.h"

namespace Examples
{
    /*!
     *  ScreenPickExample demonstrates projecting a ray through the camera origin and
     *  a screen pixel when the touch screen is tapped. If the ray intersects the Earth
     *  sphere, a red marker is drawn at the point on the terrain radially above the 
     *  intersection point. The example is similar to ScreenUnprojectExample, but uses
     *  helper method Eegeo::Camera::CameraHelpers::TryGetScreenPickIntersectionWithEarthCentredSphere
     */
    class ScreenPickExample : public IExample
    {
    private:
        Eegeo::DebugRendering::SphereMesh* m_sphere;
        Eegeo::Rendering::RenderContext& m_renderContext;
        Eegeo::Camera::ICameraProvider& m_cameraProvider;
        Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
        
    public:
        ScreenPickExample(Eegeo::Rendering::RenderContext& renderContext,
                               Eegeo::Camera::ICameraProvider& cameraProvider,
                               Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider);
        virtual ~ScreenPickExample();
        void Start();
        void Update();
        void Draw();
        void Suspend();
        
        bool Event_TouchDown(const AppInterface::TouchData& data);
    };
}

#endif /* defined(__ExampleApp__ScreenPickExample__) */
