#include <mutex>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "OpenGLUtils/Camera.hpp"

namespace VoxelFactory
{

class SafeCamera {
public:
    SafeCamera(glm::vec3 position = glm::vec3(0.0f),
                float zoom = 1.0f,
                float velocity = 10.0f)
        : _camera(position, zoom, velocity) {}

    glm::mat4 getTransformationMatrix() {
        std::lock_guard<std::mutex> lock(_mutex);
        return _camera.getTransformationMatrix();
    }

    void move(Camera::Direction direction, double deltaTime) {
        std::lock_guard<std::mutex> lock(_mutex);
        _camera.move(direction, deltaTime);
    }

    void rotateHorizontal(float yawDegrees) {
        std::lock_guard<std::mutex> lock(_mutex);
        _camera.rotateHorizontal(yawDegrees);
    }

    void rotateVertical(float pitchDegrees) {
        std::lock_guard<std::mutex> lock(_mutex);
        _camera.rotateVertical(pitchDegrees);
    }

    void setTargetPosition(glm::vec3 position) {
        std::lock_guard<std::mutex> lock(_mutex);
        _camera.setTargetPosition(position);
    }
    
    void zoom(float zoom) {
        std::lock_guard<std::mutex> lock(_mutex);
        _camera.zoom(zoom);
    }

    void setRotation(float yawDegrees, float pitchDegrees) {
        std::lock_guard<std::mutex> lock(_mutex);
        _camera.setRotation(yawDegrees, pitchDegrees);
    }

    void setZoom(float zoom) {
        std::lock_guard<std::mutex> lock(_mutex);
        _camera.setZoom(zoom);
    }

    glm::vec3 getTargetPosition() const {
        std::lock_guard<std::mutex> lock(_mutex);
        return _camera.getTargetPosition();
    }

    float getYaw() const {
        std::lock_guard<std::mutex> lock(_mutex);
        return _camera.getYaw();
    }

    float getPitch() const {
        std::lock_guard<std::mutex> lock(_mutex);
        return _camera.getPitch();
    }

    float getZoom() const {
        std::lock_guard<std::mutex> lock(_mutex);
        return _camera.getZoom();
    }

private:
    mutable std::mutex _mutex;
    Camera _camera;
};

} // namespace VoxelFactory

