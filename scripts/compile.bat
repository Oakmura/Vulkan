%VULKAN_SDK%/Bin/glslc.exe ..\Vulkan\Resources\Shaders\shader.vert -o ..\Vulkan\Resources\Shaders\vert.spv
%VULKAN_SDK%/Bin/glslc.exe ..\Vulkan\Resources\Shaders\shader.frag -o ..\Vulkan\Resources\Shaders\frag.spv

%VULKAN_SDK%/Bin/glslc.exe ..\Vulkan\Resources\Shaders\SimpleShader.vert -o ..\Vulkan\Resources\Shaders\SimpleShaderVert.spv
%VULKAN_SDK%/Bin/glslc.exe ..\Vulkan\Resources\Shaders\SimpleShader.frag -o ..\Vulkan\Resources\Shaders\SimpleShaderFrag.spv

pause