#include "Camera.h"
#include "..\TileMap\GameMap.h"
#include "..\Global\GlobalProperties.h"

Camera *Camera::s_Instance = nullptr;

void Camera::Update(float dt)
{
    if (m_Target != nullptr)
    {
        // Centralizar a visão da câmera no alvo
        m_ViewBox.x = m_Target->x - (SCREEN_WIDTH / 2);
        m_ViewBox.y = m_Target->y - (SCREEN_HEIGHT / 2);
    }
    // Garantir que a visão da câmera permaneça dentro dos limites do nível
    // std::cout << "m_LimitPosition: " << m_LimitPosition.x << " , " << m_LimitPosition.y << std::endl;
    // std::cout << "m_LimitDimension: " << m_LimitDimension.x << " , " << m_LimitDimension.y << std::endl;

    if (m_ViewBox.x < m_LimitPosition.x)
    {
        m_ViewBox.x = m_LimitPosition.x;
    }

    if (m_ViewBox.y < m_LimitPosition.y)
    {
        m_ViewBox.y = m_LimitPosition.y;
    }

    if (m_ViewBox.x > m_LimitPosition.x + m_LimitDimension.x * DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH - (SCREEN_WIDTH))
    {
        m_ViewBox.x = m_LimitPosition.x + m_LimitDimension.x * DEFAULT_UNIT_TO_PIXELS * SCALE_WIDTH - (SCREEN_WIDTH);
    }

    if (m_ViewBox.y > m_LimitPosition.y + m_LimitDimension.y * DEFAULT_UNIT_TO_PIXELS * SCALE_HEIGHT - (SCREEN_HEIGHT))
    {
        m_ViewBox.y = m_LimitPosition.y + m_LimitDimension.y * DEFAULT_UNIT_TO_PIXELS * SCALE_HEIGHT - (SCREEN_HEIGHT);
    }

    m_Position = Vector(m_ViewBox.x, m_ViewBox.y);
    // std::cout << "Camera Position: " << m_Position.x << " , " << m_Position.y << std::endl;
}
