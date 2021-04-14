#pragma once
#include "Base/Common/Common.h"
#include "Engine/Export.h"

namespace gb
{
	class GAMBIT_ENGINE_API SceneNode
	{
	public:
		SceneNode(const size_t sortIndex, const std::string& name);
		virtual ~SceneNode();

		void AddChild(SceneNode* child);

		const std::string& GetName()		const;
		size_t			   GetNumChildren() const; 
		size_t			   GetSortIndex()	const;

	public:
		std::string				m_name;
		std::vector<SceneNode*> m_children;
		size_t					m_sortIndex;

	protected:
		static const size_t s_baseChildrenCapacity = 4u;
	};

	class GAMBIT_ENGINE_API SceneLayer : public SceneNode
	{
	public:
		static const SceneLayer SceneLayer_Null;
		static const SceneLayer SceneLayer_UI;
		static const SceneLayer SceneLayer_Base;

	public:
		SceneLayer(const uint16 sortIndex, const std::string& name);
		virtual ~SceneLayer();

		inline void operator=(const SceneLayer& other)
		{
			m_sortIndex = other.m_sortIndex;
			m_name = other.m_name;
		}
	};

	using SceneLayerArray = std::vector<Unique<SceneLayer>>;
	class GAMBIT_ENGINE_API Scene
	{
	public:
		Scene();
		virtual ~Scene();
		
		const SceneLayer& GetLayer(const uint16 layerIndex) const;
		const SceneLayerArray& GetLayers() const;
		uint16 GetNumLayers() const;

	protected:
		SceneLayerArray m_layers;
	};
}