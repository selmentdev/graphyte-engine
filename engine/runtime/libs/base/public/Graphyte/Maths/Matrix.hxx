#pragma once
#include <Graphyte/Maths/Simd.hxx>
#include <Graphyte/Maths/Types.hxx>

namespace Graphyte::Maths
{
    struct Vector2;
    struct Vector3;
    struct Vector4;
    struct Matrix;
    struct Quaternion;
    struct Plane;
}

namespace Graphyte::Maths
{
    struct Matrix final
    {
    public:
        MatrixFloat4x4 M;

    public:
        mathinline mathcall operator MatrixFloat4x4() const noexcept
        {
            return M;
        }

    public:
        static Matrix mathcall Load(const float4x4a* source) noexcept;
        static Matrix mathcall Load(const float4x3a* source) noexcept;
        static Matrix mathcall Load(const float3x4a* source) noexcept;

        static Matrix mathcall Load(const float4x4* source) noexcept;
        static Matrix mathcall Load(const float4x3* source) noexcept;
        static Matrix mathcall Load(const float3x4* source) noexcept;
        static Matrix mathcall Load(const float3x3* source) noexcept;

        static void mathcall Store(float4x4a* destination, Matrix m) noexcept;
        static void mathcall Store(float4x3a* destination, Matrix m) noexcept;
        static void mathcall Store(float3x4a* destination, Matrix m) noexcept;

        static void mathcall Store(float4x4* destination, Matrix m) noexcept;
        static void mathcall Store(float4x3* destination, Matrix m) noexcept;
        static void mathcall Store(float3x4* destination, Matrix m) noexcept;
        static void mathcall Store(float3x3* destination, Matrix m) noexcept;

    public:
        static bool mathcall IsEqual(Matrix m1, Matrix m2) noexcept;
        static bool mathcall IsNotEqual(Matrix m1, Matrix m2) noexcept;
        static bool mathcall IsNaN(Matrix m) noexcept;
        static bool mathcall IsInfinite(Matrix m) noexcept;
        static bool mathcall IsIdentity(Matrix m) noexcept;

    public:
        static Matrix mathcall Multiply(Matrix m1, Matrix m2) noexcept;
        static Matrix mathcall MultiplyTranspose(Matrix m1, Matrix m2) noexcept;
        static Matrix mathcall Transpose(Matrix m) noexcept;
        static Matrix mathcall Inverse(Vector4* determinant, Matrix m) noexcept;
        static Vector4 mathcall Determinant(Matrix m) noexcept;
        static bool mathcall Decompose(Vector4* out_scale, Quaternion* out_rotation, Vector4* out_translation, Matrix m) noexcept;

    public:
        static Matrix mathcall Identity() noexcept;
        static Matrix mathcall Make(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) noexcept;

    public:
        static Matrix mathcall Add(Matrix m1, Matrix m2) noexcept;
        static Matrix mathcall Subtract(Matrix m1, Matrix m2) noexcept;
        static Matrix mathcall Multiply(Matrix m, float scalar) noexcept;
        static Matrix mathcall Divide(Matrix m, float scalar) noexcept;
        static Matrix mathcall Negate(Matrix m) noexcept;

    public:
        static Matrix mathcall Translation(float x, float y, float z) noexcept;
        static Matrix mathcall Translation(Vector3 offset) noexcept;
        static Matrix mathcall Scaling(float x, float y, float z) noexcept;
        static Matrix mathcall Scaling(Vector3 scale) noexcept;
        static Matrix mathcall RotationX(float angle) noexcept;
        static Matrix mathcall RotationY(float angle) noexcept;
        static Matrix mathcall RotationZ(float angle) noexcept;
        static Matrix mathcall FromRollPitchYaw(float pitch, float yaw, float roll) noexcept;
        static Matrix mathcall FromRollPitchYaw(Vector3 angles) noexcept;
        static Matrix mathcall FromRotationNormal(Vector3 normal_axis, float angle) noexcept;
        static Matrix mathcall FromRotationAxis(Vector3 axis, float angle) noexcept;
        static Matrix mathcall FromRotationQuaternion(Quaternion q) noexcept;

    public:
        static Matrix mathcall Transformation2D(Vector2 scaling_origin, float scaling_orientation, Vector2 scaling, Vector2 rotation_origin, float rotation, Vector2 translation) noexcept;
        static Matrix mathcall AffineTransformation2D(Vector2 scaling, Vector2 rotation_origin, float rotation, Vector2 translation) noexcept;
        static Matrix mathcall Transformation(Vector3 scaling_origin, Quaternion scaling_orientation_quaternion, Vector3 scaling, Vector3 rotation_origin, Quaternion rotation_quaternion, Vector3 translation) noexcept;
        static Matrix mathcall AffineTransformation(Vector3 scaling, Vector3 rotation_origin, Quaternion rotation_quaternion, Vector3 translation) noexcept;

