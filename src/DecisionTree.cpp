#include "DecisionTree.h"

#include <iostream>

#include "ActionNode.h"
#include  "AttackAction.h"
#include "MoveToLOSAction.h"
#include "MoveToPlayerAction.h"
#include "PatrolAction.h"


DecisionTree::DecisionTree()
{
	//m_buildTree();
}

DecisionTree::DecisionTree(Agent* agent)
{
	m_agent = agent;
	//m_buildTree();
}

DecisionTree::~DecisionTree()
= default;

Agent* DecisionTree::GetAgent() const
{
	return m_agent;
}

void DecisionTree::SetAgent(Agent* agent)
{
	m_agent = agent;
}

LOSCondition* DecisionTree::GetLOSNode() const
{
	return m_LOSNode;
}

RadiusCondition* DecisionTree::GetRadiusNode() const
{
	return m_radiusNode;
}

CloseCombatCondition* DecisionTree::GetCloseCombatNode() const
{
	return m_closeCombatNode;
}

RangedCombatCondition* DecisionTree::GetRangedCombatNode() const
{
	return m_rangedCombatNode;
}

EnemyHealthCondition* DecisionTree::GetEnemyHealthNode() const
{
	return m_enemyHealthConditionNode;
}

EnemyHitCondition* DecisionTree::GetEnemyHitNode() const
{
	return m_enemyHitConditionNode;
}

PlayerDetectedCondition* DecisionTree::GetPlayerDetectedNode() const
{
	return m_playerDetectedConditionNode;
}

void DecisionTree::SetEnemyHealthNode(EnemyHealthCondition* node)
{
	m_enemyHealthConditionNode = node;
}

void DecisionTree::SetEnemyHitNode(EnemyHitCondition* node)
{
	m_enemyHitConditionNode = node;
}

void DecisionTree::SetPlayerDetectedNode(PlayerDetectedCondition* node)
{
	m_playerDetectedConditionNode = node;
}

std::vector<TreeNode*>& DecisionTree::GetTree()
{
	return m_treeNodeList;
}

void DecisionTree::SetLOSNode(LOSCondition* node)
{
	m_LOSNode = node;
}

void DecisionTree::SetRadiusNode(RadiusCondition* node)
{
	m_radiusNode = node;
}

void DecisionTree::SetCloseCombatNode(CloseCombatCondition* node)
{
	m_closeCombatNode = node;
}

void DecisionTree::SetRangedCombatNode(RangedCombatCondition* node)
{
	m_rangedCombatNode = node;
}

TreeNode* DecisionTree::AddNode(TreeNode* parent, TreeNode* child_node, const TreeNodeType type)
{
	switch(type)
	{
	case TreeNodeType::LEFT_TREE_NODE:
		parent->m_pLeft = child_node;
		break;
	case TreeNodeType::RIGHT_TREE_NODE:
		parent->m_pRight = child_node;
		break;
	}
	child_node->m_pParent = parent;
	return child_node;
}

void DecisionTree::Display() const
{
	std::cout << "Decision Tree Nodes: " << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	for (auto node : m_treeNodeList)
	{
		std::cout << node->m_name << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}

void DecisionTree::Update()
{
	// Do something in play scene
}

void DecisionTree::Clean()
{
	for (auto node : m_treeNodeList)
	{
		delete node;
		node = nullptr;
	}
	m_treeNodeList.clear();
	m_treeNodeList.shrink_to_fit();

	m_LOSNode = nullptr;
	m_radiusNode = nullptr;
	m_closeCombatNode = nullptr;
}

// Traverse the tree in order
void DecisionTree::MakeDecision() const
{
	TreeNode* current_node = m_treeNodeList[0]; // Root node.

	// Traverse the tree down through each decision
	while (!current_node->m_isLeaf)
	{
		current_node = dynamic_cast<ConditionNode*>(current_node)->Condition() ? 
			(current_node->m_pRight) : (current_node->m_pLeft);
	}
	// Take Action
	dynamic_cast<ActionNode*>(current_node)->Action();
}

