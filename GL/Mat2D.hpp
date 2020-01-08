#include <glm/glm.hpp>
#include <cmath>
#include <array>
glm::mat2 RotMat(const float& angle);
glm::mat2 ScaleMat(const float& x, const float& y);
glm::mat2 ShearMat(const float& x, const float& y);
float angle(const glm::mat2& matrix);
glm::vec2 scale(const glm::mat2& matrix);
glm::vec2 shear(const glm::mat2& matrix);
std::array<float, 5> decomp(const glm::mat2& matrix);
glm::mat2 recompose(const std::array<float,5>& data);