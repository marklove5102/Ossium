#ifndef MATERIAL_H
#define MATERIAL_H

#include "resourcecontroller.h"
#include "shader.h"
#include "bgfx/bgfx.h"

namespace Ossium
{
    class MaterialAttribute;

    // A material consists of one or more shaders and their input/attribute values,
    // with the exception of mesh-specific data such as vertices (typically).
    class Material : public Resource
    {
    public:
        DECLARE_RESOURCE(Material);

        virtual ~Material();

        // Destroy loaded shader program
        void Free();

        // Load a material from a .MTL file.
        // Note that if you do not supply a specific material name on the end of the path the first material listed in the file will be loaded
        // and a warning will be logged if there is more than one material declared in the file.
        // Shaders loaded by materials are expected in the naming format *.vert and *.frag for vertex and fragment shaders respectively.
        bool Load(std::string guid_path);

        // Load and initialise relevant shaders.
        // You must provide a ResourceController pointer such that the shader programs can be loaded.
        bool Init(ResourceController* resources, std::string vertexShaderPath, std::string fragmentShaderPath);

        // Load from a .MTL file, then initialise the relevant shader.
        bool LoadAndInit(std::string guid_path, ResourceController* resources, std::string vertexShaderPath, std::string fragmentShaderPath);

        // Get the shader associated with this material.
        Shader* GetShader(Shader::Type shaderType);

        // Returns the name of this material.
        std::string GetName();

    private:
        // The shaders associated with this material.
        Shader* shaderVertex = nullptr;
        Shader* shaderFragment = nullptr;

        std::string shaderVertexPath = "standard.vert";
        std::string shaderFragmentPath = "standard.frag";

        // The loaded shader program
        bgfx::ProgramHandle shader;

        // Name of the material
        std::string name;

        // Shader attributes associated with this material.
        std::vector<MaterialAttribute> attributes;

    };

    // A particular material attribute to pass to the shaders
    struct MaterialAttribute
    {
    public:
        // What type of shader does this material attribute apply to?
        enum ShaderType
        {
            Vertex = 0,
            Fragment
        } shaderType;

        // Attribute name
        std::string name;

    };
    
}

#endif // MATERIAL_H
