/*
 * PinOverModelExample.h
 *
 *  Created on: Mar 7, 2014
 *      Author: kimbleoperations
 */

#ifndef PINOVERMODELEXAMPLE_H_
#define PINOVERMODELEXAMPLE_H_

#include "IExample.h"

#include "Rendering.h"
#include "Camera.h"
#include "ITextureFileLoader.h"
#include "IFileIO.h"
#include "PinsModule.h"
#include <string>
#include "IAsyncTextureRequestor.h"
#include "GlobalFogging.h"
#include "Model.h"
#include "NullMaterial.h"
#include "IRenderableFilter.h"
#include "RenderableBase.h"
#include "NullMaterial.h"

namespace Examples
{
    class PinOverModelExample : public IExample
    {
    private:

        class MyModelRenderable : public Eegeo::Rendering::RenderableBase
        {
            Eegeo::Model& m_model;
            Eegeo::Rendering::RenderContext& m_renderContext;
            Eegeo::Lighting::GlobalFogging& m_globalFogging;

        public:
            MyModelRenderable(Eegeo::Model& model,
               Eegeo::Rendering::RenderContext& renderContext,
               Eegeo::Lighting::GlobalFogging& globalFogging,
               Eegeo::Rendering::Materials::NullMaterial& nullMat);

            void Render(Eegeo::Rendering::GLState& glState) const;
        };

        class MyRenderableFilter : public Eegeo::Rendering::IRenderableFilter
        {
            Eegeo::Rendering::RenderableBase& m_renderable;
        public:
            MyRenderableFilter(Eegeo::Rendering::RenderableBase& renderable);

            void EnqueueRenderables(Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
        };

        Eegeo::Rendering::ITexturePageLayout* m_pPinIconsTexturePageLayout;
        Eegeo::Helpers::GLHelpers::TextureInfo m_pinIconsTexture;
        Eegeo::Pins::PinsModule* m_pPinsModule;
        std::string m_pin0UserData;

        Eegeo::Pins::Pin* m_pPin0;

        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Helpers::IFileIO& fileIO;
        Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor;
        Eegeo::Lighting::GlobalFogging& globalFogging;
        Eegeo::Rendering::RenderableFilters& renderableFilters;

        Eegeo::Model* pModel;
        Eegeo::Rendering::Materials::NullMaterial& nullMat;

        MyModelRenderable* m_pMyModelRenderable;
        MyRenderableFilter* m_pMyRenderableFilter;

    public:
        PinOverModelExample(
                            Eegeo::Helpers::ITextureFileLoader& textureLoader,
                            Eegeo::Rendering::GlBufferPool& glBufferPool,
                            Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                            Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                            Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                            Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                            Eegeo::Rendering::RenderableFilters& renderableFilters,
                            const Eegeo::Camera::ICameraProvider& cameraProvider,
                            Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                            Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                            Eegeo::Rendering::RenderContext& renderContext,
                            Eegeo::Helpers::IFileIO& fileIO,
                            Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
                            Eegeo::Lighting::GlobalFogging& fogging,
                            Eegeo::Rendering::Materials::NullMaterial& nullMat
                            );
        virtual ~PinOverModelExample();
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();

    private:
        void CreateExamplePins();
    };
}

#endif /* PINOVERMODELEXAMPLE_H_ */
