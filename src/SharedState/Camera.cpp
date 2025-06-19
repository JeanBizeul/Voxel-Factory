#include "Camera.hpp"

#include "glm/gtc/matrix_transform.hpp"

VoxelFactory::Camera::Camera(glm::vec3 target,
float yaw, float pitch,
float zoom, float velocity)
    : _target(target),
      _yaw(yaw), _pitch(pitch),
      _zoom(zoom), _velocity(velocity)
{
    _computePosition();
}

glm::mat4 VoxelFactory::Camera::getTransformationMatrix()
{
    if (_dirty) {
        glm::vec3 direction = glm::normalize(_target - _position);
        glm::vec3 right = glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
        glm::vec3 up = glm::cross(right, direction);
        _cachedViewMatrix = glm::lookAt(_position, _target, up);
        _dirty = false;
    }

    return _cachedViewMatrix;
}

void VoxelFactory::Camera::move(Direction direction, double deltaTime)
{
    _dirty = true;
    glm::vec3 forward = glm::normalize(_target - _position);
    forward.y = 0.0f; // Stay horizontal
    forward = glm::normalize(forward);
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

    switch (direction)
    {
    case Direction::Up :
        _target += forward * _velocity;
        break;
    case Direction::Down :
        _target -= forward * _velocity;
        break;
    case Direction::Right :
        _target += right * _velocity;
        break;
    case Direction::Left :
        _target -= right * _velocity;
        break;
    }
    _computePosition();
}

void VoxelFactory::Camera::rotateHorizontal(float yawDegrees)
{
    _dirty = true;
    _yaw += glm::radians(yawDegrees);
    _yaw = glm::mod(_yaw + glm::pi<float>(), glm::two_pi<float>());
    _yaw -= glm::pi<float>();
    _computePosition();
}

void VoxelFactory::Camera::rotateVertical(float pitchDegrees)
{
    _dirty = true;
    _pitch = glm::clamp(_pitch + glm::radians(pitchDegrees),
        glm::radians(-89.0f), glm::radians(89.0f));
    _computePosition();
}

void VoxelFactory::Camera::zoom(float zoom)
{
    _dirty = true;
    _zoom = glm::clamp(_zoom + zoom, MIN_ZOOM, MAX_ZOOM);
    _computePosition();
}

void VoxelFactory::Camera::_computePosition()
{
    _position.x = _target.x + _zoom * cos(_pitch) * sin(_yaw);
    _position.y = _target.y + _zoom * sin(_pitch);
    _position.z = _target.z + _zoom * cos(_pitch) * cos(_yaw);
}

void VoxelFactory::Camera::setTargetPosition(glm::vec3 position)
{
    _dirty = true;
    _target = position;
    _computePosition();
}

void VoxelFactory::Camera::setRotation(float yawDegrees, float pitchDegrees)
{
    _dirty = true;
    _yaw = glm::radians(yawDegrees);
    _yaw = glm::mod(_yaw + glm::pi<float>(), glm::two_pi<float>());
    _yaw -= glm::pi<float>();

    _pitch = glm::clamp(_pitch + glm::radians(pitchDegrees),
        glm::radians(-89.0f), glm::radians(89.0f));
    _computePosition();
}

void VoxelFactory::Camera::setZoom(float zoom)
{
    _dirty = true;
    _zoom = glm::clamp(zoom, MIN_ZOOM, MAX_ZOOM);
    _computePosition();
}

void VoxelFactory::Camera::setVelocity(float velocity)
{
    _velocity = velocity;
}

glm::vec3 VoxelFactory::Camera::getTargetPosition(void) const
{
    return _target;
}

float VoxelFactory::Camera::getYaw(void) const
{
    return _yaw;
}

float VoxelFactory::Camera::getPitch(void) const
{
    return _pitch;
}

float VoxelFactory::Camera::getZoom(void) const
{
    return _zoom;
}

float VoxelFactory::Camera::getVelocity(void) const
{
    return _velocity;
}
