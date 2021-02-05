#pragma once

// All includes are here so that we only
// need to include this header file
// For use by Mimou Applications

#include<iostream>
#include "Mimou/Application.h"
#include "Mimou/Log.h"
#include "Mimou/Layer.h"
#include "Mimou/Input.h"
#include "Mimou/KeyCodes.h"
#include "Mimou/MouseButtonCodes.h"
#include "Mimou/ImGui/ImGuiLayer.h"
#include "Mimou/Renderer/Renderer.h"
#include "Mimou/Renderer/Shader.h"
#include "Mimou/Renderer/Texture.h"
#include "Mimou/Renderer/OrthographicCamera.h"
#include "Mimou/Events/Event.h"
#include "Mimou/Events/KeyEvent.h"

#include "Mimou/Core/Timestep.h"

#include "imgui.h"

using namespace std;

// --Entry Pointe
#include "Mimou/EntryPoint.h"
// --