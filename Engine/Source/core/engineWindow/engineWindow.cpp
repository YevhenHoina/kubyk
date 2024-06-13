#include "engineWindow.h"



// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp




#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <include/GLSW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

const int windowHeight = 1080.0f;
const int windowWidth = 1920.0f;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

const float sensitivity = 0.1f;
bool kubykMiddleMouseButtonPressed = false;
int kubyk_last_mouse_posX = 0, kubyk_last_mouse_posY = 0;
int xoffset = 0;
int yoffset = 0;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_MIDDLE)
    {
        if (action == GLFW_PRESS)
        {
            kubykMiddleMouseButtonPressed = true;
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            kubyk_last_mouse_posX = static_cast<int>(xpos);
            kubyk_last_mouse_posY = static_cast<int>(ypos);
        }
        else if (action == GLFW_RELEASE)
        {
            kubykMiddleMouseButtonPressed = false;
           
        }
    }
}



void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (kubykMiddleMouseButtonPressed)
    {
        int x = static_cast<int>(xpos);
        int y = static_cast<int>(ypos);
        xoffset += x - kubyk_last_mouse_posX;
        yoffset += kubyk_last_mouse_posY - y; // Reversed since y-coordinates go from bottom to top

        // Update the last positions
        kubyk_last_mouse_posX = x;
        kubyk_last_mouse_posY = y;

        // Use xoffset and yoffset for any necessary logic
    }
}

std::vector<addVoxel*> nodes;

// Function to add a new node
float last_node_coordX = 300.0f;
float last_node_coordY = 70.0f;

void addNode_addVoxel(float x, float y) {
    static int nodeCounter = 0;
    // Adjust the position of new nodes to avoid overlap
    float nodeOffset = 300.0f; // Distance to avoid overlap
    
    last_node_coordX += nodeOffset;
    last_node_coordY += last_node_coordY < 820 ? nodeOffset / 2 : -600;

    addVoxel* newNode = new addVoxel(last_node_coordX, last_node_coordY);
    newNode->title = " Add voxel";
    nodes.push_back(newNode);
}





void renderImGui(int argc, char** argv);

