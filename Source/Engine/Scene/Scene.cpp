#include "Scene.h"

namespace gb
{
	SceneNode::SceneNode(const size_t sortIndex, const std::string& name = "") :
		m_sortIndex(sortIndex),
		m_name(name)
	{
		m_children.reserve(s_baseChildrenCapacity);
	}

	SceneNode::~SceneNode()
	{

	}

	void SceneNode::AddChild(SceneNode* child)
	{
		m_children.push_back(child);
	}

	const std::string& SceneNode::GetName() const
	{
		return m_name;
	}

	size_t SceneNode::GetNumChildren() const
	{
		return m_children.size();
	}

	size_t SceneNode::GetSortIndex() const
	{
		return m_sortIndex;
	}

	const SceneLayer SceneLayer::SceneLayer_Null = { UINT16_MAX,		"SceneLayer_Null" };
	const SceneLayer SceneLayer::SceneLayer_UI	 = { UINT16_MAX - 1u,   "SceneLayer_UI"   };
	const SceneLayer SceneLayer::SceneLayer_Base = { 0u,				"SceneLayer_Base" };

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
		m_layers.push_back(std::make_unique<SceneLayer>(SceneLayer::SceneLayer_Base));
		m_layers.push_back(std::make_unique<SceneLayer>(SceneLayer::SceneLayer_UI));
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
			return SceneLayer::SceneLayer_Null;
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