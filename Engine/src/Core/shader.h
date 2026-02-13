#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "bgfx/bgfx.h"

#include "resourcecontroller.h"

namespace Ossium
{

    class Shader : public Resource
    {
    public:
        DECLARE_RESOURCE(Shader);

        // What type of shader?
        enum Type
        {
            Vertex = 0,
            Fragment
        };

        Shader() = default;
        virtual ~Shader();

        // Load the shader from file
        bool Load(std::string guid_path);

        // Initialise the shader
        bool Init();

        // Load and initialise the shader
        bool LoadAndInit(std::string guid_path);

        // Get the BGFX shader handle
        bgfx::ShaderHandle GetHandle();

        // Free existing shader
        bool Free();

        // Get the correct shader path according to the current rendering backend
        static std::string GetPath(std::string id);

        // Get the shader type, e.g. fragment or vertex.
        Type GetType();

    private:
        bgfx::ShaderHandle handle = BGFX_INVALID_HANDLE;

        // What type of shader is this?
        Type type = Type::Vertex;

    };

}

#endif // SHADER_H
