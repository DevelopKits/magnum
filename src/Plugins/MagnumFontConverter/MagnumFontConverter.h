#ifndef Magnum_Text_MagnumFontConverter_h
#define Magnum_Text_MagnumFontConverter_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Class Magnum::Text::MagnumFontConverter
 */

#include <Text/AbstractFontConverter.h>

namespace Magnum { namespace Text {

/**
@brief MagnumFont converter plugin

Expects filename prefix, creates two files, `prefix.conf` and `prefix.tga`. See
@ref MagnumFont for more information about the font.

This plugin is available only on desktop OpenGL, as it uses @ref Texture::image()
to read back the generated data. It depends on
@ref Trade::TgaImageConverter "TgaImageConverter" plugin and is built if
`WITH_MAGNUMFONTCONVERTER` is enabled in CMake. To use dynamic plugin, you need
to load `%MagnumFontConverter` plugin from `fontconverters/` subdirectory of
your plugin dir. To use static plugin or use this as a dependency of another
plugin, you need to request `%MagnumFontConverter` component in CMake and link
to `${MAGNUM_MAGNUMFONTCONVERTER_LIBRARIES}`. See @ref building and @ref cmake
for more information.
*/
class MagnumFontConverter: public Text::AbstractFontConverter {
    public:
        /** @brief Default constructor */
        explicit MagnumFontConverter();

        /** @brief Plugin manager constructor */
        explicit MagnumFontConverter(PluginManager::AbstractManager* manager, std::string plugin);

    private:
        Features doFeatures() const override;
        #ifndef _WIN32
        std::vector<std::pair<std::string, Containers::Array<unsigned char>>> doExportFontToData(AbstractFont& font, GlyphCache& cache, const std::string& filename, const std::u32string& characters) const override;
        #else
        std::vector<std::pair<std::string, Containers::Array<unsigned char>>> doExportFontToData(AbstractFont& font, GlyphCache& cache, const std::string& filename, const std::vector<char32_t>& characters) const override;
        #endif
};

}}

#endif
