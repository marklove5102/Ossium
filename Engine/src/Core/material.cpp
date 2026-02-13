#include "material.h"
#include "coremaths.h"
#include "file.h"

namespace Ossium
{
    
    REGISTER_RESOURCE(Material);

    Material::~Material()
    {
        Free();
    }

    void Material::Free()
    {
        // Don't actually free the shaders as they will still exist in the resource controller and may still be used.
        shaderFragment = nullptr;
        shaderVertex = nullptr;
        if (bgfx::isValid(shader))
        {
            bgfx::destroy(shader);
            shader = BGFX_INVALID_HANDLE;
        }
    }

    bool Material::Load(std::string guid_path)
    {
        Free();

        // First, check if the path ends in .mtl or not. If not, assume a specific material name has been provided.
        std::string mtlname = Utilities::ExtractFilename(guid_path);
        std::string ext = Utilities::SplitRight(mtlname, '.', "", -1);
        if (ext != "mtl" && ext != "MTL")
        {
            guid_path = Utilities::StripFilename(guid_path, true);
            name = mtlname;
        }
        else
        {
            name = "";
        }

        // Open the MTL file
        File mtl(guid_path);
        if (mtl.HasError())
        {
            Log.Error(mtl.GetError());
            return false;
        }

        // Read the very first element of the file
        std::string keyword = mtl.ReadElement(' ');
        std::string element = "";

        // Standard material properties
        Vector3 ambient;
        Vector3 diffuse;
        Vector3 specular;
        float dissolve;

        // Parse the file
        while (!keyword.empty())
        {
            if (keyword == "newmtl")
            {
                element = mtl.ReadElement(' ');
                if (mtlname.empty())
                {
                    mtlname = element;
                    name = element;
                }
            }
            else if (keyword == "Ka")
            {
                // todo: ambient
            }
            else if (keyword == "Kd")
            {
                // todo: diffuse
            }
            else if (keyword == "Ks")
            {
                // todo: specular
            }
            else if (keyword == "d")
            {
                // todo: dissolve
            }
            else
            {
                // Irrelevant data such as comments
                // TODO: In future support different illumination models etc.
            }
            // Get the next keyword
            keyword = mtl.ReadElement(' ');
        }
        
        return true;
    }

    bool Material::Init(ResourceController* resources, std::string shaderVertexPath, std::string shaderFragmentPath)
    {
        shaderVertex = resources->Get<Shader>(shaderVertexPath);
        shaderFragment = resources->Get<Shader>(shaderFragmentPath);
        shader = bgfx::createProgram(shaderVertex->GetHandle(), shaderFragment->GetHandle(), false);
        return true;
    }

    bool Material::LoadAndInit(std::string guid_path, ResourceController* resources, std::string vertexShaderPath, std::string fragmentShaderPath)
    {
        return Load(guid_path) && Init(resources, vertexShaderPath, fragmentShaderPath);
    }

    Shader* Material::GetShader(Shader::Type shaderType)
    {
        switch (shaderType)
        {
            case Shader::Type::Vertex:
                return shaderVertex;
            case Shader::Type::Fragment:
                return shaderFragment;
            default:
                return nullptr;
        }
    }

    std::string Material::GetName()
    {
        return name;
    }

}
