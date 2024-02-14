#ifndef UNNOMINABLE_TEXTURE_HPP_
#define UNNOMINABLE_TEXTURE_HPP_
#include <exception>
#include <format>
#include <glad/gl.h>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_pixels.h>
#include <SDL_surface.h>

class TextureLoadException : public std::exception {
private:
    std::string message;

public:
    TextureLoadException(const std::string &path, const std::string &message)
        : message(std::format("Failed to load texture at path {}: {}", path,
                              message)) {}
    virtual const char *what() const throw() { return this->message.c_str(); }
};

class UnsupportedTextureFormatException : public std::exception {
private:
    std::string message;

public:
    UnsupportedTextureFormatException(Uint32 format, const std::string &path)
        : message(std::format("Unsupported format {} in texture at path {}",
                              SDL_GetPixelFormatName(format), path)) {}
    virtual const char *what() const throw() { return this->message.c_str(); }
};

enum class TextureFormat {
    RED             = GL_RED,
    RG              = GL_RG,
    RGB             = GL_RGB,
    BGR             = GL_BGR,
    RGBA            = GL_RGBA,
    BGRA            = GL_BGRA,
    DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    DEPTH_STENCIL   = GL_DEPTH_STENCIL
};

enum class TextureType {
    TEX1D                   = GL_TEXTURE_1D,
    TEX2D                   = GL_TEXTURE_2D,
    TEX3D                   = GL_TEXTURE_3D,
    TEX1D_ARRAY             = GL_TEXTURE_1D_ARRAY,
    TEX2D_ARRAY             = GL_TEXTURE_2D_ARRAY,
    RECTANGLE               = GL_TEXTURE_RECTANGLE,
    CUBE_MAP                = GL_TEXTURE_CUBE_MAP,
    CUBE_MAP_ARRAY          = GL_TEXTURE_CUBE_MAP_ARRAY,
    BUFFER                  = GL_TEXTURE_BUFFER,
    TEX2D_MULTISAMPLE       = GL_TEXTURE_2D_MULTISAMPLE,
    TEX2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};

enum class TextureUnit {
    U0  = GL_TEXTURE0,
    U1  = GL_TEXTURE1,
    U2  = GL_TEXTURE2,
    U3  = GL_TEXTURE3,
    U4  = GL_TEXTURE4,
    U5  = GL_TEXTURE5,
    U6  = GL_TEXTURE6,
    U7  = GL_TEXTURE7,
    U8  = GL_TEXTURE8,
    U9  = GL_TEXTURE9,
    U10 = GL_TEXTURE10,
    U11 = GL_TEXTURE11,
    U12 = GL_TEXTURE12,
    U13 = GL_TEXTURE13,
    U14 = GL_TEXTURE14,
    U15 = GL_TEXTURE15,
    U16 = GL_TEXTURE16,
    U17 = GL_TEXTURE17,
    U18 = GL_TEXTURE18,
    U19 = GL_TEXTURE19,
    U20 = GL_TEXTURE20,
    U21 = GL_TEXTURE21,
    U22 = GL_TEXTURE22,
    U23 = GL_TEXTURE23,
    U24 = GL_TEXTURE24,
    U25 = GL_TEXTURE25,
    U26 = GL_TEXTURE26,
    U27 = GL_TEXTURE27,
    U28 = GL_TEXTURE28,
    U29 = GL_TEXTURE29,
    U30 = GL_TEXTURE30,
    U31 = GL_TEXTURE31,
};

enum class TextureParameter {
    DEPTH_STENCIL_TEXTURE_MODE = GL_DEPTH_STENCIL_TEXTURE_MODE,
    BASE_LEVEL                 = GL_TEXTURE_BASE_LEVEL,
    COMPARE_FUNC               = GL_TEXTURE_COMPARE_FUNC,
    COMPARE_MODE               = GL_TEXTURE_COMPARE_MODE,
    LOD_BIAS                   = GL_TEXTURE_LOD_BIAS,
    MIN_FILTER                 = GL_TEXTURE_MIN_FILTER,
    MAG_FILTER                 = GL_TEXTURE_MAG_FILTER,
    MIN_LOD                    = GL_TEXTURE_MIN_LOD,
    MAX_LOD                    = GL_TEXTURE_MAX_LOD,
    MAX_LEVEL                  = GL_TEXTURE_MAX_LEVEL,
    SWIZZLE_R                  = GL_TEXTURE_SWIZZLE_R,
    SWIZZLE_G                  = GL_TEXTURE_SWIZZLE_G,
    SWIZZLE_B                  = GL_TEXTURE_SWIZZLE_B,
    SWIZZLE_A                  = GL_TEXTURE_SWIZZLE_A,
    WRAP_S                     = GL_TEXTURE_WRAP_S,
    WRAP_T                     = GL_TEXTURE_WRAP_T,
    WRAP_R                     = GL_TEXTURE_WRAP_R,
};

enum class TextureVectorParameter {
    BORDER_COLOR = GL_TEXTURE_BORDER_COLOR,
    SWIZZLE_RGBA = GL_TEXTURE_SWIZZLE_RGBA,
};

