//
//  PinsExample.h
//  ExampleApp
//

#ifndef __ExampleApp__PinsExample__
#define __ExampleApp__PinsExample__

#include "IExample.h"

#include "Rendering.h"
#include "Camera.h"
#include "ITextureFileLoader.h"

#include "PinsModule.h"
#include <string>

namespace Examples
{
    /*!
     *  PinsExample demonstrates the display of Pins within the 3D world.
     *  Pins are placed relative to the underlying terrain and displayed as Sprites which always face the camera.
     *  This example also demonstrates how Pins can be selected by testing against their screen bounds.
     *  Pin add / remove functionality is demonstrated by adding / removing pin 0 every 3 seconds.
     */
    class PinsExample : public IExample
    {
    private:
        Eegeo::Rendering::ITexturePageLayout* m_pPinIconsTexturePageLayout;
        Eegeo::Helpers::GLHelpers::TextureInfo m_pinIconsTexture;
        Eegeo::Pins::PinsModule* m_pPinsModule;
        std::string m_pin0UserData;
        std::string m_pin1UserData;
        std::string m_pin2UserData;
        std::string m_pin3UserData;

        float m_addRemoveTimer;
        Eegeo::Pins::Pin* m_pPin0;

    public:
        PinsExample(
                    Eegeo::Helpers::ITextureFileLoader& textureLoader,
                    Eegeo::Rendering::EnvironmentMaterialController& environmentMaterialController,
                    Eegeo::Rendering::GlBufferPool& glBufferPool,
                    Eegeo::Rendering::ItemRenderer& itemRenderer,
                    const Eegeo::Camera::ICameraProvider& cameraProvider,
                    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider
                    );
        virtual ~PinsExample();
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();

        bool Event_TouchDown(const AppInterface::TouchData& data);

    private:
        void CreateExamplePins();
        void AddRemovePin0();
    };
}

#endif /* defined(__ExampleApp__PinsExample__) */
