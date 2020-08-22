#include <iostream>
#include <chrono>
using namespace std::chrono;

#include "Base/GambitBaseModule.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Device/DeviceModule.h"
#include "Device/Window/WindowManager.h"
#include "Graphics/GraphicsModule.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Shader/ShaderManager.h"
#include "Graphics/Texture/TextureManager.h"

#include "Graphics/Geometry/VertexArray.h"
#include "Graphics/RHI/RHI.h"

#define CONSOLE_PAUSE 0

#include "Device/DeviceModule.h"
#include "Device/Window/WindowManager.h"

static const char* g_vertexShader = 
    "#version 450 core\n"
    "layout(location = 0) in vec2 Position;\n"
    "uniform vec3 Color;\n"
    "out VS_OUT\n"
    "{\n"
    "   vec2 pos;\n"
    "   vec2 uv;\n"
    "   vec3 color;\n"
    "} vertex;\n"
    "void main()\n"
    "{\n"
    "   vertex.color = Color;\n"
    "   vertex.pos = Position;\n"
    "   gl_Position = vec4(Position, 0.0, 1.0);\n"
    "}";

static const char* g_fragmentShader = 
    "#version 450 core\n"
    "uniform float Time;\n"
    "in VS_OUT\n"
    "{\n"
    "   vec2 pos;\n"
    "   vec2 uv;\n"
    "   vec3 color;\n"
    "} vertex;\n"
    "out vec4 fragmentColor;\n"
    "void main()\n"
    "{\n"
    "   float r = abs(sin(Time));\n"
    "   float b = abs(cos(Time));\n"
    "   fragmentColor = vec4(r, 0.5, b, 1.0);\n"
    "}";

int main()
{
    // ========================================================= //
    //                          Base Module                      //
    // ========================================================= //
    std::cout << "Attempting to call GambitBase API...\n";
    gb::ModuleBase gbMod;

    std::cout << "Attempting to StartUp GambitBase API...\n";
    gbMod.StartUp();

    std::cout << "Attempting to RegisterSingletons of GambitBase API...\n";
    gbMod.RegisterSingletons();

    std::cout << "Adding Log Channel EngineInfo to Engine...\n";
    CREATE_LOG_CHANNEL(gb::EChannelComponent::EngineInfo, gb::EOutputType::Both, gb::ELogLevel::Info, "Engine.txt");

    std::cout << "Attempting to log in EngineInfo channel...\n";
    LOG(gb::EChannelComponent::EngineInfo, "Test EngineInfo channel.");

    LOG(gb::EChannelComponent::EngineInfo, "Attempting to Shutdown GambitBase API...");
    gbMod.ShutDown();

    // ========================================================= //
    //                          Device Module                    //
    // ========================================================= //
    std::cout << "Attempting to call GambitDevice API...\n";
    gb::DeviceModule dev;
    dev.StartUp();
    dev.RegisterSingletons();

    gb::WindowManager& wm = *gb::GetWindowManager();
    gb::WindowSettings ws;
    wm.CreateWindow(ws);
    
    gb::GraphicsModule gfx;
    gfx.StartUp();
    gfx.RegisterSingletons();

    gb::ShaderManager& sm = *gb::GetShaderManager();
    const bool doesShaderExist =
        sm.LoadShader("VS_Default", g_vertexShader, gb::EShaderStage::Vertex) &&
        sm.LoadShader("FS_Default", g_fragmentShader, gb::EShaderStage::Fragment) &&
        sm.CreateShaderProgram("VS_Default", "FS_Default");

    if (doesShaderExist)
    {
        sm.BindShaderProgram("VS_DefaultFS_Default");
    }

    milliseconds startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    gb::Renderer& renderer = *gb::GetRenderer();
    while (!wm.ShouldClose())
    {
        wm.PollEvents();

        milliseconds elapsedTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()) - startTime;
        float uniformTime = elapsedTime.count() / 1000.f;
        sm.SetUniform("Time", uniformTime);

        renderer.BeginFrame();
        renderer.EndFrame();
        wm.SwapBuffers();
    }

    gbMod.ShutDown();
    gfx.ShutDown();
    dev.ShutDown();

#if CONSOLE_PAUSE
    system("pause");
#endif

    return 0;
}