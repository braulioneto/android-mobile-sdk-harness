#include "EnvironmentNotifierExample.h"
#include "CubeMapCellInfo.h"
#include "Logger.h"

#define SPHERE_HEIGHT_ABOVE_SEA 10.0

namespace Examples
{
    //EnvironmentNotifierExample//
    EnvironmentNotifierExample::EnvironmentNotifierExample(Eegeo::Rendering::RenderContext& renderContext,
                                                           Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming)
    :renderContext(renderContext)
    ,terrainStreaming(terrainStreaming)
    ,observer(NULL)
    {
    }
    
    void EnvironmentNotifierExample::Start()
    {
        observer = new EnvironmentNotifierExampleTerrainStreamObserver(renderContext, renderables);
        terrainStreaming.AddStreamingObserver(observer);
    }
    
    void EnvironmentNotifierExample::Suspend()
    {
        terrainStreaming.RemoveStreamingObserver(observer);
        delete observer;
        observer = NULL;
    }
    
    void EnvironmentNotifierExample::Update()
    {
    }
    
    
    void EnvironmentNotifierExample::Draw()
    {
        //draw all the spheres
        for(std::map<Eegeo::Streaming::MortonKeyLong, Eegeo::DebugRendering::SphereMesh*>::iterator
            it = renderables.begin(); it != renderables.end(); ++ it)
        {
            Eegeo::DebugRendering::SphereMesh& mesh = *(*it).second;
            mesh.Draw(renderContext);
        }
    }
    
    
    //EnvironmentNotifierExampleTerrainStreamObserver///
    void EnvironmentNotifierExampleTerrainStreamObserver::AddSphere(const Eegeo::Streaming::MortonKeyLong& key)
    {
        Eegeo::Space::CubeMap::CubeMapCellInfo cellInfo(key);
        const Eegeo::dv2& resourceQuadtreeCellCenter = cellInfo.GetFaceCentre();
        Eegeo::dv3 worldSpaceCellCenter = Eegeo::Space::CubeMap::FacePointToWorld(cellInfo.GetFaceIndex(),
                                                                                  resourceQuadtreeCellCenter,
                                                                                  Eegeo::Space::EarthConstants::CubeSideLengthHalf);
        
        
        Eegeo::dv3 up = worldSpaceCellCenter.Norm();
        Eegeo::dv3 spherePosition = Eegeo::dv3::Scale(up, Eegeo::Space::EarthConstants::Radius + SPHERE_HEIGHT_ABOVE_SEA);
        
        Eegeo::v3 color(1.f, 0.f, 1.f);
        
        Eegeo::DebugRendering::SphereMesh* sphere = new Eegeo::DebugRendering::SphereMesh(
                                                                                          renderContext,
                                                                                          20.0f,
                                                                                          16, 16,
                                                                                          spherePosition,
                                                                                          NULL,
                                                                                          color
                                                                                          );
        sphere->Tesselate();
        
        renderables.insert(std::make_pair(key,sphere));
    }
    
    void EnvironmentNotifierExampleTerrainStreamObserver::AddedStreamingResourceToSceneGraph(const Eegeo::Streaming::MortonKeyLong& key)
    {
    	EXAMPLE_LOG("Adding Terrain Resource :: %s\n", key.ToString().c_str());
        AddSphere(key);
    }
    
    void EnvironmentNotifierExampleTerrainStreamObserver::RemovedStreamingResourceFromSceneGraph(const Eegeo::Streaming::MortonKeyLong& key)
    {
    	EXAMPLE_LOG("Removing Terrain Resource :: %s\n", key.ToString().c_str());
        renderables.erase(key);
    }
}
