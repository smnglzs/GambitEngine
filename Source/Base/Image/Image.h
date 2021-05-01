#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Export.h"

namespace gb
{
	class GAMBIT_BASE_API Image final
	{
	public:
		Image(const std::string& imagePath, const bool flipVertically = true);
		~Image();

		bool LoadFromFile(const std::string& filePath, const bool flipVertically = true);

		inline const byte* GetPixelData() const { return m_pixelData; }
		inline int32	   GetWidth()     const { return m_width;	  }
		inline int32	   GetHeight()    const { return m_height;	  }
		inline bool		   IsValid()	  const	{ return m_valid;	  }

	protected:
		void FreePixelData();

		byte* m_pixelData;
		int32 m_width;
		int32 m_height;
		bool  m_valid;
	};
}