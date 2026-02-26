#pragma once

#include <string>
#include <unordered_map>

namespace Miriya {
    class Shader {
    public:
        // Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~Shader() = default;

        // In the future, want to have subclasses; Implemented per API; so need to be virtual
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0; // for debugging purposes

        // not want to expose these
        // void UploadUniformFloat4(const std::string &name, const glm::vec4& values);
        // void UploadUniformMat4(const std::string &name, const glm::mat4& matrix);

        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string& filepath);
        static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };

    class ShaderLibrary {
    public:
        void Add(const std::string& name, const Ref<Shader>& shader);
        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& filepath);
        Ref<Shader> Load(const std::string& name, const std::string& filepath);

        Ref<Shader> Get(const std::string& name);

        bool Exists(const std::string& name) const;
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
} // Miriya