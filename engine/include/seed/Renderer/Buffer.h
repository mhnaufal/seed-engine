#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace seed {
// TODO: change to reflection
enum class ShaderDataType : uint8_t {
    NONE = 0,
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    MATRIX2,
    MATRIX3,
    MATRIX4,
    INT,
    INT2,
    INT3,
    INT4,
    BOOL,
};

inline auto ShaderDataTypeSize(const ShaderDataType type) -> uint32_t
{
    switch (type) {
    case ShaderDataType::FLOAT:
        return 4;
    case ShaderDataType::FLOAT2:
        return 4 * 2;
    case ShaderDataType::FLOAT3:
        return 4 * 3;
    case ShaderDataType::FLOAT4:
        return 4 * 4;
    case ShaderDataType::MATRIX2:
        return 4 * 2 * 2;
    case ShaderDataType::MATRIX3:
        return 4 * 3 * 3;
    case ShaderDataType::MATRIX4:
        return 4 * 4 * 4;
    case ShaderDataType::INT:
        return 4;
    case ShaderDataType::INT2:
        return 4 * 2;
    case ShaderDataType::INT3:
        return 4 * 3;
    case ShaderDataType::INT4:
        return 4 * 4;
    case ShaderDataType::BOOL:
        return 1;
    default:
        return 0;
    }
}

struct BufferElement {
    std::string name{};
    ShaderDataType type{};
    uint32_t size{0};
    uint32_t offset{0};
    bool normalized{};

    BufferElement() = default;

    BufferElement(const ShaderDataType type, std::string  name, const bool normalized = false)
        : name(std::move(name)), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
    {
    }

    [[nodiscard]] auto GetComponentCount() const -> uint32_t
    {
        switch (type) {
        case ShaderDataType::FLOAT:
            return 1;
        case ShaderDataType::FLOAT2:
            return 2;
        case ShaderDataType::FLOAT3:
            return 3;
        case ShaderDataType::FLOAT4:
            return 4;
        case ShaderDataType::MATRIX2:
            return 2 * 2;
        case ShaderDataType::MATRIX3:
            return 3 * 3;
        case ShaderDataType::MATRIX4:
            return 4 * 4;
        case ShaderDataType::INT:
            return 1;
        case ShaderDataType::INT2:
            return 2;
        case ShaderDataType::INT3:
            return 3;
        case ShaderDataType::INT4:
            return 4;
        case ShaderDataType::BOOL:
            return 1;
        default:
            return 0;
        }
    }
};

class BufferLayout {
public:
    BufferLayout() = default;

    BufferLayout(const std::initializer_list<BufferElement>& elements)
        : m_elements(elements)
    {
        CalculateOffsetAndStride();
    }

    [[nodiscard]] auto GetStride() const -> uint32_t { return m_stride; }
    [[nodiscard]] auto GetElements() const -> const std::vector<BufferElement>& { return m_elements; }

    std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_elements.end(); }
    [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
    [[nodiscard]] std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

private:
    auto CalculateOffsetAndStride() -> void;

    std::vector<BufferElement> m_elements{};
    uint32_t m_stride{0};
};

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual auto Bind() const -> void = 0;
    virtual auto Unbind() const -> void = 0;

    [[nodiscard]] virtual auto GetLayout() const -> BufferLayout = 0;
    virtual auto SetLayout(const BufferLayout& layout) -> void = 0;

    static auto Create(const float* vertices, uint32_t size) -> VertexBuffer*;
};

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual auto Bind() const -> void = 0;
    virtual auto Unbind() const -> void = 0;
    [[nodiscard]] virtual auto GetCount() const -> uint32_t = 0;

    static auto Create(const uint32_t* indices, uint32_t size) -> IndexBuffer*;
};
}