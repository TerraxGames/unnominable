#include "texture.hpp"
#include <algorithm>
#include <optional>
#include <SDL_image.h>
#include <SDL_log.h>
#include <SDL_surface.h>

Texture::Texture(TextureType type) { this->type_ = type; }

void Texture::generate() { glGenTextures(1, &this->object); }

void Texture::bind() { glBindTexture(this->type(), this->object); }

void Texture::bind_generate() {
    this->generate();
    this->bind();
}

void Texture::bind_active(TextureUnit texture_unit) {
    glActiveTexture(texture_unit);
    this->bind();
}

void Texture::upload_2d(GLsizei width, GLsizei height,
                        TextureDataType data_type) {
    glTexImage2D(this->type_, 0, this->format, width, height, 0, this->format,
                 data_type, this->data_);
}

void Texture::generate_mipmap() { glGenerateMipmap(this->type()); }

void Texture::parameter_f(TextureParameter parameter, GLfloat value) {
    glTextureParameterf(this->object, parameter, value);
}

void Texture::parameter_i(TextureParameter parameter, GLint value) {
    glTextureParameteri(this->object, parameter, value);
}

void Texture::parameter_fv(TextureVectorParameter parameter,
                           const GLfloat         *values) {
    glTextureParameterfv(this->object, parameter, values);
}

void Texture::parameter_iv(TextureVectorParameter parameter,
                           const GLint           *values) {
    glTextureParameteriv(this->object, parameter, values);
}

Texture2D::Texture2D(TextureType type) : Texture(type) {}

void Texture2D::upload(TextureDataType data_type) {
    this->upload_2d(this->width_, this->height_, data_type);
}

ImageTexture::ImageTexture(const std::string &path)
    : Texture2D(TextureType::TEX2D) {
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
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
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
