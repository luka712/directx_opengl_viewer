#include "UIControl.hpp"


namespace Viewer
{
	void UIControl::AddChild(UIControl* child)
	{
		m_children.push_back(child);
		child->m_parent = this;
	}
}