// Main code
int kubykEngineInit(int argc, char** argv)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    GLFWwindow* kubykWindow = glfwCreateWindow(windowWidth, windowHeight, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (kubykWindow == nullptr)
        return 1;
    glfwMakeContextCurrent(kubykWindow);
    glfwSwapInterval(1); // Enable vsync

    // Set the GLFW callbacks
    glfwSetMouseButtonCallback(kubykWindow, mouseButtonCallback);
    glfwSetCursorPosCallback(kubykWindow, cursorPositionCallback);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(kubykWindow, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.26f, 0.34f, 0.38f, 1.00f);

    // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(kubykWindow))
#endif
    {
        // Poll and handle events (inputs, kubykWindow resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderImGui(argc, argv);

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(kubykWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(kubykWindow);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(kubykWindow);
    glfwTerminate();

    return 0;
}

void renderImGui(int argc, char** argv) {
    // Calculate sizes
    float leftPanelWidth = windowWidth * 0.15f;
    float bottomPanelHeight = windowHeight * 0.3f;

    ImVec4 opaqueWindowBg = ImVec4(0.15f, 0.175f, 0.192f, 1.0f); // Opaque
    ImVec4 translucentWindowBg = ImVec4(0.15f, 0.175f, 0.192f, 0.70f); // Translucent
    ImVec4 opaqueButton = ImVec4(0.1f, 0.09f, 0.08f, 1.00f); // Opaque button color
    ImVec4 translucentButton = ImVec4(0.7f, 0.09f, 0.07f, 0.50f); // Translucent button color
    ImU32 lineColor = IM_COL32(254, 180, 28, 255);
    ImU32 arrowColor = IM_COL32(168, 197, 69, 255);

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoMouseInputs;

    float x = 350 + xoffset;
    float y = 250 - yoffset;

    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(100, 115), ImGuiCond_Always);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, opaqueButton);
    ImGui::Begin("Begin", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::GetWindowDrawList()->AddTriangleFilled(ImVec2(x + 29, y + 90), ImVec2(x + 75, y + 65), ImVec2(x + 29, y + 40), arrowColor);
    ImGui::End();
    ImGui::PopStyleColor(1);
    for (size_t i = 0; i < nodes.size(); ++i) {
        addVoxel* node = nodes[i];

        if (node->isOpen) {
            float x = node->nodePosX + xoffset;
            float y = node->nodePosY - yoffset;
            // Ensure node positions are set properly and apply the global offset
            ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(node->nodeSizeX, node->nodeSizeY), ImGuiCond_Always);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
            ImGui::PushStyleColor(ImGuiCol_WindowBg, opaqueWindowBg);
            ImGui::PushStyleColor(ImGuiCol_Button, translucentButton);

            

            // Ensure the window is draggable and remains uncollapsed
            std::string id = " Add voxel##" + std::to_string(i);
            ImGui::Begin(id.c_str(), &node->isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            
            // Make nodes always draggable
            if (ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows) && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                ImVec2 dragDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
                node->nodePosX += dragDelta.x;
                node->nodePosY += dragDelta.y;
                ImGui::ResetMouseDragDelta();
            }
            
            
            if (ImGui::BeginTabBar("Tabs")) {
                if (ImGui::BeginTabItem("Position")) {
                    ImGui::SliderFloat("X", &node->position[0], -1.0f, 1.0f);
                    ImGui::SliderFloat("Y", &node->position[1], -1.0f, 1.0f);
                    ImGui::SliderFloat("Z", &node->position[2], -1.0f, 1.0f);
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Rotation")) {
                    ImGui::SliderFloat("X", &node->rotation[0], -180.0f, 180.0f);
                    ImGui::SliderFloat("Y", &node->rotation[1], -180.0f, 180.0f);
                    ImGui::SliderFloat("Z", &node->rotation[2], -180.0f, 180.0f);
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Scale")) {
                    ImGui::SliderFloat("X", &node->scale[0], -5.0f, 5.0f);
                    ImGui::SliderFloat("Y", &node->scale[1], -5.0f, 5.0f);
                    ImGui::SliderFloat("Z", &node->scale[2], -5.0f, 5.0f);
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }

            ImGui::End();

            
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(2);
            ImGui::SetNextWindowSize(ImVec2(windowWidth - leftPanelWidth, windowHeight - bottomPanelHeight), ImGuiCond_Always);
            ImGui::SetNextWindowPos(ImVec2(leftPanelWidth, 0), ImGuiCond_Always);
            ImGui::Begin("Top Right Empty Space", nullptr, window_flags);

            ImVec2 firstPoint = ImVec2(x - 8, y + 25);
            ImVec2 secondPoint = ImVec2(455 + xoffset, 275 - yoffset);
            if (i >= 1)
            {
                secondPoint = ImVec2(nodes[i - 1]->nodePosX + nodes[i - 1]->nodeSizeX + xoffset + 5, nodes[i - 1]->nodePosY + 25 - yoffset);
            }
            ImGui::GetWindowDrawList()->AddLine(firstPoint, secondPoint, lineColor, 3.0f);

            ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(442 + xoffset, 270 - yoffset), ImVec2(458 + xoffset, 280 - yoffset), lineColor, 4);

            ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x - 8, y + 20), ImVec2(x + 8, y + 30), lineColor, 4);
            ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x - 8 + node->nodeSizeX, y + 20), ImVec2(x + 8 + node->nodeSizeX, y + 30), lineColor, 4);
            ImGui::End();
        }
    }

    // Left Panel
    window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, opaqueWindowBg);
    ImGui::PushStyleColor(ImGuiCol_Button, opaqueButton);
    ImGui::SetNextWindowSize(ImVec2(leftPanelWidth, windowHeight), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::Begin("Inspector", 0, window_flags);

    if (ImGui::Button("Add Node")) {
        addNode_addVoxel(last_node_coordX, last_node_coordY);
    }
    if (ImGui::Button("Launch Game")) {

        
        loadAdditionVoxels(nodes);
        gameInit(argc, argv, "myGame");
    }
    ImGui::End();
    ImGui::PopStyleColor(2);

    // Bottom Panel
    ImGui::PushStyleColor(ImGuiCol_WindowBg, opaqueWindowBg);
    ImGui::PushStyleColor(ImGuiCol_Button, opaqueButton);
    ImGui::SetNextWindowSize(ImVec2(windowWidth - leftPanelWidth, bottomPanelHeight), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(leftPanelWidth, windowHeight - bottomPanelHeight), ImGuiCond_Always);
    ImGui::Begin("Bottom Panel", 0, window_flags);
    
    ImGui::Text("This is the bottom panel.");
    
    ImGui::End();
    ImGui::PopStyleColor(2);

    

    // Top Right Empty Space (using child window to avoid border and title)
    
    
}
