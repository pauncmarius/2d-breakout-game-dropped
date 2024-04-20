#ifndef MAT4_H
#define MAT4_H

class Mat4 {
public:
    float data[16]; // Column-major order

    // Default constructor initializes to identity matrix
    Mat4() {
        for (int i = 0; i < 16; i++) {
            data[i] = 0.0f;
        }
        data[0] = data[5] = data[10] = data[15] = 1.0f;
    }

    // Creates a translation matrix from an existing matrix
    static Mat4 translate(const Mat4& mat, float x, float y) {
        Mat4 result = mat;
        result.data[12] += x;
        result.data[13] += y;
        return result;
    }

    // Returns a pointer to the matrix data
    const float* ptr() const {
        return data;
    }
};

#endif // MAT4_H