    public:
        //static Matrix mathcall Reflect(Plane reflection_plane) noexcept;
        //static Matrix mathcall Shadow(Plane shadow_plane, Vector4 light_position) noexcept;

    public:
        static Matrix mathcall LookAtLH(Vector3 eye_position, Vector3 focus_position, Vector3 up_direction) noexcept;
        static Matrix mathcall LookAtRH(Vector3 eye_position, Vector3 focus_position, Vector3 up_direction) noexcept;
        static Matrix mathcall LookToLH(Vector3 eye_position, Vector3 eye_direction, Vector3 up_direction) noexcept;
        static Matrix mathcall LookToRH(Vector3 eye_position, Vector3 eye_direction, Vector3 up_direction) noexcept;

        static Matrix mathcall PerspectiveLH(float width, float height, float z_near, float z_far) noexcept;
        static Matrix mathcall PerspectiveRH(float width, float height, float z_near, float z_far) noexcept;
        static Matrix mathcall PerspectiveFovLH(float fov_angle_y, float aspect_ratio, float z_near, float z_far) noexcept;
        static Matrix mathcall PerspectiveFovRH(float fov_angle_y, float aspect_ratio, float z_near, float z_far) noexcept;
        static Matrix mathcall PerspectiveOffCenterLH(float left, float right, float bottom, float top, float z_near, float z_far) noexcept;
        static Matrix mathcall PerspectiveOffCenterRH(float left, float right, float bottom, float top, float z_near, float z_far) noexcept;
        static Matrix mathcall OrthographicLH(float width, float height, float z_near, float z_far) noexcept;
        static Matrix mathcall OrthographicRH(float width, float height, float z_near, float z_far) noexcept;
        static Matrix mathcall OrthographicOffCenterLH(float left, float right, float bottom, float top, float z_near, float z_far) noexcept;
        static Matrix mathcall OrthographicOffCenterRH(float left, float right, float bottom, float top, float z_near, float z_far) noexcept;
    };

#if GRAPHYTE_MATH_ENABLE_OPERATORS

    mathinline bool mathcall operator== (Matrix m1, Matrix m2) noexcept
    {
        return Matrix::IsEqual(m1, m2);
    }

    mathinline bool mathcall operator!= (Matrix m1, Matrix m2) noexcept
    {
        return Matrix::IsNotEqual(m1, m2);
    }

    mathinline Matrix mathcall operator- (Matrix m) noexcept
    {
        return Matrix::Negate(m);
    }

    mathinline Matrix mathcall operator+ (Matrix m1, Matrix m2) noexcept
    {
        return Matrix::Add(m1, m2);
    }

    mathinline Matrix mathcall operator- (Matrix m1, Matrix m2) noexcept
    {
        return Matrix::Subtract(m1, m2);
    }

    mathinline Matrix mathcall operator* (Matrix m1, Matrix m2) noexcept
    {
        return Matrix::Multiply(m1, m2);
    }

    mathinline Matrix mathcall operator* (Matrix m, float scalar) noexcept
    {
        return Matrix::Multiply(m, scalar);
    }

    mathinline Matrix mathcall operator* (float scalar, Matrix m) noexcept
    {
        return Matrix::Multiply(m, scalar);
    }

    mathinline Matrix mathcall operator/ (Matrix m, float scalar) noexcept
    {
        return Matrix::Divide(m, scalar);
    }

    mathinline Matrix mathcall operator+= (Matrix& m1, Matrix m2) noexcept
    {
        m1 = Matrix::Add(m1, m2);
        return m1;
    }

    mathinline Matrix mathcall operator-= (Matrix& m1, Matrix m2) noexcept
    {
        m1 = Matrix::Subtract(m1, m2);
        return m1;
    }

    mathinline Matrix mathcall operator*= (Matrix& m1, Matrix m2) noexcept
    {
        m1 = Matrix::Multiply(m1, m2);
        return m1;
    }

    mathinline Matrix mathcall operator*= (Matrix& m, float scalar) noexcept
    {
        m = Matrix::Multiply(m, scalar);
        return m;
    }

    mathinline Matrix mathcall operator/= (Matrix& m, float scalar) noexcept
    {
        m = Matrix::Divide(m, scalar);
        return m;
    }

#endif
}

#include <Graphyte/Maths/Matrix.impl.hxx>