enum class TextureDataType {
    UNSIGNED_BYTE               = GL_UNSIGNED_BYTE,
    BYTE                        = GL_BYTE,
    UNSIGNED_SHORT              = GL_UNSIGNED_SHORT,
    SHORT                       = GL_SHORT,
    UNSIGNED_INT                = GL_UNSIGNED_INT,
    INT                         = GL_INT,
    FLOAT                       = GL_FLOAT,
    UNSIGNED_BYTE_3_3_2         = GL_UNSIGNED_BYTE_3_3_2,
    UNSIGNED_BYTE_2_3_3_REV     = GL_UNSIGNED_BYTE_2_3_3_REV,
    UNSIGNED_SHORT_5_6_5        = GL_UNSIGNED_SHORT_5_6_5,
    UNSIGNED_SHORT_5_6_5_REV    = GL_UNSIGNED_SHORT_5_6_5_REV,
    UNSIGNED_SHORT_4_4_4_4      = GL_UNSIGNED_SHORT_4_4_4_4,
    UNSIGNED_SHORT_4_4_4_4_REV  = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    UNSIGNED_SHORT_5_5_5_1      = GL_UNSIGNED_SHORT_5_5_5_1,
    UNSIGNED_SHORT_1_5_5_5_REV  = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    UNSIGNED_INT_8_8_8_8        = GL_UNSIGNED_INT_8_8_8_8,
    UNSIGNED_INT_8_8_8_8_REV    = GL_UNSIGNED_INT_8_8_8_8_REV,
    UNSIGNED_INT_10_10_10_2     = GL_UNSIGNED_INT_10_10_10_2,
    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
};

class Texture {
private:
    const void *data_;
    TextureType type_;

public:
    GLuint        object;
    TextureFormat format;

    Texture(TextureType type);
    Texture() { data_ = nullptr; }

    /// Generates the texture using glGenTextures.
    void generate();

    /// Binds the texture using glBindTexture.
    void bind();
    /// Generates the texture and then binds it.
    void bind_generate();
    /// Sets the active texture unit using glActiveTexture then binds the
    /// texture using glBindTexture.
    void bind_active(TextureUnit texture_unit);

    /// Upload two-dimensional texture data.
    void upload_2d(GLsizei width, GLsizei height, TextureDataType data_type);

    /// Generates a mipmap using glGenerateMipmap.
    void generate_mipmap();

    /// Sets a texture parameter using glTextureParameterf.
    void parameter_f(TextureParameter parameter, GLfloat value);
    /// Sets a texture parameter using glTextureParameteri.
    void parameter_i(TextureParameter parameter, GLint value);
    /// Sets a texture parameter using glTextureParameterfv.
    void parameter_fv(TextureVectorParameter parameter, const GLfloat *values);
    /// Sets a texture parameter using glTextureParameteriv.
    void parameter_iv(TextureVectorParameter parameter, const GLint *values);
    /// Sets a texture parameter using glTextureParameterfv.
    template <size_t N>
    void parameter_fv(TextureVectorParameter        parameter,
                      const std::array<GLfloat, N> &values) {
        this->parameter_fv(parameter, values.data());
    }
    /// Sets a texture parameter using glTextureParameteriv.
    template <size_t N>
    void parameter_iv(TextureVectorParameter      parameter,
                      const std::array<GLint, N> &values) {
        this->parameter_iv(parameter, values.data());
    }
    /// Sets a texture parameter using glTextureParameterfv.
    void parameter_fv(TextureVectorParameter parameter,
                      std::convertible_to<GLfloat> auto... values) {
        std::array<GLfloat, sizeof...(values)> values_array{values...};
        this->parameter_fv(parameter, values_array);
    }
    /// Sets a texture parameter using glTextureParameteriv.
    void parameter_iv(TextureVectorParameter parameter,
                      std::convertible_to<GLint> auto... values) {
        std::array<GLint, sizeof...(values)> values_array{values...};
        this->parameter_iv(parameter, values_array);
    }

    const std::optional<const void *> data() const {
        return (data_ == nullptr) ? std::nullopt : std::optional(data_);
    }
    void data(const void *data) { data_ = std::move(data); }

    const TextureType type() const { return type_; }
};

/// A two-dimensional texture.
class Texture2D : public Texture {
private:
    GLsizei width_, height_;

public:
    Texture2D(TextureType type);
    Texture2D() : Texture() {}

    /// Upload two-dimensional texture data.
    void upload(TextureDataType data_type);

    GLsizei       &width() { return width_; }
    const GLsizei &width() const { return width_; }

    GLsizei       &height() { return height_; }
    const GLsizei &height() const { return height_; }
};

/// A texture image.
class ImageTexture : public Texture2D {
private:
    SDL_Surface *surface;
    std::string  path;

public:
    ImageTexture(const std::string &path);
    ImageTexture() : Texture2D() {}
    ~ImageTexture();

    /// Vertically flip the texture.
    void flip_surface();

    /// Upload texture data.
    void upload();

    /// Sets the default mipmap parameters.
    void default_parameters();

    /// Frees the internal SDL_Surface. This must be called after calling
    /// glTexImage!
    void free_surface();
};

#endif // UNNOMINABLE_TEXTURE_HPP_
