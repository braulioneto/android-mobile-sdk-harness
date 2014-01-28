//
//  PinsExample.cpp
//  ExampleApp
//

#include "PinsExample.h"
#include "RegularTexturePageLayout.h"
#include "Logger.h"

namespace Examples
{
    PinsExample::PinsExample(
                            Eegeo::Helpers::ITextureFileLoader& textureLoader,
                            Eegeo::Rendering::EnvironmentMaterialController& environmentMaterialController,
                            Eegeo::Rendering::GlBufferPool& glBufferPool,
                            Eegeo::Rendering::ItemRenderer& itemRenderer,
                            const Eegeo::Camera::ICameraProvider& cameraProvider,
                            Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider
                            )
    : m_pin0UserData("Pin Zero(0) User Data")
    , m_pin1UserData("Pin One(1) User Data")
    , m_pin2UserData("Pin Two(2) User Data")
    , m_pin3UserData("Pin Three(3) User Data")
    , m_addRemoveTimer(0.0f)
    , m_pPin0(NULL)
    {
    	textureLoader.LoadTexture(m_pinIconsTexture, "PinIconTexturePage.png", true);
        Eegeo_ASSERT(m_pinIconsTexture.textureId != 0);

        // This example uses a texture page containing 2 x 2 icons.
        // Increase the following number to use a texture page containing more icons
        // (e.g. 3 for a page containing 3 x 3 icons)
        int numberOfTilesAlongEachAxisOfTexturePage = 2;
        m_pPinIconsTexturePageLayout = Eegeo_NEW(Eegeo::Rendering::RegularTexturePageLayout)(numberOfTilesAlongEachAxisOfTexturePage);

        // The following values specify the size and shape of the Pins within the 3D world.
        int spriteWidthInMetres = 100;
        int spriteHeightInMetres = 100;

        // N.B. The implementation for PinModule is given in PinModule.h as a guide for Apps that
        // require an alternate configuration of the various Pin related components.
        m_pPinsModule = Eegeo_NEW(Eegeo::Pins::PinsModule)(
                                                           m_pinIconsTexture.textureId,
                                                           *m_pPinIconsTexturePageLayout,
                                                           environmentMaterialController,
                                                           glBufferPool,
                                                           itemRenderer,
                                                           cameraProvider,
                                                           terrainHeightProvider,
                                                           spriteWidthInMetres,
                                                           spriteHeightInMetres
                                                           );

        CreateExamplePins();
    }

    PinsExample::~PinsExample()
    {
        // Delete the PinsModule and all of its underlying components.
        // N.B. Deleting the PinRepository will delete all Pins it contains.
        // However, responsibility for managing the lifetime of any user data on those Pins is the responsbility
        // of the App.
        Eegeo_DELETE(m_pPinsModule);

        // Delete the icon texture and its layout.
        Eegeo_DELETE m_pPinIconsTexturePageLayout;
        glDeleteTextures(1, &m_pinIconsTexture.textureId);
    }

    void PinsExample::CreateExamplePins()
    {
        // Get the repository of all currently active Pins.
        Eegeo::Pins::PinRepository& pinRepository = m_pPinsModule->GetRepository();

        // Create test pins and add them to the repository.
        Eegeo::Pins::TPinId pin0Id = 0;
        Eegeo::Space::LatLong pin0Location = Eegeo::Space::LatLong::FromDegrees(37.7858,-122.401);
        int pin0Icon = 0;
        Eegeo::Pins::Pin* pPin0 = Eegeo_NEW(Eegeo::Pins::Pin)(pin0Id, pin0Location, 0, pin0Icon, &m_pin0UserData);
        pinRepository.AddPin(pPin0);

        // Save this pin so that we can add and remove it in AddRemovePin0()
        m_pPin0 = pPin0;

        Eegeo::Pins::TPinId pin1Id = 1;
        Eegeo::Space::LatLong pin1Location = Eegeo::Space::LatLong::FromDegrees(37.78547,-122.40259);
        int pin1Icon = 1;
        Eegeo::Pins::Pin* pPin1 = Eegeo_NEW(Eegeo::Pins::Pin)(pin1Id, pin1Location, 0, pin1Icon, &m_pin1UserData);
        pinRepository.AddPin(pPin1);

        Eegeo::Pins::TPinId pin2Id = 2;
        Eegeo::Space::LatLong pin2Location = Eegeo::Space::LatLong::FromDegrees(37.78547,-122.402);
        int pin2Icon = 2;
        Eegeo::Pins::Pin* pPin2 = Eegeo_NEW(Eegeo::Pins::Pin)(pin2Id, pin2Location, 0, pin2Icon, &m_pin2UserData);
        pinRepository.AddPin(pPin2);

        Eegeo::Pins::TPinId pin3Id = 3;
        Eegeo::Space::LatLong pin3Location = Eegeo::Space::LatLong::FromDegrees(37.78547,-122.403);
        int pin3Icon = 3;
        Eegeo::Pins::Pin* pPin3 = Eegeo_NEW(Eegeo::Pins::Pin)(pin3Id, pin3Location, 30, pin3Icon, &m_pin3UserData);
        pinRepository.AddPin(pPin3);
    }

    void PinsExample::Start()
    {
    }

    void PinsExample::Suspend()
    {
    }

    void PinsExample::Update(float dt)
    {
    	m_addRemoveTimer += dt;
    	if(m_addRemoveTimer > 3.0f)
    	{
    		AddRemovePin0();
    		m_addRemoveTimer = 0.0f;
    	}

        // Update the PinsModule to query terrain heights and update screen space coordinats for the Pins.
        m_pPinsModule->Update(dt);
    }

    void PinsExample::Draw()
    {
    }

    void PinsExample::AddRemovePin0()
    {
        Eegeo::Pins::PinRepository& pinRepository = m_pPinsModule->GetRepository();

        Eegeo::Pins::Pin* pPin0 = pinRepository.GetPinById(m_pPin0->GetId());
        if(pPin0)
        {
            Eegeo_TTY("Remove Pin 0 from repository.\n");
            pinRepository.RemovePin(m_pPin0);
        }
        else
        {
            Eegeo_TTY("Add Pin 0 to repository.\n");
            pinRepository.AddPin(m_pPin0);
        }
    }

    bool PinsExample::Event_TouchDown(const AppInterface::TouchData& data)
    {
        Eegeo::v2 screenTapPoint = Eegeo::v2(data.point.GetX(), data.point.GetY());

        EXAMPLE_LOG("Searching for Pins intersecting tap point %d,%d...", (int) screenTapPoint.GetX(), (int) screenTapPoint.GetY());

        Eegeo::Pins::PinController& pinController = m_pPinsModule->GetController();
        std::vector<Eegeo::Pins::Pin*> intersectingPinsClosestToCameraFirst;
        if(pinController.TryGetPinsIntersectingScreenPoint(screenTapPoint, intersectingPinsClosestToCameraFirst))
        {
        	EXAMPLE_LOG("found %ld :\n", intersectingPinsClosestToCameraFirst.size());

            for(std::vector<Eegeo::Pins::Pin*>::const_iterator it = intersectingPinsClosestToCameraFirst.begin(); it != intersectingPinsClosestToCameraFirst.end(); ++it)
            {
                Eegeo::Pins::Pin* pPin = *it;

                EXAMPLE_LOG("\tId=%d, User Data='%s'\n", pPin->GetId(), ((std::string*) pPin->GetUserData())->c_str());
            }

            return true;
        }
        else
        {
        	EXAMPLE_LOG("none found.\n");
            return false;
        }
    }
}


