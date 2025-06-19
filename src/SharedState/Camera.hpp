#pragma once
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace VoxelFactory
{

constexpr float MIN_ZOOM = 10.0f;
constexpr float MAX_ZOOM = 100.0f;

class Camera
{
    public:
        enum class Direction {
            Up,
            Down,
            Left,
            Right
        };

        Camera(glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f),
            float yaw = 45.0f, float pitch = 45.0f,
            float zoom = 1.0f, float velocity = 1.0f);

        glm::mat4 getTransformationMatrix(void);

        void move(Direction direction, double deltaTime);
        void rotateHorizontal(float yawDegrees);
        void rotateVertical(float pitchDegrees);
        void zoom(float zoom);

        void setTargetPosition(glm::vec3 position);
        void setRotation(float yawDegrees, float pitchDegrees);
        void setZoom(float zoom);
        void setVelocity(float velocity);

        glm::vec3 getTargetPosition(void) const;
        float getYaw(void) const;
        float getPitch(void) const;
        float getZoom(void) const;
        float getVelocity(void) const;

    private:
        glm::vec3 _target;
        glm::vec3 _position;

        float _velocity;
        float _zoom;

        float _yaw;    // in radians
        float _pitch;  // in radians

        glm::mat4 _cachedViewMatrix;
        bool _dirty;

        void _computePosition();
};
}
