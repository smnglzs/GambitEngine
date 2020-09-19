#include "Scene.h"

namespace gb
{
	SceneNode::SceneNode(const uint16 sortIndex, const std::string& name = "") :
		m_sortIndex(sortIndex),
		m_name(name)
	{
		m_children.reserve(BASE_CHILDREN_CAPACITY);
	}

	void SceneNode::AddChild(SceneNode* child)
	{
		m_children.push_back(child);
	}

	const std::string& SceneNode::GetName() const
	{
		return m_name;
	}

	uint16 SceneNode::GetSortIndex() const
	{
		return m_sortIndex;
	}

	const SceneLayer SceneLayer::SCENE_LAYER_NULL = { UINT16_MAX,		"SceneLayerNull" };
	const SceneLayer SceneLayer::SCENE_LAYER_UI	  = { UINT16_MAX - 1u,  "SceneLayerUI"	 };
	const SceneLayer SceneLayer::SCENE_LAYER_BASE = { 0u,				"SceneLayerBase" };

	SceneLayer::SceneLayer(const uint16 sortIndex, const std::string& name) :
		SceneNode(sortIndex, name)
	{
		
	}

	SceneLayer::~SceneLayer()
	{
		// what happens to scene nodes?
	}

	Scene::Scene()
	{
		m_layers.push_back(std::make_unique<SceneLayer>(SceneLayer::SCENE_LAYER_BASE));
		m_layers.push_back(std::make_unique<SceneLayer>(SceneLayer::SCENE_LAYER_UI));
	}

	Scene::~Scene()
	{
		// what happens to scene layers?
	}

	const SceneLayer& Scene::GetLayer(const uint16 layerIndex) const
	{
		if (layerIndex < m_layers.size())
		{
			return *m_layers[layerIndex];
		}
		else
		{
			return SceneLayer::SCENE_LAYER_NULL;
		}
	}

	const SceneLayerArray& Scene::GetLayers() const
	{
		return m_layers;
	}

	uint16 Scene::GetNumLayers() const
	{
		return static_cast<uint16>(m_layers.size());
	}
}