#include "texture.hpp"
#include <algorithm>
#include <utility>
#include <SDL_image.h>
#include <SDL_log.h>
#include <SDL_surface.h>

TextureUnit get_texture_unit(GLenum index) {
    if (index > 31) {
        throw std::runtime_error(
            std::format("Invalid texture unit #{}", index));
    }

    return TextureUnit{GL_TEXTURE0 + index};
}

Texture::Texture(TextureDimensionality type) { this->dimensionality_ = type; }

void Texture::generate() { glGenTextures(1, &this->object); }

void Texture::bind() {
    glBindTexture(std::to_underlying(this->dimensionality()), this->object);
}

void Texture::bind_generate() {
    this->generate();
    this->bind();
}

void Texture::bind_active(TextureUnit texture_unit) {
    glActiveTexture(std::to_underlying(texture_unit));
    this->bind();
}

void Texture::upload_2d(GLsizei width, GLsizei height,
                        TextureDataType data_type) {
    glTexImage2D(std::to_underlying(this->dimensionality()), 0,
                 std::to_underlying(this->format), width, height, 0,
                 std::to_underlying(this->format),
                 std::to_underlying(data_type), this->data_);
}

void Texture::generate_mipmap() {
    glGenerateMipmap(std::to_underlying(this->dimensionality()));
}

void Texture::parameter_f(TextureParameter parameter, GLfloat value) {
    glTextureParameterf(this->object, std::to_underlying(parameter), value);
}

void Texture::parameter_i(TextureParameter parameter, GLint value) {
    glTextureParameteri(this->object, std::to_underlying(parameter), value);
}

void Texture::parameter_fv(TextureVectorParameter parameter,
                           const GLfloat         *values) {
    glTextureParameterfv(this->object, std::to_underlying(parameter), values);
}

void Texture::parameter_iv(TextureVectorParameter parameter,
                           const GLint           *values) {
    glTextureParameteriv(this->object, std::to_underlying(parameter), values);
}

Texture2D::Texture2D(TextureDimensionality type) : Texture(type) {}

void Texture2D::upload(TextureDataType data_type) {
    this->upload_2d(this->width_, this->height_, data_type);
}

ImageTexture::ImageTexture(const std::string &path)
    : Texture2D(TextureDimensionality::TEX2D) {
    this->path    = path;
    this->surface = IMG_Load(path.c_str());
    if (!this->surface) {
        throw TextureLoadException(path, SDL_GetError());
    }

    this->flip_surface();
    this->width()  = this->surface->w;
    this->height() = this->surface->h;
    this->data(this->surface->pixels);

    Uint8 num_colors = this->surface->format->BytesPerPixel;
    if (num_colors == 4) {
        if (this->surface->format->Rmask == 0x000000ff)
            this->format = TextureFormat::RGBA;
        else
            this->format = TextureFormat::BGRA;
    } else if (num_colors == 3) {
        if (this->surface->format->Rmask == 0x000000ff)
            this->format = TextureFormat::RGB;
        else
            this->format = TextureFormat::BGR;
    } else {
        throw UnsupportedTextureFormatException(this->surface->format->format,
                                                path);
    }
}

ImageTexture::~ImageTexture() {
    if (surface != nullptr) {
        SDL_LogWarn(SDL_LOG_CATEGORY_RENDER,
                    "SDL_Surface for texture at path %s wasn't freed!",
                    this->path.c_str()); // give 'em a slap on the wrist
        this->free_surface();
    }
}

// https://stackoverflow.com/a/65817254/11774699
void ImageTexture::flip_surface() {
    SDL_LockSurface(this->surface);

    int   pitch  = this->surface->pitch; // row size
    char *pixels = static_cast<char *>(this->surface->pixels);

    for (int i = 0; i < this->surface->h / 2; i++) {
        // get pointers to the two rows we'll swap
        char *row1 = pixels + i * pitch;
        char *row2 = pixels + (this->surface->h - i - 1) * pitch;

        std::swap_ranges(row1, row1 + pitch, row2);
    }

    SDL_UnlockSurface(this->surface);
}

void ImageTexture::upload() {
    this->Texture2D::upload(TextureDataType::UNSIGNED_BYTE);
}

void ImageTexture::default_parameters() {
    this->parameter_i(TextureParameter::WRAP_S, GL_MIRRORED_REPEAT);
    this->parameter_i(TextureParameter::WRAP_T, GL_MIRRORED_REPEAT);
    this->parameter_i(TextureParameter::MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    this->parameter_i(TextureParameter::MAG_FILTER, GL_LINEAR);
}

void ImageTexture::free_surface() {
    SDL_FreeSurface(this->surface);
    this->surface = nullptr;
}
