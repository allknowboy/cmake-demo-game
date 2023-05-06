#pragma once

#include <glm/glm.hpp>

static const glm::vec3 Cube_P[8] = {
        glm::vec3{ -1.0f, -1.0f, 1.0f},
        glm::vec3{ 1.0f, -1.0f, 1.0f},
        glm::vec3{ 1.0f, 1.0f, 1.0f},
        glm::vec3{ -1.0f, 1.0f, 1.0f},
        glm::vec3{ 1.0f, -1.0f, -1.0f},
        glm::vec3{ -1.0f, -1.0f, -1.0f},
        glm::vec3{ -1.0f, 1.0f, -1.0f},
        glm::vec3{ 1.0f, 1.0f, -1.0f}
};

static const glm::vec3 kPositions[36] = {
        // 前面
        glm::vec3(Cube_P[0]),
        glm::vec3(Cube_P[1]),
        glm::vec3(Cube_P[2]),
        glm::vec3(Cube_P[2]),
        glm::vec3(Cube_P[3]),
        glm::vec3(Cube_P[0]),
        // 后面
        glm::vec3(Cube_P[4]),
        glm::vec3(Cube_P[5]),
        glm::vec3(Cube_P[6]),
        glm::vec3(Cube_P[6]),
        glm::vec3(Cube_P[7]),
        glm::vec3(Cube_P[4]),
        // 左边
        glm::vec3(Cube_P[5]),
        glm::vec3(Cube_P[0]),
        glm::vec3(Cube_P[3]),
        glm::vec3(Cube_P[3]),
        glm::vec3(Cube_P[6]),
        glm::vec3(Cube_P[5]),
        // 右边
        glm::vec3(Cube_P[1]),
        glm::vec3(Cube_P[4]),
        glm::vec3(Cube_P[7]),
        glm::vec3(Cube_P[7]),
        glm::vec3(Cube_P[2]),
        glm::vec3(Cube_P[1]),
        // 上边
        glm::vec3(Cube_P[3]),
        glm::vec3(Cube_P[2]),
        glm::vec3(Cube_P[7]),
        glm::vec3(Cube_P[7]),
        glm::vec3(Cube_P[6]),
        glm::vec3(Cube_P[3]),
        // 下边
        glm::vec3(Cube_P[5]),
        glm::vec3(Cube_P[4]),
        glm::vec3(Cube_P[1]),
        glm::vec3(Cube_P[1]),
        glm::vec3(Cube_P[0]),
        glm::vec3(Cube_P[5]),
};

static const glm::vec4 kColors[6] = {
        glm::vec4{ 1.f, 0.f, 0.f, 1.f},
        glm::vec4{ 0.f, 1.f, 0.f, 1.f},
        glm::vec4{ 0.f, 0.f, 1.f, 1.f},
        glm::vec4{ 0.f, 0.f, 1.f, 1.f},
        glm::vec4{ 0.f, 1.f, 0.f, 1.f},
        glm::vec4{ 1.f, 0.f, 0.f, 1.f}
};

static const glm::vec2 kUvs[36] = {
        // 前面
        glm::vec2{ 0.25f, 0.25f},
        glm::vec2{ 0.25f, 0.5f},
        glm::vec2{ 0.f, 0.5f},
        glm::vec2{ 0.f, 0.5f},
        glm::vec2{ 0.f, 0.25f},
        glm::vec2{ 0.25f, 0.25f},
        // 后面
        glm::vec2{ 0.5f, 0.5f},
        glm::vec2{ 0.5f, 0.25f},
        glm::vec2{ 0.75f, 0.25f},
        glm::vec2{ 0.75f, 0.25f},
        glm::vec2{ 0.75f, 0.5f},
        glm::vec2{ 0.5f, 0.5f},
        // 左边
        glm::vec2{ 0.5f, 0.25f},
        glm::vec2{ 0.25f, 0.25f},
        glm::vec2{ 0.25f, 0.f},
        glm::vec2{ 0.25f, 0.f},
        glm::vec2{ 0.5f, 0.f},
        glm::vec2{ 0.5f, 0.25f},
        // 右边
        glm::vec2{ 0.25f, 0.5f},
        glm::vec2{ 0.5f, 0.5f},
        glm::vec2{ 0.5f, 0.75f},
        glm::vec2{ 0.5f, 0.75f},
        glm::vec2{ 0.25f, 0.75f},
        glm::vec2{ 0.25f, 0.5f},
        // 上面
        glm::vec2{ 1.f, 0.25f},
        glm::vec2{ 1.f, 0.5f},
        glm::vec2{ 0.75f, 0.5f},
        glm::vec2{ 0.75f, 0.5f},
        glm::vec2{ 0.75f, 0.25f},
        glm::vec2{ 1.0f, 0.25f},
        // 下面
        glm::vec2{ 0.5f, 0.25f},
        glm::vec2{ 0.5f, 0.5f},
        glm::vec2{ 0.25f, 0.5f},
        glm::vec2{ 0.25f, 0.5f},
        glm::vec2{ 0.25f, 0.25f},
        glm::vec2{ 0.5f, 0.25f},
};