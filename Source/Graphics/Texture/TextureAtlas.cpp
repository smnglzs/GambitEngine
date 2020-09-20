#include "TextureAtlas.h"

namespace gb
{
	TextureAtlas::~TextureAtlas()
	{
		// We don't call Destroy because the parent RHIObject (Texture) does.
	}
}