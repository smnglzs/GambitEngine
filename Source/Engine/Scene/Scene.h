#pragma once
#include "Base/Common/Common.h"

namespace gb
{
	class SceneNode
	{
	public:
		SceneNode(const uint16 sortIndex, const std::string& name);
		virtual ~SceneNode() = default;

		void AddChild(SceneNode* child);
		const std::string& GetName() const;
		uint16 GetSortIndex() const;

	public:
		static const size_t BASE_CHILDREN_CAPACITY = 4u;

		std::vector<SceneNode*> m_children;
		std::string				m_name;
		uint32					m_sortIndex;
	};

	class SceneLayer : public SceneNode
	{
	public:
		static const SceneLayer SCENE_LAYER_NULL;
		static const SceneLayer SCENE_LAYER_UI;
		static const SceneLayer SCENE_LAYER_BASE;

	public:
		SceneLayer(const uint16 sortIndex, const std::string& name);
		virtual ~SceneLayer();
	};

	using SceneLayerArray = std::vector<Unique<SceneLayer>>;
	class Scene
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