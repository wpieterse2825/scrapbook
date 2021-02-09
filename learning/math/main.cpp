#include <iostream>

struct Vector {
    float x;
    float y;
    float z;
};

float DotProduct(const Vector lhs, const Vector rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

void DotProductTestSide() {
    auto v_left = Vector {
      .x = -1.0f,
      .y = 0.0f,
      .z = 0.0f,
    };

    auto v_right = Vector {
      .x = +1.0f,
      .y = 0.0f,
      .z = 0.0f,
    };

    auto v_test = Vector {
      .x = -20.0f,
      .y = 0.0f,
      .z = 0.0f,
    };

    auto v_result_1 = DotProduct(v_test, v_left);
    auto v_result_2 = DotProduct(v_test, v_right);

    auto side_1 = v_result_1 > 0;
    auto side_2 = v_result_2 > 0;

    std::cout << side_1 << " - " << v_result_1 << std::endl;
    std::cout << side_2 << " - " << v_result_2 << std::endl;
}

int main() {
    DotProductTestSide();

    return 0;
}
