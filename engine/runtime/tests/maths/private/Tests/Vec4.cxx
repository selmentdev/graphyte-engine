#include "Test.Maths.pch.hxx"
#include <Graphyte/Maths.hxx>

TEST_CASE("Maths / Transforms")
{
    using namespace Graphyte::Maths;

    SECTION("Affine Transforms")
    {
        SECTION("2D")
        {
            Vector2 const scaling = Make<Vector2>(1.3f, -3.4f);
            Vector2 const rotation_origin = Make<Vector2>(3.4f, 1.7f);
            float const rotation = DegreesToRadians(-60.0f);
            Vector2 const translation = Make<Vector2>(-2.3f, 3.3f);

            Matrix const m = CreateAffineTransform2D(
                scaling,
                rotation_origin,
                rotation,
                translation
            );

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.649999917f });
            CHECK(GetY(GetBaseX(m)) == Approx{ -1.12583303f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseY(m)) == Approx{ -2.94448662f });
            CHECK(GetY(GetBaseY(m)) == Approx{ -1.69999981f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseW(m)) == Approx{ -2.07224298f });
            CHECK(GetY(GetBaseW(m)) == Approx{ 7.09448671f });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
        }

        SECTION("3D")
        {
            Vector3 const scaling = Make<Vector3>(1.1f, 1.1f, 1.1f);
            Vector3 const rotation_origin = Make<Vector3>(3.4f, 1.7f, -2.3f);
            Quaternion const rotation = CreateFromAxisAngle(Make<Vector3>(2.1f, 1.1f, -3.3f), DegreesToRadians(-60.0f));
            Vector3 const translation = Make<Vector3>(3.3f, -1.3f, 2.1f);

            Matrix const m = CreateAffineTransform(
                scaling,
                rotation_origin,
                rotation,
                translation
            );

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.696910977f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.850637615f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0270346422f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseY(m)) == Approx{ -0.696730852f });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.590308905f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ -0.613271236f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -0.488754869f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.371417761f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.912780166f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseW(m)) == Approx{ 4.60073566f });
            CHECK(GetY(GetBaseW(m)) == Approx{ -2.36493826f });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 2.57276130f });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
        }
    }

    SECTION("Transforms")
    {
        SECTION("2D")
        {
            Vector2 const scaling_origin = Make<Vector2>(-2.1f, 1.3f);
            float const scaling_orientation = DegreesToRadians(45.0f);
            Vector2 const scaling = Make<Vector2>(1.1f, 1.1f);
            Vector2 const rotation_origin = Make<Vector2>(3.4f, 1.7f);
            float const rotation = DegreesToRadians(-60.0f);
            Vector2 const translation = Make<Vector2>(3.3f, -1.3f);

            Matrix const m = CreateTransform2D(
                scaling_origin,
                scaling_orientation,
                scaling,
                rotation_origin,
                rotation,
                translation
            );

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.549999893f });
            CHECK(GetY(GetBaseX(m)) == Approx{ -0.952627897f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.952627897f });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.549999893f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseW(m)) == Approx{ 3.52017379f });
            CHECK(GetY(GetBaseW(m)) == Approx{ 2.24762177f });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
        }

        SECTION("3D")
        {
            Vector3 const scaling_origin = Make<Vector3>(-2.1f, 1.3f, -3.4f);
            Quaternion const scaling_orientation = CreateFromAxisAngle(Make<Vector3>(-2.1f, 1.1f, 2.3f), DegreesToRadians(45.0f));
            Vector3 const scaling = Make<Vector3>(1.1f, 1.1f, 1.1f);
            Vector3 const rotation_origin = Make<Vector3>(3.4f, 1.7f, -2.3f);
            Quaternion const rotation = CreateFromAxisAngle(Make<Vector3>(2.1f, 1.1f, -3.3f), DegreesToRadians(-60.0f));
            Vector3 const translation = Make<Vector3>(3.3f, -1.3f, 2.1f);

            Matrix const m = CreateTransform(
                scaling_origin,
                scaling_orientation,
                scaling,
                rotation_origin,
                rotation,
                translation
            );

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.696911037f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.850637555f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0270346627f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseY(m)) == Approx{ -0.696730852f });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.590308845f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ -0.613271236f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -0.488754809f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.371417731f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.912780046f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseW(m)) == Approx{ 4.66505337f });
            CHECK(GetY(GetBaseW(m)) == Approx{ -2.15750575f });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 2.93253255f });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
        }
    }
}

TEST_CASE("Maths / Rotations / Matrix rotations around arbitrary axis")
{
    using namespace Graphyte::Maths;

    SECTION("Case 1")
    {
        Vector3 const axis = Make<Vector3>(1.0f, -2.0f, 3.0f);

        Matrix m = Matrix_CreateFromAxisAngle(axis, DegreesToRadians(45.0f));

        CHECK(GetX(GetBaseX(m)) == Approx{ 0.7280276f });
        CHECK(GetY(GetBaseX(m)) == Approx{ 0.5251047f });
        CHECK(GetZ(GetBaseX(m)) == Approx{ 0.44072793f });
        CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseY(m)) == Approx{ -0.608788610f });
        CHECK(GetY(GetBaseY(m)) == Approx{ 0.790790498f });
        CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0634565353f });
        CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseZ(m)) == Approx{ -0.315201640f });
        CHECK(GetY(GetBaseZ(m)) == Approx{ -0.31507931f }.margin(0.001f));
        CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.895395219f });
        CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetY(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
    }

    SECTION("Case 2")
    {
        Vector3 const axis = Make<Vector3>(-1.0f, 3.0f, -3.0f);

        Matrix m = Matrix_CreateFromAxisAngle(axis, DegreesToRadians(60.0f));

        CHECK(GetX(GetBaseX(m)) == Approx{ 0.526315749f });
        CHECK(GetY(GetBaseX(m)) == Approx{ -0.674986959f });
        CHECK(GetZ(GetBaseX(m)) == Approx{ -0.517092228f });
        CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseY(m)) == Approx{ 0.517092228f });
        CHECK(GetY(GetBaseY(m)) == Approx{ 0.736842036f });
        CHECK(GetZ(GetBaseY(m)) == Approx{ -0.43552199f});
        CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseZ(m)) == Approx{ 0.674986959f });
        CHECK(GetY(GetBaseZ(m)) == Approx{ -0.0381622612f });
        CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.736842036 });
        CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetY(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
    }
}

TEST_CASE("Maths / Rotations / Matrix <-> Quaternion")
{
    using namespace Graphyte::Maths;

    constexpr float const angle_step = 5.0f;

    Vector3 const v = Make<Vector3>(1.0f, -2.0f, 3.0f);

    SECTION("Rotation X")
    {
        Vector3 const axis = UnitX<Vector3>();

        for (float angle = -360.0f; angle <= 360.0f; angle += angle_step)
        {
            float const radians = DegreesToRadians(angle);
            Matrix const m = CreateRotationX(radians);
            Quaternion const q = CreateFromNormalAngle(axis, radians);

            //
            // Check if quaternion rotates vector as well as matrix.
            //

            Vector3 const vm = Transform(v, m);
            Vector3 const vq = Rotate(v, q);

            CHECK(GetX(vm) == Approx{ GetX(vq) });
            CHECK(GetY(vm) == Approx{ GetY(vq) });
            CHECK(GetZ(vm) == Approx{ GetZ(vq) });


            //
            // Convert quaternion back to matrix and check whether rotation will match.
            //

            Quaternion const mq = CreateFromMatrix(m);
            Vector3 const vmq = Rotate(v, mq);

            CHECK(GetX(vmq) == Approx{ GetX(vq) });
            CHECK(GetY(vmq) == Approx{ GetY(vq) });
            CHECK(GetZ(vmq) == Approx{ GetZ(vq) });

            Matrix const qm = CreateFromQuaternion(q);
            Vector3 const vqm = Transform(v, qm);

            CHECK(GetX(vqm) == Approx{ GetX(vq) });
            CHECK(GetY(vqm) == Approx{ GetY(vq) });
            CHECK(GetZ(vqm) == Approx{ GetZ(vq) });
        }
    }

    SECTION("Rotation Y")
    {
        Vector3 const axis = UnitY<Vector3>();

        for (float angle = -360.0f; angle <= 360.0f; angle += angle_step)
        {
            float const radians = DegreesToRadians(angle);
            Matrix const m = CreateRotationY(radians);
            Quaternion const q = CreateFromNormalAngle(axis, radians);

            //
            // Check if quaternion rotates vector as well as matrix.
            //

            Vector3 const vm = Transform(v, m);
            Vector3 const vq = Rotate(v, q);

            CHECK(GetX(vm) == Approx{ GetX(vq) });
            CHECK(GetY(vm) == Approx{ GetY(vq) });
            CHECK(GetZ(vm) == Approx{ GetZ(vq) });


            //
            // Convert quaternion back to matrix and check whether rotation will match.
            //

            Quaternion const mq = CreateFromMatrix(m);
            Vector3 const vmq = Rotate(v, mq);

            CHECK(GetX(vmq) == Approx{ GetX(vq) });
            CHECK(GetY(vmq) == Approx{ GetY(vq) });
            CHECK(GetZ(vmq) == Approx{ GetZ(vq) });

            Matrix const qm = CreateFromQuaternion(q);
            Vector3 const vqm = Transform(v, qm);

            CHECK(GetX(vqm) == Approx{ GetX(vq) });
            CHECK(GetY(vqm) == Approx{ GetY(vq) });
            CHECK(GetZ(vqm) == Approx{ GetZ(vq) });
        }
    }

    SECTION("Rotation Z")
    {
        Vector3 const axis = UnitZ<Vector3>();

        for (float angle = -360.0f; angle <= 360.0f; angle += angle_step)
        {
            float const radians = DegreesToRadians(angle);
            Matrix const m = CreateRotationZ(radians);
            Quaternion const q = CreateFromNormalAngle(axis, radians);

            //
            // Check if quaternion rotates vector as well as matrix.
            //

            Vector3 const vm = Transform(v, m);
            Vector3 const vq = Rotate(v, q);

            CHECK(GetX(vm) == Approx{ GetX(vq) });
            CHECK(GetY(vm) == Approx{ GetY(vq) });
            CHECK(GetZ(vm) == Approx{ GetZ(vq) });


            //
            // Convert quaternion back to matrix and check whether rotation will match.
            //

            Quaternion const mq = CreateFromMatrix(m);
            Vector3 const vmq = Rotate(v, mq);

            CHECK(GetX(vmq) == Approx{ GetX(vq) });
            CHECK(GetY(vmq) == Approx{ GetY(vq) });
            CHECK(GetZ(vmq) == Approx{ GetZ(vq) });

            Matrix const qm = CreateFromQuaternion(q);
            Vector3 const vqm = Transform(v, qm);

            CHECK(GetX(vqm) == Approx{ GetX(vq) });
            CHECK(GetY(vqm) == Approx{ GetY(vq) });
            CHECK(GetZ(vqm) == Approx{ GetZ(vq) });
        }
    }
}

TEST_CASE("Maths / Matrix / Rotations")
{
    using namespace Graphyte::Maths;

    SECTION("Rotation X")
    {
        Vector3 const v = Make<Vector3>(1.0f, -2.0f, 3.0f);

        SECTION("angle = 0 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(0.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0F });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0F });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -30 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(-30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.866025f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ -0.5F });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.5F });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.866025f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 30 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.866025f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.5f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ -0.5f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.866025f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -45 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(-45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 45 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -90 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(-90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetZ(GetBaseY(m)) == Approx{ -1.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 90 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetZ(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ -1.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -135 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(-135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 135 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }
    }

    SECTION("Rotation Y")
    {
        Vector3 const v = Make<Vector3>(3.0f, 1.0f, -2.0);

        SECTION("angle = 0 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(0.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0F });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0F });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -30 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(-30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.866025f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.5F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -0.5f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.866025f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 30 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.866025f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ -0.5f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.5f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.866025f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -45 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(-45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 45 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -90 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(-90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.0F }.margin(0.001f));
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -1.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 90 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.0F }.margin(0.001f));
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ -1.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -135 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(-135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 135 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }
    }

    SECTION("Rotation Z")
    {
        Vector3 const v = Make<Vector3>(-2.0f, 3.0f, 1.0f);

        SECTION("angle = 0 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(0.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0F });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0F });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -30 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(-30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.866025f });
            CHECK(GetY(GetBaseX(m)) == Approx{ -0.5F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.5F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.866025f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 30 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.866025f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.5F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ -0.5F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.866025f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -45 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(-45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 45 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -90 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(-90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.0F }.margin(0.001f));
            CHECK(GetY(GetBaseX(m)) == Approx{ -1.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 90 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.0F }.margin(0.001f));
            CHECK(GetY(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ -1.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -135 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(-135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 135 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ -0.7071067f});
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0f });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
        }
    }
}


TEST_CASE("Maths / Vector4 / Vector4 Cross Product")
{
    using namespace Graphyte::Maths;

    Vector4 v0 = Make<Vector4>(1.0F, 2.0F, 1.0F, 3.0F);
    Vector4 v1 = Make<Vector4>(3.0F, 1.0F, 3.0F, 5.0F);
    Vector4 v2 = Make<Vector4>(2.0F, 2.0F, 3.0F, 2.0F);
    Vector4 v3 = Make<Vector4>(-2.0F, 2.0F, -3.0F, 2.0F);

    SECTION("cross(v0, v1, v2)")
    {
        Vector4 r = Cross(v0, v1, v2);

        CHECK(GetX(r) == -19.0F);
        CHECK(GetY(r) == -4.0F);
        CHECK(GetZ(r) == 12.0F);
        CHECK(GetW(r) == 5.0F);
    }

    SECTION("cross(v1, v0, v2)")
    {
        Vector4 r = Cross(v1, v0, v2);

        CHECK(GetX(r) == 19.0F);
        CHECK(GetY(r) == 4.0F);
        CHECK(GetZ(r) == -12.0F);
        CHECK(GetW(r) == -5.0F);
    }

    SECTION("cross(v1, v2, v3)")
    {
        Vector4 r = Cross(v1, v2, v3);

        CHECK(GetX(r) == -48.0F);
        CHECK(GetY(r) == -12.0F);
        CHECK(GetZ(r) == 32.0F);
        CHECK(GetW(r) == 12.0F);
    }

    SECTION("cross(v2, v3, v0)")
    {
        Vector4 r = Cross(v2, v3, v0);

        CHECK(GetX(r) == -12.0F);
        CHECK(GetY(r) == -4.0F);
        CHECK(GetZ(r) == 8.0F);
        CHECK(GetW(r) == 4.0F);
    }
}


TEST_CASE("BitCast between floating type")
{
    using namespace Graphyte;

    CHECK(BitCast<uint32_t>(1.0f) == 0x3f800000u);
    CHECK(BitCast<uint32_t>(12.5f) == 0x41480000u);
    CHECK(BitCast<uint32_t>(1337.0f) == 0x44a72000u);
    CHECK(BitCast<uint32_t>(-14.25f) == 0xc1640000u);

    CHECK(BitCast<float>(0x3f800000u) == 1.0f);
    CHECK(BitCast<float>(0x41480000u) == 12.5f);
    CHECK(BitCast<float>(0x44a72000u) == 1337.0f);
    CHECK(BitCast<float>(0xc1640000u) == -14.25f);
}


TEST_CASE("Maths / Vector / Copy Sign")
{
    using namespace Graphyte::Maths;

    Vector4 const vn = Make<Vector4>(-1.0F, 2.0F, 3.0F, -4.0F);
    Vector4 const vs = Make<Vector4>(1.0F, 1.0F, -1.0F, -1.0F);
    Vector4 const vc = CopySign(vn, vs);

    CHECK(GetX(vc) == 1.0F);
    CHECK(GetY(vc) == 2.0F);
    CHECK(GetZ(vc) == -3.0F);
    CHECK(GetW(vc) == -4.0F);

    float const sn = -1.0F;
    float const ss = 1.0F;
    float const sc = CopySign(sn, ss);

    CHECK(sc == 1.0F);
}

TEST_CASE("Maths / Matrix Invertability")
{
    using namespace Graphyte::Maths;

    auto test = [](Float4x4A const& src, Vector4 cdet1, Vector4 cdet2, Vector4 epsilon)
    {
        Vector4 det1{};
        Vector4 det2{};

        Float4x4A work{};
        Matrix original = Load<Matrix>(&src);

        Matrix inverted = Inverse(original, &det1);
        Store<Matrix>(&work, inverted);

        CHECK(IsEqual(det1, cdet1, epsilon));


        Matrix reconstructed = Inverse(inverted, &det2);
        Store<Matrix>(&work, reconstructed);

        CHECK(IsEqual(det2, cdet2, epsilon));

        CHECK(IsEqual(GetBaseX(reconstructed), GetBaseX(original), epsilon));
        CHECK(IsEqual(GetBaseY(reconstructed), GetBaseY(original), epsilon));
        CHECK(IsEqual(GetBaseZ(reconstructed), GetBaseZ(original), epsilon));
        CHECK(IsEqual(GetBaseW(reconstructed), GetBaseW(original), epsilon));
    };

    test(
        Float4x4A{ { {
            2.0F, 0.0F, 0.0F, 0.0F,
            0.0F, 1.0F, 0.0F, 0.0F,
            0.0F, 0.0F, 1.0F, 0.0F,
            0.0F, 0.0F, 0.0F, 1.0F,
        } } },
        Replicate<Vector4>(2.0F),
        Replicate<Vector4>(0.5F),
        Epsilon<Vector4>()
    );

    test(
        Float4x4A{ { {
            1.0F, 3.0F, 1.0F, 4.0F,
            3.0F, 9.0F, 5.0F, 15.0F,
            0.0F, 2.0F, 1.0F, 1.0F,
            0.0F, 4.0F, 2.0F, 3.0F,
        } } },
        Replicate<Vector4>(-4.0F),
        Replicate<Vector4>(-0.25F),
        Epsilon<Vector4>()
    );

    test(
        Float4x4A{ { {
            5.0F, -7.0F, 2.0F, 2.0F,
            0.0F, 3.0F, 0.0F, -4.0F,
            -5.0F, -8.0F, 0.0F, 3.0F,
            0.0F, 5.0F, 0.0F, -6.0F,
        } } },
        Replicate<Vector4>(20.0F),
        Replicate<Vector4>(0.05F),
        Replicate<Vector4>(0.01F)
    );

}

TEST_CASE("Maths / Fresnel Term")
{
    using namespace Graphyte::Maths;

    SECTION("index = 0.5")
    {
        Vector4 const r0a = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(0.0F),
                DegreesToRadians(30.0F),
                DegreesToRadians(45.0F),
                DegreesToRadians(60.0F)
                )),
            Replicate<Vector4>(0.5F)
        );

        CHECK(GetX(r0a) == Approx{ 0.111111112F }.margin(0.001F));
        CHECK(GetY(r0a) == Approx{ 1.0F }.margin(0.01F));
        CHECK(GetZ(r0a) == Approx{ 0.0151518816F }.margin(0.001F));
        CHECK(GetW(r0a) == Approx{ 0.0166181885F }.margin(0.001F));

        Vector4 const r0b = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(90.0F),
                DegreesToRadians(135.0F),
                DegreesToRadians(180.0F),
                DegreesToRadians(225.0F)
                )),
            Replicate<Vector4>(0.5F)
        );

        CHECK(GetX(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetY(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetZ(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetW(r0b) == Approx{ 1.0F }.margin(0.001F));

        Vector4 const r0c = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(-30.0F),
                DegreesToRadians(-45.0F),
                DegreesToRadians(-60.0F),
                DegreesToRadians(-90.0F)
                )),
            Replicate<Vector4>(0.5F)
        );

        CHECK(GetX(r0c) == Approx{ 1.0F }.margin(0.01F));
        CHECK(GetY(r0c) == Approx{ 0.0151518816F }.margin(0.001F));
        CHECK(GetZ(r0c) == Approx{ 0.0166181885F }.margin(0.001F));
        CHECK(GetW(r0c) == Approx{ 1.0F }.margin(0.001F));
    }

    SECTION("index = 1")
    {
        Vector4 const r0a = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians( 0.0F),
                DegreesToRadians(30.0F),
                DegreesToRadians(45.0F),
                DegreesToRadians(60.0F)
                )),
            Replicate<Vector4>(1.0F)
        );

        CHECK(GetX(r0a) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetY(r0a) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetZ(r0a) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetW(r0a) == Approx{ 0.0F }.margin(0.001F));

        Vector4 const r0b = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians( 90.0F),
                DegreesToRadians(135.0F),
                DegreesToRadians(180.0F),
                DegreesToRadians(225.0F)
                )),
            Replicate<Vector4>(1.0F)
        );

        CHECK(GetX(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetY(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetZ(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetW(r0b) == Approx{ 1.0F }.margin(0.001F));

        Vector4 const r0c = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(-30.0F),
                DegreesToRadians(-45.0F),
                DegreesToRadians(-60.0F),
                DegreesToRadians(-90.0F)
                )),
            Replicate<Vector4>(1.0F)
        );

        CHECK(GetX(r0c) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetY(r0c) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetZ(r0c) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetW(r0c) == Approx{ 1.0F }.margin(0.001F));
    }

    SECTION("index = 1.5")
    {
        Vector4 const r0a = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians( 0.0F),
                DegreesToRadians(30.0F),
                DegreesToRadians(45.0F),
                DegreesToRadians(60.0F)
                )),
            Replicate<Vector4>(1.5F)
        );

        CHECK(GetX(r0a) == Approx{ 0.0399999991F }.margin(0.001F));
        CHECK(GetY(r0a) == Approx{ 0.0415226296F }.margin(0.01F));
        CHECK(GetZ(r0a) == Approx{ 0.0502399169F }.margin(0.001F));
        CHECK(GetW(r0a) == Approx{ 0.0891867429F }.margin(0.001F));

        Vector4 const r0b = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians( 90.0F),
                DegreesToRadians(135.0F),
                DegreesToRadians(180.0F),
                DegreesToRadians(225.0F)
                )),
            Replicate<Vector4>(1.5F)
        );

        CHECK(GetX(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetY(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetZ(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetW(r0b) == Approx{ 1.0F }.margin(0.001F));

        Vector4 const r0c = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(-30.0F),
                DegreesToRadians(-45.0F),
                DegreesToRadians(-60.0F),
                DegreesToRadians(-90.0F)
                )),
            Replicate<Vector4>(1.5F)
        );

        CHECK(GetX(r0c) == Approx{ 0.0415226296F }.margin(0.01F));
        CHECK(GetY(r0c) == Approx{ 0.0502399169F }.margin(0.001F));
        CHECK(GetZ(r0c) == Approx{ 0.0891867429F }.margin(0.001F));
        CHECK(GetW(r0c) == Approx{ 1.0F }.margin(0.001F));
    }
}


TEST_CASE("Maths / Vector / Line - point distance")
{
    using namespace Graphyte::Maths;

    Vector3 const p0 = Make<Vector3>(-1.0F, -1.0F, -1.0F);
    Vector3 const p7 = Make<Vector3>(+1.0F, +1.0F, +1.0F);

    Vector3 const p1 = Make<Vector3>(+1.0F, -1.0F, -1.0F);
    Vector3 const p2 = Make<Vector3>(-1.0F, +1.0F, -1.0F);
    Vector3 const p3 = Make<Vector3>(+1.0F, +1.0F, -1.0F);
    Vector3 const p4 = Make<Vector3>(-1.0F, -1.0F, +1.0F);
    Vector3 const p5 = Make<Vector3>(+1.0F, -1.0F, +1.0F);
    Vector3 const p6 = Make<Vector3>(-1.0F, +1.0F, +1.0F);

    Vector4 const r0 = LinePointDistance(p0, p7, p0);
    Vector4 const r1 = LinePointDistance(p0, p7, p1);
    Vector4 const r2 = LinePointDistance(p0, p7, p2);
    Vector4 const r3 = LinePointDistance(p0, p7, p3);
    Vector4 const r4 = LinePointDistance(p0, p7, p4);
    Vector4 const r5 = LinePointDistance(p0, p7, p5);
    Vector4 const r6 = LinePointDistance(p0, p7, p6);
    Vector4 const r7 = LinePointDistance(p0, p7, p7);

    CHECK(GetX(r0) == Approx{ 0.0F });
    CHECK(GetX(r1) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r2) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r3) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r4) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r5) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r6) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r7) == Approx{ 0.0F });
}

TEST_CASE("Maths / Vector / Refraction")
{
    using namespace Graphyte::Maths;

    SECTION("Vector2")
    {
        Vector2 const n = Normalize(Make<Vector2>(1.0F, 1.0F));
        Vector2 const i = NegativeUnitY<Vector2>();

        SECTION("index = 0.5")
        {
            Vector2 const r = Refract(i, n, 0.5F);

            CHECK(GetX(r) == Approx{ -0.411437869F });
            CHECK(GetY(r) == Approx{ -0.911437869F });
        }

        SECTION("index = 1")
        {
            Vector2 const r = Refract(i, n, 1.0F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ -1.0F });
        }

        SECTION("index = 1.2")
        {
            Vector2 const r = Refract(i, n, 1.2F);

            CHECK(GetX(r) == Approx{ 0.225834280F });
            CHECK(GetY(r) == Approx{ -0.974165797F });
        }

        SECTION("index = 1.4")
        {
            Vector2 const r = Refract(i, n, 1.4F);

            CHECK(GetX(r) == Approx{ 0.599999845F });
            CHECK(GetY(r) == Approx{ -0.800000131F });
        }

        SECTION("index = 1.5")
        {
            Vector2 const r = Refract(i, n, 1.5F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
        }
    }

    SECTION("Vector3")
    {
        Vector3 const n = Normalize(Make<Vector3>(1.0F, 1.0F, 1.0F));
        Vector3 const i = NegativeUnitY<Vector3>();

        SECTION("index = 0.5")
        {
            Vector3 const r = Refract(i, n, 0.5F);

            CHECK(GetX(r) == Approx{ -0.360379606F });
            CHECK(GetY(r) == Approx{ -0.860379577F });
            CHECK(GetZ(r) == Approx{ -0.360379606F });
        }

        SECTION("index = 1")
        {
            Vector3 const r = Refract(i, n, 1.0F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ -1.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
        }

        SECTION("index = 1.2")
        {
            Vector3 const r = Refract(i, n, 1.2F);

            CHECK(GetX(r) == Approx{ 0.284530073F });
            CHECK(GetY(r) == Approx{ -0.915470004F });
            CHECK(GetZ(r) == Approx{ 0.284530073F });
        }

        SECTION("index = 1.4")
        {
            Vector3 const r = Refract(i, n, 1.4F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
        }

        SECTION("index = 1.5")
        {
            Vector3 const r = Refract(i, n, 1.5F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
        }
    }

    SECTION("Vector4")
    {
        Vector4 const n = Normalize(Make<Vector4>(1.0F, 1.0F, 1.0F, 1.0F));
        Vector4 const i = NegativeUnitY<Vector4>();

        SECTION("index = 0.5")
        {
            Vector4 const r = Refract(i, n, 0.5F);

            CHECK(GetX(r) == Approx{ -0.325693905F });
            CHECK(GetY(r) == Approx{ -0.825693905F });
            CHECK(GetZ(r) == Approx{ -0.325693905F });
            CHECK(GetW(r) == Approx{ -0.325693905F });
        }

        SECTION("index = 1")
        {
            Vector4 const r = Refract(i, n, 1.0F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ -1.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
            CHECK(GetW(r) == Approx{ 0.0F });
        }

        SECTION("index = 1.2")
        {
            Vector4 const r = Refract(i, n, 1.2F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
            CHECK(GetW(r) == Approx{ 0.0F });
        }

        SECTION("index = 1.4")
        {
            Vector4 const r = Refract(i, n, 1.4F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
            CHECK(GetW(r) == Approx{ 0.0F });
        }

        SECTION("index = 1.5")
        {
            Vector4 const r = Refract(i, n, 1.5F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
            CHECK(GetW(r) == Approx{ 0.0F });
        }
    }
}

TEST_CASE("Maths / Vector / Reflection")
{
    using namespace Graphyte::Maths;

    SECTION("-45 deg Z reflection")
    {
        Vector3 const n = Normalize(Make<Vector3>(1.0F, 1.0F, 0.0));
        Vector3 const i = NegativeUnitX<Vector3>();
        Vector3 const r = Reflect(i, n);

        CHECK(GetX(r) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetY(r) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetZ(r) == Approx{ 0.0F }.margin(0.001F));
    }

    SECTION("incident perpendicular to normal - not reflected")
    {
        Vector3 const n = Normalize(Make<Vector3>(0.0F, 1.0F, 0.0));
        Vector3 const i = UnitX<Vector3>();
        Vector3 const r = Reflect(i, n);

        CHECK(GetX(r) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetY(r) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetZ(r) == Approx{ 0.0F }.margin(0.001F));
    }

    SECTION("parallel to normal reflection")
    {
        Vector3 const n = UnitY<Vector3>();
        Vector3 const i = NegativeUnitY<Vector3>();
        Vector3 const r = Reflect(i, n);

        CHECK(GetX(r) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetY(r) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetZ(r) == Approx{ 0.0F }.margin(0.001F));
    }
}

TEST_CASE("Maths / Vector / Plane Intersection")
{
    using namespace Graphyte::Maths;

    SECTION("+X -> point")
    {
        Plane const p = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitX<Vector3>());
        Vector3 const a = Make<Vector3>(-5.0F, 1.0F, 1.0F);
        Vector3 const b = Make<Vector3>(5.0F, 1.0F, 1.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(GetX(r) == Approx{ 1.0F });
        CHECK(GetY(r) == Approx{ 1.0F });
        CHECK(GetZ(r) == Approx{ 1.0F });
    }

    SECTION("+X -> nan")
    {
        Plane const p = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitX<Vector3>());
        Vector3 const a = Make<Vector3>(1.0F, -5.0F, 1.0F);
        Vector3 const b = Make<Vector3>(1.0F, 5.0F, 1.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(std::isnan(GetX(r)));
        CHECK(std::isnan(GetY(r)));
        CHECK(std::isnan(GetZ(r)));
    }

    SECTION("+Y -> point")
    {
        Plane const p = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitY<Vector3>());
        Vector3 const a = Make<Vector3>(1.0F, -5.0F, 1.0F);
        Vector3 const b = Make<Vector3>(1.0F, 5.0F, 1.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(GetX(r) == Approx{ 1.0F });
        CHECK(GetY(r) == Approx{ 1.0F });
        CHECK(GetZ(r) == Approx{ 1.0F });
    }

    SECTION("+Y -> nan")
    {
        Plane const p = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitY<Vector3>());
        Vector3 const a = Make<Vector3>(-5.0F, 1.0F, 1.0F);
        Vector3 const b = Make<Vector3>(5.0F, 1.0F, 1.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(std::isnan(GetX(r)));
        CHECK(std::isnan(GetY(r)));
        CHECK(std::isnan(GetZ(r)));
    }

    SECTION("+Z -> point")
    {
        Plane const p = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitZ<Vector3>());
        Vector3 const a = Make<Vector3>(1.0F, 1.0F, -5.0F);
        Vector3 const b = Make<Vector3>(1.0F, 1.0F, 5.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(GetX(r) == Approx{ 1.0F });
        CHECK(GetY(r) == Approx{ 1.0F });
        CHECK(GetZ(r) == Approx{ 1.0F });
    }

    SECTION("+Z -> nan")
    {
        Plane const p = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitZ<Vector3>());
        Vector3 const a = Make<Vector3>(1.0F, -5.0F, 1.0F);
        Vector3 const b = Make<Vector3>(1.0F, 5.0F, 1.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(std::isnan(GetX(r)));
        CHECK(std::isnan(GetY(r)));
        CHECK(std::isnan(GetZ(r)));
    }
}

TEST_CASE("Maths / Vector / Clamp length")
{
    using namespace Graphyte::Maths;

    SECTION("Vector2")
    {
        for (float x = -5.0F; x <= 5.0F; x += 1.0F)
        {
            for (float y = -5.0F; y <= 5.0F; y += 1.0F)
            {
                if (IsZero(x, 0.001F) && IsZero(y, 0.001F))
                {
                    continue;
                }

                Vector2 const v = Make<Vector2>(x, y);
                Vector2 const c = ClampLength(v, 0.5F, 1.5F);

                // Normalize vector and get original length
                Vector2 const n = Normalize(v);
                Vector4 const l = Length(v);

                // Compute clamped expected length
                Vector4 const cl = Clamp(l, Replicate<Vector4>(0.5F), Replicate<Vector4>(1.5F));

                // And expected vector
                Vector2 const e = As<Vector2>(Multiply(As<Vector4>(n), cl));

                CHECK(IsEqual(c, e, Replicate<Vector2>(0.001F)));
            }
        }
    }

    SECTION("Vector3")
    {
        for (float x = -5.0F; x <= 5.0F; x += 1.0F)
        {
            for (float y = -5.0F; y <= 5.0F; y += 1.0F)
            {
                for (float z = -5.0F; z <= 5.0F; z += 1.0F)
                {
                    if (IsZero(x, 0.001F) && IsZero(y, 0.001F) && IsZero(z, 0.001F))
                    {
                        continue;
                    }

                    Vector3 const v = Make<Vector3>(x, y, z);
                    Vector3 const c = ClampLength(v, 0.5F, 1.5F);

                    // Normalize vector and get original length
                    Vector3 const n = Normalize(v);
                    Vector4 const l = Length(v);

                    // Compute clamped expected length
                    Vector4 const cl = Clamp(l, Replicate<Vector4>(0.5F), Replicate<Vector4>(1.5F));

                    // And expected vector
                    Vector3 const e = As<Vector3>(Multiply(As<Vector4>(n), cl));

                    CHECK(IsEqual(c, e, Replicate<Vector3>(0.001F)));
                }
            }
        }
    }

    SECTION("Vector4")
    {
        for (float x = -5.0F; x <= 5.0F; x += 1.0F)
        {
            for (float y = -5.0F; y <= 5.0F; y += 1.0F)
            {
                for (float z = -5.0F; z <= 5.0F; z += 1.0F)
                {
                    for (float w = -5.0F; w <= 5.0F; w += 1.0F)
                    {
                        if (IsZero(x, 0.001F) && IsZero(y, 0.001F) && IsZero(z, 0.001F) && IsZero(w, 0.001F))
                        {
                            continue;
                        }

                        Vector4 const v = Make<Vector4>(x, y, z, w);
                        Vector4 const c = ClampLength(v, 0.5F, 1.5F);

                        // Normalize vector and get original length
                        Vector4 const n = Normalize(v);
                        Vector4 const l = Length(v);

                        // Compute clamped expected length
                        Vector4 const cl = Clamp(l, Replicate<Vector4>(0.5F), Replicate<Vector4>(1.5F));

                        // And expected vector
                        Vector4 const e = As<Vector4>(Multiply(As<Vector4>(n), cl));

                        CHECK(IsEqual(c, e, Replicate<Vector4>(0.001F)));
                    }
                }
            }
        }
    }
}

TEST_CASE("Maths / Quaternion / Rotate vector by quaternion")
{
    using namespace Graphyte::Maths;

    SECTION("Unit X")
    {
        Vector3 const x0 = UnitX<Vector3>();

        SECTION("Around X")
        {
            Quaternion const q = CreateFromAxisAngle(UnitX<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1 = Rotate(x0, q);

            CHECK(GetX(x0) == Approx{ GetX(x1) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x1) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x1) }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x0) == Approx{ GetX(x2) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x2) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x2) }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x0) == Approx{ GetX(x3) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x3) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x3) }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x0) == Approx{ GetX(x4) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x4) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x4) }.margin(0.001F));
        }

        SECTION("Around Y")
        {
            Quaternion const q = CreateFromAxisAngle(UnitY<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1 = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ -1.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ 1.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 0.0F }.margin(0.001F));
        }

        SECTION("Around Z")
        {
            Quaternion const q = CreateFromAxisAngle(UnitZ<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1 = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 0.0F }.margin(0.001F));
        }
    }

    SECTION("Unit Y")
    {
        Vector3 const x0 = UnitY<Vector3>();

        SECTION("Around X")
        {
            Quaternion const q = CreateFromAxisAngle(UnitX<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1 = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ 1.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ -1.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 0.0F }.margin(0.001F));
        }

        SECTION("Around Y")
        {
            Quaternion const q = CreateFromAxisAngle(UnitY<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1 = Rotate(x0, q);

            CHECK(GetX(x0) == Approx{ GetX(x1) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x1) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x1) }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x0) == Approx{ GetX(x2) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x2) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x2) }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x0) == Approx{ GetX(x3) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x3) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x3) }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x0) == Approx{ GetX(x4) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x4) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x4) }.margin(0.001F));
        }

        SECTION("Around Z")
        {
            Quaternion const q = CreateFromAxisAngle(UnitZ<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1 = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 0.0F }.margin(0.001F));
        }
    }

    SECTION("Unit Z")
    {
        Vector3 const x0 = UnitZ<Vector3>();

        SECTION("Around X")
        {
            Quaternion const q = CreateFromAxisAngle(UnitX<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1 = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ -1.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 1.0F }.margin(0.001F));
        }

        SECTION("Around Y")
        {
            Quaternion const q = CreateFromAxisAngle(UnitY<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1 = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ -1.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 1.0F }.margin(0.001F));
        }

        SECTION("Around Z")
        {
            Quaternion const q = CreateFromAxisAngle(UnitZ<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1 = Rotate(x0, q);

            CHECK(GetX(x0) == Approx{ GetX(x1) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x1) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x1) }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x0) == Approx{ GetX(x2) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x2) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x2) }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x0) == Approx{ GetX(x3) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x3) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x3) }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x0) == Approx{ GetX(x4) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x4) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x4) }.margin(0.001F));
        }
    }
}

TEST_CASE("Maths / Quaternion / Rotation from axis angle")
{
    using namespace Graphyte::Maths;

    SECTION("Axis X")
    {
        Quaternion const q000 = CreateFromAxisAngle(UnitX<Vector3>(), DegreesToRadians(0.0F));
        Quaternion const q090 = CreateFromAxisAngle(UnitX<Vector3>(), DegreesToRadians(90.0F));
        Quaternion const q180 = CreateFromAxisAngle(UnitX<Vector3>(), DegreesToRadians(180.0F));
        Quaternion const q270 = CreateFromAxisAngle(UnitX<Vector3>(), DegreesToRadians(270.0F));

        CHECK(GetX(q000) == Approx{ 0.0F });
        CHECK(GetY(q000) == Approx{ 0.0F });
        CHECK(GetZ(q000) == Approx{ 0.0F });
        CHECK(GetW(q000) == Approx{ 1.0F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q000);

            CHECK(GetX(axis) == 0.0F);
            CHECK(GetY(axis) == 0.0F);
            CHECK(GetZ(axis) == 0.0F);
            CHECK(angle == 0.0F);
        }

        CHECK(GetX(q090) == Approx{ 0.70711F });
        CHECK(GetY(q090) == Approx{ 0.0F });
        CHECK(GetZ(q090) == Approx{ 0.0F });
        CHECK(GetW(q090) == Approx{ 0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q090);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == Approx{ 1.0F });
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(90.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q180) == Approx{ 1.0F });
        CHECK(GetY(q180) == Approx{ 0.0F });
        CHECK(GetZ(q180) == Approx{ 0.0F });
        CHECK(GetW(q180) == Approx{ 0.0F }.margin(0.001F));

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q180);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 1.0F);
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(180.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q270) == Approx{ 0.70711F });
        CHECK(GetY(q270) == Approx{ 0.0F });
        CHECK(GetZ(q270) == Approx{ 0.0F });
        CHECK(GetW(q270) == Approx{ -0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q270);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == Approx{ 1.0F });
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(270.0F) }.margin(0.0001F));
        }
    }

    SECTION("Axis Y")
    {
        Quaternion const q000 = CreateFromAxisAngle(UnitY<Vector3>(), DegreesToRadians(0.0F));
        Quaternion const q090 = CreateFromAxisAngle(UnitY<Vector3>(), DegreesToRadians(90.0F));
        Quaternion const q180 = CreateFromAxisAngle(UnitY<Vector3>(), DegreesToRadians(180.0F));
        Quaternion const q270 = CreateFromAxisAngle(UnitY<Vector3>(), DegreesToRadians(270.0F));

        CHECK(GetX(q000) == Approx{ 0.0F });
        CHECK(GetY(q000) == Approx{ 0.0F });
        CHECK(GetZ(q000) == Approx{ 0.0F });
        CHECK(GetW(q000) == Approx{ 1.0F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q000);

            CHECK(GetX(axis) == 0.0F);
            CHECK(GetY(axis) == 0.0F);
            CHECK(GetZ(axis) == 0.0F);
            CHECK(angle == 0.0F);
        }

        CHECK(GetX(q090) == Approx{ 0.0F });
        CHECK(GetY(q090) == Approx{ 0.70711F });
        CHECK(GetZ(q090) == Approx{ 0.0F });
        CHECK(GetW(q090) == Approx{ 0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q090);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == Approx{ 1.0F });
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(90.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q180) == Approx{ 0.0F });
        CHECK(GetY(q180) == Approx{ 1.0F });
        CHECK(GetZ(q180) == Approx{ 0.0F });
        CHECK(GetW(q180) == Approx{ 0.0F }.margin(0.001F));

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q180);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == 1.0F);
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(180.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q270) == Approx{ 0.0F });
        CHECK(GetY(q270) == Approx{ 0.70711F });
        CHECK(GetZ(q270) == Approx{ 0.0F });
        CHECK(GetW(q270) == Approx{ -0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q270);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == Approx{ 1.0F });
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(270.0F) }.margin(0.0001F));
        }
    }

    SECTION("Axis Z")
    {
        Quaternion const q000 = CreateFromAxisAngle(UnitZ<Vector3>(), DegreesToRadians(0.0F));
        Quaternion const q090 = CreateFromAxisAngle(UnitZ<Vector3>(), DegreesToRadians(90.0F));
        Quaternion const q180 = CreateFromAxisAngle(UnitZ<Vector3>(), DegreesToRadians(180.0F));
        Quaternion const q270 = CreateFromAxisAngle(UnitZ<Vector3>(), DegreesToRadians(270.0F));

        CHECK(GetX(q000) == Approx{ 0.0F });
        CHECK(GetY(q000) == Approx{ 0.0F });
        CHECK(GetZ(q000) == Approx{ 0.0F });
        CHECK(GetW(q000) == Approx{ 1.0F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q000);

            CHECK(GetX(axis) == 0.0F);
            CHECK(GetY(axis) == 0.0F);
            CHECK(GetZ(axis) == 0.0F);
            CHECK(angle == 0.0F);
        }

        CHECK(GetX(q090) == Approx{ 0.0F });
        CHECK(GetY(q090) == Approx{ 0.0F });
        CHECK(GetZ(q090) == Approx{ 0.70711F });
        CHECK(GetW(q090) == Approx{ 0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q090);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == Approx{ 1.0F });
            CHECK(angle == Approx{ DegreesToRadians(90.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q180) == Approx{ 0.0F });
        CHECK(GetY(q180) == Approx{ 0.0F });
        CHECK(GetZ(q180) == Approx{ 1.0F });
        CHECK(GetW(q180) == Approx{ 0.0F }.margin(0.001F));

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q180);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == 1.0F);
            CHECK(angle == Approx{ DegreesToRadians(180.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q270) == Approx{ 0.0F });
        CHECK(GetY(q270) == Approx{ 0.0F });
        CHECK(GetZ(q270) == Approx{ 0.70711F });
        CHECK(GetW(q270) == Approx{ -0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q270);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == Approx{ 1.0F });
            CHECK(angle == Approx{ DegreesToRadians(270.0F) }.margin(0.0001F));
        }
    }
}


TEST_CASE("Maths / Quaternion / Multiply")
{
    using namespace Graphyte::Maths;

    Quaternion const qx = UnitX<Quaternion>();
    Quaternion const qy = UnitY<Quaternion>();
    Quaternion const qz = UnitZ<Quaternion>();
    Quaternion const qw = UnitW<Quaternion>();

    SECTION("x*x")
    {
        Quaternion const qq = Multiply(qx, qx);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == -1.0F);
    }

    SECTION("x*y")
    {
        Quaternion const qq = Multiply(qx, qy);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 1.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("x*z")
    {
        Quaternion const qq = Multiply(qx, qz);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == -1.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("x*w")
    {
        Quaternion const qq = Multiply(qx, qw);
        CHECK(GetX(qq) == 1.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("y*x")
    {
        Quaternion const qq = Multiply(qy, qx);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == -1.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("y*y")
    {
        Quaternion const qq = Multiply(qy, qy);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == -1.0F);
    }

    SECTION("y*z")
    {
        Quaternion const qq = Multiply(qy, qz);
        CHECK(GetX(qq) == 1.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("y*w")
    {
        Quaternion const qq = Multiply(qy, qw);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 1.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("z*x")
    {
        Quaternion const qq = Multiply(qz, qx);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 1.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("z*y")
    {
        Quaternion const qq = Multiply(qz, qy);
        CHECK(GetX(qq) == -1.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("z*z")
    {
        Quaternion const qq = Multiply(qz, qz);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == -1.0F);
    }

    SECTION("z*w")
    {
        Quaternion const qq = Multiply(qz, qw);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 1.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("w*x")
    {
        Quaternion const qq = Multiply(qw, qx);
        CHECK(GetX(qq) == 1.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("w*y")
    {
        Quaternion const qq = Multiply(qw, qy);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 1.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("w*z")
    {
        Quaternion const qq = Multiply(qw, qz);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 1.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("w*w")
    {
        Quaternion const qq = Multiply(qw, qw);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 1.0F);
    }
}

TEST_CASE("Maths / Plane / Normalized")
{
    using namespace Graphyte::Maths;

    Plane const p = CreateFromPoints(
        Add(UnitX<Vector3>(), UnitY<Vector3>()),
        Add(Zero<Vector3>(), UnitY<Vector3>()),
        Add(UnitZ<Vector3>(), UnitY<Vector3>())
    );

    CHECK(GetX(p) == Approx{ 0.0F });
    CHECK(GetY(p) == Approx{ 1.0F });
    CHECK(GetZ(p) == Approx{ 0.0F });
    CHECK(GetW(p) == Approx{ -1.0F });
}

TEST_CASE("Maths / Vector / Horizontal operations")
{
    using namespace Graphyte::Maths;


    SECTION("Vector4")
    {
        Vector4 const v0 = Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F);
        Vector4 const v1 = Make<Vector4>(4.0F, 1.0F, 2.0F, 3.0F);
        Vector4 const v2 = Make<Vector4>(3.0F, 4.0F, 1.0F, 2.0F);
        Vector4 const v3 = Make<Vector4>(2.0F, 3.0F, 4.0F, 1.0F);

        SECTION("Horizontal min")
        {
            Vector4 const h0 = Hmin(v0);
            Vector4 const h1 = Hmin(v1);
            Vector4 const h2 = Hmin(v2);
            Vector4 const h3 = Hmin(v3);

            CHECK(GetX(h0) == 1.0F);
            CHECK(GetY(h0) == 1.0F);
            CHECK(GetZ(h0) == 1.0F);
            CHECK(GetW(h0) == 1.0F);

            CHECK(GetX(h1) == 1.0F);
            CHECK(GetY(h1) == 1.0F);
            CHECK(GetZ(h1) == 1.0F);
            CHECK(GetW(h1) == 1.0F);

            CHECK(GetX(h2) == 1.0F);
            CHECK(GetY(h2) == 1.0F);
            CHECK(GetZ(h2) == 1.0F);
            CHECK(GetW(h2) == 1.0F);

            CHECK(GetX(h3) == 1.0F);
            CHECK(GetY(h3) == 1.0F);
            CHECK(GetZ(h3) == 1.0F);
            CHECK(GetW(h3) == 1.0F);
        }

        SECTION("Horizontal max")
        {
            Vector4 const h0 = Hmax(v0);
            Vector4 const h1 = Hmax(v1);
            Vector4 const h2 = Hmax(v2);
            Vector4 const h3 = Hmax(v3);

            CHECK(GetX(h0) == 4.0F);
            CHECK(GetY(h0) == 4.0F);
            CHECK(GetZ(h0) == 4.0F);
            CHECK(GetW(h0) == 4.0F);

            CHECK(GetX(h1) == 4.0F);
            CHECK(GetY(h1) == 4.0F);
            CHECK(GetZ(h1) == 4.0F);
            CHECK(GetW(h1) == 4.0F);

            CHECK(GetX(h2) == 4.0F);
            CHECK(GetY(h2) == 4.0F);
            CHECK(GetZ(h2) == 4.0F);
            CHECK(GetW(h2) == 4.0F);

            CHECK(GetX(h3) == 4.0F);
            CHECK(GetY(h3) == 4.0F);
            CHECK(GetZ(h3) == 4.0F);
            CHECK(GetW(h3) == 4.0F);
        }

        SECTION("Horizontal sum")
        {
            Vector4 const h0 = Hsum(v0);
            Vector4 const h1 = Hsum(v1);
            Vector4 const h2 = Hsum(v2);
            Vector4 const h3 = Hsum(v3);

            CHECK(GetX(h0) == 10.0F);
            CHECK(GetY(h0) == 10.0F);
            CHECK(GetZ(h0) == 10.0F);
            CHECK(GetW(h0) == 10.0F);

            CHECK(GetX(h1) == 10.0F);
            CHECK(GetY(h1) == 10.0F);
            CHECK(GetZ(h1) == 10.0F);
            CHECK(GetW(h1) == 10.0F);

            CHECK(GetX(h2) == 10.0F);
            CHECK(GetY(h2) == 10.0F);
            CHECK(GetZ(h2) == 10.0F);
            CHECK(GetW(h2) == 10.0F);

            CHECK(GetX(h3) == 10.0F);
            CHECK(GetY(h3) == 10.0F);
            CHECK(GetZ(h3) == 10.0F);
            CHECK(GetW(h3) == 10.0F);
        }
    }


    SECTION("Horizontal Min / Vector3")
    {
        Vector3 const v0 = Make<Vector3>(1.0F, 2.0F, 3.0F);
        Vector3 const v1 = Make<Vector3>(4.0F, 3.0F, 2.0F);
        Vector3 const v2 = Make<Vector3>(5.0F, 3.0F, 4.0F);

        SECTION("Horizontal min")
        {
            Vector4 const h0 = Hmin(v0);
            Vector4 const h1 = Hmin(v1);
            Vector4 const h2 = Hmin(v2);

            CHECK(GetX(h0) == 1.0F);
            CHECK(GetY(h0) == 1.0F);
            CHECK(GetZ(h0) == 1.0F);
            CHECK(GetW(h0) == 1.0F);

            CHECK(GetX(h1) == 2.0F);
            CHECK(GetY(h1) == 2.0F);
            CHECK(GetZ(h1) == 2.0F);
            CHECK(GetW(h1) == 2.0F);

            CHECK(GetX(h2) == 3.0F);
            CHECK(GetY(h2) == 3.0F);
            CHECK(GetZ(h2) == 3.0F);
            CHECK(GetW(h2) == 3.0F);
        }

        SECTION("Horizontal max")
        {
            Vector4 const h0 = Hmax(v0);
            Vector4 const h1 = Hmax(v1);
            Vector4 const h2 = Hmax(v2);

            CHECK(GetX(h0) == 3.0F);
            CHECK(GetY(h0) == 3.0F);
            CHECK(GetZ(h0) == 3.0F);
            CHECK(GetW(h0) == 3.0F);

            CHECK(GetX(h1) == 4.0F);
            CHECK(GetY(h1) == 4.0F);
            CHECK(GetZ(h1) == 4.0F);
            CHECK(GetW(h1) == 4.0F);

            CHECK(GetX(h2) == 5.0F);
            CHECK(GetY(h2) == 5.0F);
            CHECK(GetZ(h2) == 5.0F);
            CHECK(GetW(h2) == 5.0F);
        }

        SECTION("Horizontal sum")
        {
            Vector4 const h0 = Hsum(v0);
            Vector4 const h1 = Hsum(v1);
            Vector4 const h2 = Hsum(v2);

            CHECK(GetX(h0) == 6.0F);
            CHECK(GetY(h0) == 6.0F);
            CHECK(GetZ(h0) == 6.0F);
            CHECK(GetW(h0) == 6.0F);

            CHECK(GetX(h1) == 9.0F);
            CHECK(GetY(h1) == 9.0F);
            CHECK(GetZ(h1) == 9.0F);
            CHECK(GetW(h1) == 9.0F);

            CHECK(GetX(h2) == 12.0F);
            CHECK(GetY(h2) == 12.0F);
            CHECK(GetZ(h2) == 12.0F);
            CHECK(GetW(h2) == 12.0F);
        }
    }


    SECTION("Horizontal Min / Vector2")
    {
        Vector2 const v0 = Make<Vector2>(1.0F, 2.0F);
        Vector2 const v1 = Make<Vector2>(4.0F, 3.0F);

        SECTION("Horizontal min")
        {
            Vector4 const h0 = Hmin(v0);
            Vector4 const h1 = Hmin(v1);

            CHECK(GetX(h0) == 1.0F);
            CHECK(GetY(h0) == 1.0F);
            CHECK(GetZ(h0) == 1.0F);
            CHECK(GetW(h0) == 1.0F);

            CHECK(GetX(h1) == 3.0F);
            CHECK(GetY(h1) == 3.0F);
            CHECK(GetZ(h1) == 3.0F);
            CHECK(GetW(h1) == 3.0F);
        }

        SECTION("Horizontal max")
        {
            Vector4 const h0 = Hmax(v0);
            Vector4 const h1 = Hmax(v1);

            CHECK(GetX(h0) == 2.0F);
            CHECK(GetY(h0) == 2.0F);
            CHECK(GetZ(h0) == 2.0F);
            CHECK(GetW(h0) == 2.0F);

            CHECK(GetX(h1) == 4.0F);
            CHECK(GetY(h1) == 4.0F);
            CHECK(GetZ(h1) == 4.0F);
            CHECK(GetW(h1) == 4.0F);
        }

        SECTION("Horizontal sum")
        {
            Vector4 const h0 = Hsum(v0);
            Vector4 const h1 = Hsum(v1);

            CHECK(GetX(h0) == 3.0F);
            CHECK(GetY(h0) == 3.0F);
            CHECK(GetZ(h0) == 3.0F);
            CHECK(GetW(h0) == 3.0F);

            CHECK(GetX(h1) == 7.0F);
            CHECK(GetY(h1) == 7.0F);
            CHECK(GetZ(h1) == 7.0F);
            CHECK(GetW(h1) == 7.0F);
        }
    }
}


TEST_CASE("Maths / Quaternion / exp log identity")
{
    using namespace Graphyte::Maths;

    SECTION("Identity quaternion exp+log")
    {
        Quaternion const qi = Make<Quaternion>(1.2F, -2.6F, 3.1F, 6.0F);
        Quaternion const ql = Log(qi);
        Quaternion const qe = Exp(ql);

        CHECK(GetX(ql) == Approx{ 0.174299479F }.margin(0.0005F));
        CHECK(GetY(ql) == Approx{ -0.377526760F }.margin(0.0005F));
        CHECK(GetZ(ql) == Approx{ 0.450128078F }.margin(0.0005F));
        CHECK(GetW(ql) == Approx{ 1.99272966F }.margin(0.0005F));

        CHECK(GetX(qi) == Approx{ GetX(qe) }.margin(0.001F));
        CHECK(GetY(qi) == Approx{ GetY(qe) }.margin(0.001F));
        CHECK(GetZ(qi) == Approx{ GetZ(qe) }.margin(0.001F));
        CHECK(GetW(qi) == Approx{ GetW(qe) }.margin(0.001F));
    }
}

TEST_CASE("Maths / Vector / Interpolation")
{
    using namespace Graphyte::Maths;
    constexpr float const DeltaT = 0.1F;


    SECTION("Catmull Rom")
    {
        Vector4 const a = Make<Vector4>(-1.0F, +2.0F, +3.0F, -4.0F);
        Vector4 const b = Make<Vector4>(+4.0F, -3.0F, +7.0F, -11.0F);
        Vector4 const c = Make<Vector4>(+1.0F, -1.0F, -3.0F, +5.0F);
        Vector4 const d = Make<Vector4>(+3.0F, +1.0F, -4.0F, -10.0F);

        SECTION("Linear")
        {
            for (float t = 0.0F; t <= 1.0F; t += DeltaT)
            {
                Vector4 const v = CatmullRom(a, b, c, d, t);

                CHECK(GetX(v) == Approx{ CatmullRom(GetX(a), GetX(b), GetX(c), GetX(d), t) });
                CHECK(GetY(v) == Approx{ CatmullRom(GetY(a), GetY(b), GetY(c), GetY(d), t) });
                CHECK(GetZ(v) == Approx{ CatmullRom(GetZ(a), GetZ(b), GetZ(c), GetZ(d), t) });
                CHECK(GetW(v) == Approx{ CatmullRom(GetW(a), GetW(b), GetW(c), GetW(d), t) });
            }
        }

        SECTION("Vectorized")
        {
            for (float x = 0.0F; x <= 1.0F; x += DeltaT)
            {
                for (float y = 0.0F; y <= 1.0F; y += DeltaT)
                {
                    for (float z = 0.0F; z <= 1.0F; z += DeltaT)
                    {
                        for (float w = 0.0F; w <= 1.0F; w += DeltaT)
                        {
                            Vector4 const t = Make<Vector4>(x, y, z, w);
                            Vector4 const v = CatmullRom(a, b, c, d, t);

                            CHECK(GetX(v) == Approx{ CatmullRom(GetX(a), GetX(b), GetX(c), GetX(d), x) });
                            CHECK(GetY(v) == Approx{ CatmullRom(GetY(a), GetY(b), GetY(c), GetY(d), y) });
                            CHECK(GetZ(v) == Approx{ CatmullRom(GetZ(a), GetZ(b), GetZ(c), GetZ(d), z) });
                            CHECK(GetW(v) == Approx{ CatmullRom(GetW(a), GetW(b), GetW(c), GetW(d), w) });
                        }
                    }
                }
            }
        }
    }

    SECTION("Barycentric")
    {
        Vector4 const a = Make<Vector4>(-1.0F, +2.0F, +3.0F, -4.0F);
        Vector4 const b = Make<Vector4>(+4.0F, -3.0F, +7.0F, -11.0F);
        Vector4 const c = Make<Vector4>(+1.0F, -1.0F, -3.0F, 5.0F);

        SECTION("Linear")
        {
            for (float f = 0.0F; f < 1.0F; f += DeltaT)
            {
                for (float g = 0.0F; g < 1.0F; g += DeltaT)
                {
                    Vector4 v = Barycentric(a, b, c, f, g);

                    CHECK(GetX(v) == Approx{ Barycentric(GetX(a), GetX(b), GetX(c), f, g) }.margin(0.0001F));
                    CHECK(GetY(v) == Approx{ Barycentric(GetY(a), GetY(b), GetY(c), f, g) }.margin(0.0001F));
                    CHECK(GetZ(v) == Approx{ Barycentric(GetZ(a), GetZ(b), GetZ(c), f, g) }.margin(0.0001F));
                    CHECK(GetW(v) == Approx{ Barycentric(GetW(a), GetW(b), GetW(c), f, g) }.margin(0.0001F));
                }
            }
        }

        SECTION("Vectorized")
        {
            for (float f = 0.0F; f < 1.0F; f += DeltaT)
            {
                for (float g = 0.0F; g < 1.0F; g += DeltaT)
                {
                    Vector4 tf = Make<Vector4>(f, f * 0.5F, 1.0F - f, 1.0F - (f * 0.5F));
                    Vector4 tg = Make<Vector4>(g, g * 0.5F, 1.0F - g, 1.0F - (g * 0.5F));

                    Vector4 v = Barycentric(a, b, c, tf, tg);

                    CHECK(GetX(v) == Approx{ Barycentric(GetX(a), GetX(b), GetX(c), GetX(tf), GetX(tg)) }.margin(0.0001F));
                    CHECK(GetY(v) == Approx{ Barycentric(GetY(a), GetY(b), GetY(c), GetY(tf), GetY(tg)) }.margin(0.0001F));
                    CHECK(GetZ(v) == Approx{ Barycentric(GetZ(a), GetZ(b), GetZ(c), GetZ(tf), GetZ(tg)) }.margin(0.0001F));
                    CHECK(GetW(v) == Approx{ Barycentric(GetW(a), GetW(b), GetW(c), GetW(tf), GetW(tg)) }.margin(0.0001F));
                }
            }
        }
    }

    SECTION("Hermite")
    {
        Vector4 const a = Make<Vector4>(-2.0F, +2.0F, -1.0F, +1.0F);
        Vector4 const b = Make<Vector4>(+1.0F, +1.0F, -1.0F, +1.0F);
        Vector4 const c = Make<Vector4>(+2.0F, -2.0F, -2.0F, +1.0F);
        Vector4 const d = Make<Vector4>(-1.0F, +1.0F, -1.0F, -1.0F);

        SECTION("Linear")
        {
            for (float t = 0.0F; t <= 1.0F; t += DeltaT)
            {
                Vector4 const v = Hermite(a, b, c, d, t);

                CHECK(GetX(v) == Approx{ Hermite(GetX(a), GetX(b), GetX(c), GetX(d), t) });
                CHECK(GetY(v) == Approx{ Hermite(GetY(a), GetY(b), GetY(c), GetY(d), t) });
                CHECK(GetZ(v) == Approx{ Hermite(GetZ(a), GetZ(b), GetZ(c), GetZ(d), t) });
                CHECK(GetW(v) == Approx{ Hermite(GetW(a), GetW(b), GetW(c), GetW(d), t) });
            }
        }

        SECTION("Vectorized")
        {
            for (float x = 0.0F; x <= 1.0F; x += DeltaT)
            {
                Vector4 const t = Replicate<Vector4>(x);
                Vector4 const v = Hermite(a, b, c, d, t);

                CHECK(GetX(v) == Approx{ Hermite(GetX(a), GetX(b), GetX(c), GetX(d), x) });
                CHECK(GetY(v) == Approx{ Hermite(GetY(a), GetY(b), GetY(c), GetY(d), x) });
                CHECK(GetZ(v) == Approx{ Hermite(GetZ(a), GetZ(b), GetZ(c), GetZ(d), x) });
                CHECK(GetW(v) == Approx{ Hermite(GetW(a), GetW(b), GetW(c), GetW(d), x) });
            }
        }
    }

    SECTION("Lerp")
    {
        Vector4 const a = Make<Vector4>(-1.0F, 2.0F, 3.0F, -4.0F);
        Vector4 const b = Make<Vector4>(3.0F, 1.0F, -4.0F, -10.0F);

        SECTION("Linear")
        {
            for (float t = 0.0F; t <= 1.0F; t += DeltaT)
            {
                Vector4 const v = Lerp(a, b, t);

                CHECK(GetX(v) == Approx{ Lerp(GetX(a), GetX(b), t) });
                CHECK(GetY(v) == Approx{ Lerp(GetY(a), GetY(b), t) });
                CHECK(GetZ(v) == Approx{ Lerp(GetZ(a), GetZ(b), t) });
                CHECK(GetW(v) == Approx{ Lerp(GetW(a), GetW(b), t) });
            }
        }

        SECTION("Vectorized")
        {
            for (float x = 0.0F; x <= 1.0F; x += DeltaT)
            {
                for (float y = 0.0F; y <= 1.0F; y += DeltaT)
                {
                    for (float z = 0.0F; z <= 1.0F; z += DeltaT)
                    {
                        for (float w = 0.0F; w <= 1.0F; w += DeltaT)
                        {
                            Vector4 const t = Make<Vector4>(x, y, z, w);
                            Vector4 const v = Lerp(a, b, t);

                            CHECK(GetX(v) == Approx{ Lerp(GetX(a), GetX(b), x) });
                            CHECK(GetY(v) == Approx{ Lerp(GetY(a), GetY(b), y) });
                            CHECK(GetZ(v) == Approx{ Lerp(GetZ(a), GetZ(b), z) });
                            CHECK(GetW(v) == Approx{ Lerp(GetW(a), GetW(b), w) });
                        }
                    }
                }
            }
        }
    }
}

TEST_CASE("Maths / Vector / Permute")
{
    using namespace Graphyte::Maths;

    Vector4 const a = Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F);
    Vector4 const b = Make<Vector4>(5.0F, 6.0F, 7.0F, 8.0F);

    for (uint32_t x = 0; x < 8; ++x)
    {
        for (uint32_t y = 0; y < 8; ++y)
        {
            for (uint32_t z = 0; z < 8; ++z)
            {
                for (uint32_t w = 0; w < 8; ++w)
                {
                    Vector4 const expected = Make<Vector4>(
                        static_cast<float>(x + 1),
                        static_cast<float>(y + 1),
                        static_cast<float>(z + 1),
                        static_cast<float>(w + 1)
                    );

                    Vector4 const permuted = Permute(a, b, x, y, z, w);

                    CHECK(GetX(expected) == GetX(permuted));
                    CHECK(GetY(expected) == GetY(permuted));
                    CHECK(GetZ(expected) == GetZ(permuted));
                    CHECK(GetW(expected) == GetW(permuted));
                }
            }
        }
    }
}

TEST_CASE("Maths / Vector / Swizzle")
{
    using namespace Graphyte::Maths;

    Vector4 const a = Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F);

    for (uint32_t x = 0; x < 4; ++x)
    {
        for (uint32_t y = 0; y < 4; ++y)
        {
            for (uint32_t z = 0; z < 4; ++z)
            {
                for (uint32_t w = 0; w < 4; ++w)
                {
                    Vector4 const expected = Make<Vector4>(
                        static_cast<float>(x + 1),
                        static_cast<float>(y + 1),
                        static_cast<float>(z + 1),
                        static_cast<float>(w + 1)
                    );

                    Vector4 const swizzled = Swizzle(a, x, y, z, w);

                    CHECK(GetX(expected) == GetX(swizzled));
                    CHECK(GetY(expected) == GetY(swizzled));
                    CHECK(GetZ(expected) == GetZ(swizzled));
                    CHECK(GetW(expected) == GetW(swizzled));
                }
            }
        }
    }
}

TEST_CASE("Maths / Vector / Compiled swizzles")
{
    using namespace Graphyte::Maths;

    Vector4 const a = Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F);

    SECTION("Generic case")
    {
        CHECK(IsEqual(Swizzle<3, 2, 1, 0>(a), Make<Vector4>(4.0F, 3.0F, 2.0F, 1.0F)));
        CHECK(IsEqual(Swizzle<0, 1, 2, 3>(a), Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F)));
    }

    SECTION("AVX specializations")
    {
        CHECK(IsEqual(Swizzle<0, 1, 0, 1>(a), Make<Vector4>(1.0F, 2.0F, 1.0F, 2.0F)));
        CHECK(IsEqual(Swizzle<2, 3, 2, 3>(a), Make<Vector4>(3.0F, 4.0F, 3.0F, 4.0F)));
        CHECK(IsEqual(Swizzle<0, 0, 1, 1>(a), Make<Vector4>(1.0F, 1.0F, 2.0F, 2.0F)));
        CHECK(IsEqual(Swizzle<2, 2, 3, 3>(a), Make<Vector4>(3.0F, 3.0F, 4.0F, 4.0F)));
        CHECK(IsEqual(Swizzle<0, 0, 2, 2>(a), Make<Vector4>(1.0F, 1.0F, 3.0F, 3.0F)));
        CHECK(IsEqual(Swizzle<1, 1, 3, 3>(a), Make<Vector4>(2.0F, 2.0F, 4.0F, 4.0F)));
    }

    SECTION("AVX2 specializations")
    {
        CHECK(IsEqual(Swizzle<0, 0, 0, 0>(a), Make<Vector4>(1.0F, 1.0F, 1.0F, 1.0F)));
    }

}


TEST_CASE("Maths / Vector / Orthogonal")
{
    using namespace Graphyte::Maths;

    SECTION("Vector2")
    {
        Vector2 const o0 = Make<Vector2>(1.0F, 2.0F);
        CHECK(GetX(o0) == 1.0F);
        CHECK(GetY(o0) == 2.0F);

        Vector2 const o1 = Orthogonal(o0);
        CHECK(GetX(o1) == -2.0F);
        CHECK(GetY(o1) == 1.0F);

        Vector2 const o2 = Orthogonal(o1);
        CHECK(GetX(o2) == -1.0F);
        CHECK(GetY(o2) == -2.0F);

        Vector2 const o3 = Orthogonal(o2);
        CHECK(GetX(o3) == 2.0F);
        CHECK(GetY(o3) == -1.0F);

        Vector2 const o4 = Orthogonal(o3);
        CHECK(GetX(o4) == 1.0F);
        CHECK(GetY(o4) == 2.0F);
    }

    SECTION("Vector4")
    {
        Vector4 const o0 = Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F);
        CHECK(GetX(o0) == 1.0F);
        CHECK(GetY(o0) == 2.0F);
        CHECK(GetZ(o0) == 3.0F);
        CHECK(GetW(o0) == 4.0F);

        Vector4 const o1 = Orthogonal(o0);
        CHECK(GetX(o1) == 3.0F);
        CHECK(GetY(o1) == 4.0F);
        CHECK(GetZ(o1) == -1.0F);
        CHECK(GetW(o1) == -2.0F);

        Vector4 const o2 = Orthogonal(o1);
        CHECK(GetX(o2) == -1.0F);
        CHECK(GetY(o2) == -2.0F);
        CHECK(GetZ(o2) == -3.0F);
        CHECK(GetW(o2) == -4.0F);

        Vector4 const o3 = Orthogonal(o2);
        CHECK(GetX(o3) == -3.0F);
        CHECK(GetY(o3) == -4.0F);
        CHECK(GetZ(o3) == 1.0F);
        CHECK(GetW(o3) == 2.0F);

        Vector4 const o4 = Orthogonal(o3);
        CHECK(GetX(o4) == 1.0F);
        CHECK(GetY(o4) == 2.0F);
        CHECK(GetZ(o4) == 3.0F);
        CHECK(GetW(o4) == 4.0F);
    }
}


TEST_CASE("Maths / Matrix / Transpose")
{
    using namespace Graphyte::Maths;

    Float4x4A const values{ { {
        0.0F, 1.0F, 2.0F, 3.0F,
        4.0F, 5.0F, 6.0F, 7.0F,
        8.0F, 9.0F, 10.0F, 11.0F,
        12.0F, 13.0F, 14.0F, 15.0F,
    } } };

    Matrix const original = Load<Matrix>(&values);
    Matrix const transposed = Transpose(original);

    Float4x4A stored{};
    Store<Matrix>(&stored, transposed);

    CHECK(stored.M11 == 0.0F);
    CHECK(stored.M12 == 4.0F);
    CHECK(stored.M13 == 8.0F);
    CHECK(stored.M14 == 12.0F);

    CHECK(stored.M21 == 1.0F);
    CHECK(stored.M22 == 5.0F);
    CHECK(stored.M23 == 9.0F);
    CHECK(stored.M24 == 13.0F);

    CHECK(stored.M31 == 2.0F);
    CHECK(stored.M32 == 6.0F);
    CHECK(stored.M33 == 10.0F);
    CHECK(stored.M34 == 14.0F);

    CHECK(stored.M41 == 3.0F);
    CHECK(stored.M42 == 7.0F);
    CHECK(stored.M43 == 11.0F);
    CHECK(stored.M44 == 15.0F);
}

TEST_CASE("Maths / Matrix / Load-Store")
{
    using namespace Graphyte::Maths;

    Float4x4A const mm{ { {
        1.0F, 2.0F, 3.0F, 4.0F,
        1.5F, 2.5F, 3.5F, 4.5F,
        2.1F, 3.1F, 4.1F, 5.1F,
        3.2F, 4.3F, 5.4F, 6.5F,
    } } };

    Matrix const m = Load<Matrix>(&mm);

    Vector4 r0 = GetBaseX(m);
    Vector4 r1 = GetBaseY(m);
    Vector4 r2 = GetBaseZ(m);
    Vector4 r3 = GetBaseW(m);

    CHECK(GetX(r0) == mm.M11);
    CHECK(GetY(r0) == mm.M12);
    CHECK(GetZ(r0) == mm.M13);
    CHECK(GetW(r0) == mm.M14);

    CHECK(GetX(r1) == mm.M21);
    CHECK(GetY(r1) == mm.M22);
    CHECK(GetZ(r1) == mm.M23);
    CHECK(GetW(r1) == mm.M24);

    CHECK(GetX(r2) == mm.M31);
    CHECK(GetY(r2) == mm.M32);
    CHECK(GetZ(r2) == mm.M33);
    CHECK(GetW(r2) == mm.M34);

    CHECK(GetX(r3) == mm.M41);
    CHECK(GetY(r3) == mm.M42);
    CHECK(GetZ(r3) == mm.M43);
    CHECK(GetW(r3) == mm.M44);

    Matrix const mr = Multiply(Identity<Matrix>(), m);

    r0 = GetBaseX(mr);
    r1 = GetBaseY(mr);
    r2 = GetBaseZ(mr);
    r3 = GetBaseW(mr);

    CHECK_FALSE(IsEqual(r0, r1));

    CHECK(GetX(r0) == mm.M11);
    CHECK(GetY(r0) == mm.M12);
    CHECK(GetZ(r0) == mm.M13);
    CHECK(GetW(r0) == mm.M14);

    CHECK(GetX(r1) == mm.M21);
    CHECK(GetY(r1) == mm.M22);
    CHECK(GetZ(r1) == mm.M23);
    CHECK(GetW(r1) == mm.M24);

    CHECK(GetX(r2) == mm.M31);
    CHECK(GetY(r2) == mm.M32);
    CHECK(GetZ(r2) == mm.M33);
    CHECK(GetW(r2) == mm.M34);

    CHECK(GetX(r3) == mm.M41);
    CHECK(GetY(r3) == mm.M42);
    CHECK(GetZ(r3) == mm.M43);
    CHECK(GetW(r3) == mm.M44);
}

TEST_CASE("Maths / LoadStore")
{
    using namespace Graphyte::Maths;

    Float4A const f1{ 1.0F, 2.0F, 3.0F, 4.0F };
    Vector4 const v1 = Load<Vector4>(&f1);

    CHECK(GetX(v1) == 1.0F);
    CHECK(GetY(v1) == 2.0F);
    CHECK(GetZ(v1) == 3.0F);
    CHECK(GetW(v1) == 4.0F);

    Float3A f2{};
    Store<Vector4>(&f2, v1);

    CHECK(f2.X == 1.0F);
    CHECK(f2.Y == 2.0F);
    CHECK(f2.Z == 3.0F);

    Plane const p1 = Load<Plane>(&f1);
    Float2A f3{};
    Store<Plane>(&f3, p1);

    CHECK(f3.X == 1.0F);
    CHECK(f3.Y == 2.0F);
}

TEST_CASE("Maths / Vector4 / Cross Product")
{
    using namespace Graphyte::Maths;

    Vector4 const a = Make<Vector4>(1.0F, 5.0F, 3.0F, 4.0F);
    Vector4 const b = Make<Vector4>(7.0F, 7.0F, 9.0F, 10.0F);
    Vector4 const c = Make<Vector4>(3.0F, 7.0F, 4.0F, -1.0F);

    Vector4 const abc = Cross(a, b, c);

    Graphyte::Maths::Impl::ConstFloat32x4 cc;
    cc.V = abc.V;

    CHECK(cc.F[0] == -154.0F);
    CHECK(cc.F[1] == -66.0F);
    CHECK(cc.F[2] == 220.0F);
    CHECK(cc.F[3] == -44.0F);
}

TEST_CASE("Maths / Vector4 / Dot Product")
{
    using namespace Graphyte::Maths;

    Vector4 const a = Make<Vector4>(1.0F, 5.0F, 3.0F, 4.0F);
    Vector4 const b = Make<Vector4>(7.0F, 7.0F, 9.0F, 10.0F);
    Vector4 const c = Make<Vector4>(3.0F, 7.0F, 4.0F, -1.0F);

    //Vector4 Dot(a, b);
}

TEST_CASE("Maths / Vector / Rounding")
{
    using namespace Graphyte::Maths;

    Vector4 const v1 = Make<Vector4>(0.1F, 0.4F, 0.6F, 0.9F);
    Vector4 const v2 = Make<Vector4>(-0.1F, 0.5F, -0.5F, -0.9F);

    Vector4 const v3 = Make<Vector4>(10.1F, 3330.4F, 5510.6F, 124420.9F);
    Vector4 const v4 = Make<Vector4>(-20.1F, 44444440.5F, -1120.5F, -512520.9F);

    SECTION("Round")
    {
        Vector4 const r1 = Round(v1);
        Vector4 const r2 = Round(v2);
        Vector4 const r3 = Round(v3);
        Vector4 const r4 = Round(v4);

        CHECK(GetX(r1) == Approx{ 0.0F });
        CHECK(GetY(r1) == Approx{ 0.0F });
        CHECK(GetZ(r1) == Approx{ 1.0F });
        CHECK(GetW(r1) == Approx{ 1.0F });

        CHECK(GetX(r2) == Approx{ 0.0F });
        CHECK(GetY(r2) == Approx{ 0.0F });
        CHECK(GetZ(r2) == Approx{ 0.0F });
        CHECK(GetW(r2) == Approx{ -1.0F });

        CHECK(GetX(r3) == Approx{ 10.0F });
        CHECK(GetY(r3) == Approx{ 3330.0F });
        CHECK(GetZ(r3) == Approx{ 5511.0F });
        CHECK(GetW(r3) == Approx{ 124421.0F });

        CHECK(GetX(r4) == Approx{ -20.0F });
        CHECK(GetY(r4) == Approx{ 44444440.0F });
        CHECK(GetZ(r4) == Approx{ -1120.0F });
        CHECK(GetW(r4) == Approx{ -512521.0F });

        CHECK(Round(0.1F) == Approx{ 0.0F });
        CHECK(Round(0.4F) == Approx{ 0.0F });
        CHECK(Round(0.6F) == Approx{ 1.0F });
        CHECK(Round(0.9F) == Approx{ 1.0F });
        CHECK(Round(-0.1F) == Approx{ 0.0F });
        CHECK(Round(0.5F) == Approx{ 1.0F });
        CHECK(Round(-0.5F) == Approx{ -1.0F });
        CHECK(Round(-0.9F) == Approx{ -1.0F });
    }

    SECTION("Truncate")
    {
        Vector4 const r1 = Truncate(v1);
        Vector4 const r2 = Truncate(v2);
        Vector4 const r3 = Truncate(v3);
        Vector4 const r4 = Truncate(v4);

        CHECK(GetX(r1) == Approx{ 0.0F });
        CHECK(GetY(r1) == Approx{ 0.0F });
        CHECK(GetZ(r1) == Approx{ 0.0F });
        CHECK(GetW(r1) == Approx{ 0.0F });

        CHECK(GetX(r2) == Approx{ 0.0F });
        CHECK(GetY(r2) == Approx{ 0.0F });
        CHECK(GetZ(r2) == Approx{ 0.0F });
        CHECK(GetW(r2) == Approx{ 0.0F });

        CHECK(GetX(r3) == Approx{ 10.0F });
        CHECK(GetY(r3) == Approx{ 3330.0F });
        CHECK(GetZ(r3) == Approx{ 5510.0F });
        CHECK(GetW(r3) == Approx{ 124420.0F });

        CHECK(GetX(r4) == Approx{ -20.0F });
        CHECK(GetY(r4) == Approx{ 44444440.0F });
        CHECK(GetZ(r4) == Approx{ -1120.0F });
        CHECK(GetW(r4) == Approx{ -512520.0F });

        CHECK(Truncate(0.1F) == Approx{ 0.0F });
        CHECK(Truncate(0.4F) == Approx{ 0.0F });
        CHECK(Truncate(0.6F) == Approx{ 0.0F });
        CHECK(Truncate(0.9F) == Approx{ 0.0F });
        CHECK(Truncate(-0.1F) == Approx{ 0.0F });
        CHECK(Truncate(0.5F) == Approx{ 0.0F });
        CHECK(Truncate(-0.5F) == Approx{ -0.0F });
        CHECK(Truncate(-0.9F) == Approx{ -0.0F });
    }

    SECTION("Floor")
    {
        Vector4 const r1 = Floor(v1);
        Vector4 const r2 = Floor(v2);
        Vector4 const r3 = Floor(v3);
        Vector4 const r4 = Floor(v4);

        CHECK(GetX(r1) == Approx{ 0.0F });
        CHECK(GetY(r1) == Approx{ 0.0F });
        CHECK(GetZ(r1) == Approx{ 0.0F });
        CHECK(GetW(r1) == Approx{ 0.0F });

        CHECK(GetX(r2) == Approx{ -1.0F });
        CHECK(GetY(r2) == Approx{ 0.0F });
        CHECK(GetZ(r2) == Approx{ -1.0F });
        CHECK(GetW(r2) == Approx{ -1.0F });

        CHECK(GetX(r3) == Approx{ 10.0F });
        CHECK(GetY(r3) == Approx{ 3330.0F });
        CHECK(GetZ(r3) == Approx{ 5510.0F });
        CHECK(GetW(r3) == Approx{ 124420.0F });

        CHECK(GetX(r4) == Approx{ -21.0F });
        CHECK(GetY(r4) == Approx{ 44444440.0F });
        CHECK(GetZ(r4) == Approx{ -1121.0F });
        CHECK(GetW(r4) == Approx{ -512520.0F });

        CHECK(Floor(0.1F) == Approx{ 0.0F });
        CHECK(Floor(0.4F) == Approx{ 0.0F });
        CHECK(Floor(0.6F) == Approx{ 0.0F });
        CHECK(Floor(0.9F) == Approx{ 0.0F });
        CHECK(Floor(-0.1F) == Approx{ -1.0F });
        CHECK(Floor(0.5F) == Approx{ 0.0F });
        CHECK(Floor(-0.5F) == Approx{ -1.0F });
        CHECK(Floor(-0.9F) == Approx{ -1.0F });
    }

    SECTION("Ceiling")
    {
        Vector4 const r1 = Ceiling(v1);
        Vector4 const r2 = Ceiling(v2);
        Vector4 const r3 = Ceiling(v3);
        Vector4 const r4 = Ceiling(v4);

        CHECK(GetX(r1) == Approx{ 1.0F });
        CHECK(GetY(r1) == Approx{ 1.0F });
        CHECK(GetZ(r1) == Approx{ 1.0F });
        CHECK(GetW(r1) == Approx{ 1.0F });

        CHECK(GetX(r2) == Approx{ 0.0F });
        CHECK(GetY(r2) == Approx{ 1.0F });
        CHECK(GetZ(r2) == Approx{ 0.0F });
        CHECK(GetW(r2) == Approx{ 0.0F });

        CHECK(GetX(r3) == Approx{ 11.0F });
        CHECK(GetY(r3) == Approx{ 3331.0F });
        CHECK(GetZ(r3) == Approx{ 5511.0F });
        CHECK(GetW(r3) == Approx{ 124420.0F });

        CHECK(GetX(r4) == Approx{ -20.0F });
        CHECK(GetY(r4) == Approx{ 44444440.0F });
        CHECK(GetZ(r4) == Approx{ -1120.0F });
        CHECK(GetW(r4) == Approx{ -512520.0F });

        CHECK(Ceiling(0.1F) == Approx{ 1.0F });
        CHECK(Ceiling(0.4F) == Approx{ 1.0F });
        CHECK(Ceiling(0.6F) == Approx{ 1.0F });
        CHECK(Ceiling(0.9F) == Approx{ 1.0F });
        CHECK(Ceiling(-0.1F) == Approx{ 0.0F });
        CHECK(Ceiling(0.5F) == Approx{ 1.0F });
        CHECK(Ceiling(-0.5F) == Approx{ -0.0F });
        CHECK(Ceiling(-0.9F) == Approx{ -0.0F });
    }

    SECTION("Fraction")
    {
        Vector4 const r1 = Fraction(v1, One<Vector4>());
        Vector4 const r2 = Fraction(v2, One<Vector4>());
        Vector4 const r3 = Fraction(v3, One<Vector4>());
        Vector4 const r4 = Fraction(v4, One<Vector4>());

        CHECK(GetX(r1) == Approx{ 0.1F });
        CHECK(GetY(r1) == Approx{ 0.4F });
        CHECK(GetZ(r1) == Approx{ 0.6F });
        CHECK(GetW(r1) == Approx{ 0.9F });

        CHECK(GetX(r2) == Approx{ -0.1F });
        CHECK(GetY(r2) == Approx{ 0.5F });
        CHECK(GetZ(r2) == Approx{ -0.5F });
        CHECK(GetW(r2) == Approx{ -0.9F });

        CHECK(GetX(r3) == Approx{ 0.1F });
        CHECK(GetY(r3) == Approx{ 0.4F }.margin(0.01F));
        CHECK(GetZ(r3) == Approx{ 0.6F }.margin(0.01F));
        CHECK(GetW(r3) == Approx{ 0.9F }.margin(0.01F));

        CHECK(GetX(r4) == Approx{ -0.1F });
        CHECK(GetY(r4) == Approx{ 0.0F }.margin(0.01F));
        CHECK(GetZ(r4) == Approx{ -0.5F });
        CHECK(GetW(r4) == Approx{ -0.9F }.margin(0.01F));

        CHECK(Fraction(0.1F, 1.0F) == Approx{ 0.1F });
        CHECK(Fraction(0.4F, 1.0F) == Approx{ 0.4F });
        CHECK(Fraction(0.6F, 1.0F) == Approx{ 0.6F });
        CHECK(Fraction(0.9F, 1.0F) == Approx{ 0.9F });
        CHECK(Fraction(-0.1F, 1.0F) == Approx{ -0.1F });
        CHECK(Fraction(0.5F, 1.0F) == Approx{ 0.5F });
        CHECK(Fraction(-0.5F, 1.0F) == Approx{ -0.5F });
        CHECK(Fraction(-0.9F, 1.0F) == Approx{ -0.9F });
    }
}

#if false

mathinline Graphyte::Maths::Vec4 ToVec4(float x, Graphyte::Maths::Vec2 v, float w) noexcept
{
    Graphyte::Maths::Vec4 const v_xwxw = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(x, w, x, w);
    return Graphyte::Maths::Permute<0, 4, 5, 1>(v_xwxw, { v.V });
}

mathinline Graphyte::Maths::Vec4 ToVec4(float x, float y, Graphyte::Maths::Vec2 v) noexcept
{
    Graphyte::Maths::Vec4 const v_xyxy = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(x, y, x, y);
    return Graphyte::Maths::Permute<0, 1, 4, 5>(v_xyxy, { v.V });
}

mathinline Graphyte::Maths::Vec4 ToVec4(Graphyte::Maths::Vec2 v, float z, float w) noexcept
{
    Graphyte::Maths::Vec4 const v_zwzw = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(z, w, z, w);
    return Graphyte::Maths::Permute<4, 5, 0, 1>(v_zwzw, { v.V });
}

mathinline Graphyte::Maths::Vec4 ToVec4(float x, Graphyte::Maths::Vec3 v) noexcept
{
    Graphyte::Maths::Vec4 const v_xxxx = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(x);
    return Graphyte::Maths::Permute<4, 0, 1, 2>({ v.V }, v_xxxx);
}

mathinline Graphyte::Maths::Vec4 ToVec4(Graphyte::Maths::Vec3 v, float w) noexcept
{
    Graphyte::Maths::Vec4 const v_wwww = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(w);
    return Graphyte::Maths::Permute<0, 1, 2, 4>({ v.V }, v_wwww);
}

mathinline Graphyte::Maths::Vec3 ToVec3(float x, Graphyte::Maths::Vec2 v) noexcept
{
    Graphyte::Maths::Vec4 const v_xxxx = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(x);
    return { Graphyte::Maths::Permute<4, 0, 1, 4>({ v.V }, v_xxxx).V };
}

mathinline Graphyte::Maths::Vec3 ToVec3(Graphyte::Maths::Vec2 v, float z) noexcept
{
    Graphyte::Maths::Vec4 const v_zzzz = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(z);
    return { Graphyte::Maths::Permute<0, 1, 4, 4>({v.V}, v_zzzz).V };
}

TEST_CASE("Maths / Vector / Get and Set component value")
{
    using namespace Graphyte::Maths;

    Vec4 const v = Zero<Vec4>();

    REQUIRE(GetX(v) == Approx{ 0.0F });
    REQUIRE(GetY(v) == Approx{ 0.0F });
    REQUIRE(GetZ(v) == Approx{ 0.0F });
    REQUIRE(GetW(v) == Approx{ 0.0F });


    Vec4 const va = SetX(v, 1.0F);

    REQUIRE(GetX(va) == Approx{ 1.0F });
    REQUIRE(GetY(va) == Approx{ 0.0F });
    REQUIRE(GetZ(va) == Approx{ 0.0F });
    REQUIRE(GetW(va) == Approx{ 0.0F });

    Vec4 const vb = SetY(v, 1.0F);

    REQUIRE(GetX(vb) == Approx{ 0.0F });
    REQUIRE(GetY(vb) == Approx{ 1.0F });
    REQUIRE(GetZ(vb) == Approx{ 0.0F });
    REQUIRE(GetW(vb) == Approx{ 0.0F });

    Vec4 const vc = SetZ(v, 1.0F);

    REQUIRE(GetX(vc) == Approx{ 0.0F });
    REQUIRE(GetY(vc) == Approx{ 0.0F });
    REQUIRE(GetZ(vc) == Approx{ 1.0F });
    REQUIRE(GetW(vc) == Approx{ 0.0F });

    Vec4 const vd = SetW(v, 1.0F);

    REQUIRE(GetX(vd) == Approx{ 0.0F });
    REQUIRE(GetY(vd) == Approx{ 0.0F });
    REQUIRE(GetZ(vd) == Approx{ 0.0F });
    REQUIRE(GetW(vd) == Approx{ 1.0F });
}

TEST_CASE("Maths / Vector / Making Vec4 form other vectors")
{
    using namespace Graphyte::Maths;

    SECTION("From Vec3")
    {
        Vec3 const xyz = Make<Vec3>(1.0F, 2.0F, 3.0F);

        SECTION("xyz | w")
        {
            Vec4 const r = ToVec4(xyz, 4.0F);

            CHECK(GetX(r) == Approx{ 1.0F });
            CHECK(GetY(r) == Approx{ 2.0F });
            CHECK(GetZ(r) == Approx{ 3.0F });
            CHECK(GetW(r) == Approx{ 4.0F });
        }

        SECTION("w | xyz")
        {
            Vec4 const r = ToVec4(4.0F, xyz);

            CHECK(GetX(r) == Approx{ 4.0F });
            CHECK(GetY(r) == Approx{ 1.0F });
            CHECK(GetZ(r) == Approx{ 2.0F });
            CHECK(GetW(r) == Approx{ 3.0F });
        }
    }

    SECTION("From Vec2")
    {
        Vec2 const xy = Make<Vec2>(1.0F, 2.0F);

        SECTION("xy | z | w")
        {
            Vec4 const r = ToVec4(xy, 3.0F, 4.0F);

            CHECK(GetX(r) == Approx{ 1.0F });
            CHECK(GetY(r) == Approx{ 2.0F });
            CHECK(GetZ(r) == Approx{ 3.0F });
            CHECK(GetW(r) == Approx{ 4.0F });
        }

        SECTION("z | xy | w")
        {
            Vec4 const r = ToVec4(3.0F, xy, 4.0F);

            CHECK(GetX(r) == Approx{ 3.0F });
            CHECK(GetY(r) == Approx{ 1.0F });
            CHECK(GetZ(r) == Approx{ 2.0F });
            CHECK(GetW(r) == Approx{ 4.0F });
        }

        SECTION("z | w | xy")
        {
            Vec4 const r = ToVec4(3.0F, 4.0F, xy);

            CHECK(GetX(r) == Approx{ 3.0F });
            CHECK(GetY(r) == Approx{ 4.0F });
            CHECK(GetZ(r) == Approx{ 1.0F });
            CHECK(GetW(r) == Approx{ 2.0F });
        }
    }
}

TEST_CASE("Maths / Vector / Making Vec3 from other vectors")
{
    using namespace Graphyte::Maths;

    SECTION("From Vec2")
    {
        Vec2 const xy = Make<Vec2>(1.0F, 2.0F);

        SECTION("z | xy")
        {
            Vec3 const r = ToVec3(5.0F, xy);

            CHECK(GetX(r) == Approx{ 5.0F });
            CHECK(GetY(r) == Approx{ 1.0F });
            CHECK(GetZ(r) == Approx{ 2.0F });
        }

        SECTION("xy | z")
        {
            Vec3 const r = ToVec3(xy, 5.0F);

            CHECK(GetX(r) == Approx{ 1.0F });
            CHECK(GetY(r) == Approx{ 2.0F });
            CHECK(GetZ(r) == Approx{ 5.0F });
        }
    }
}

TEST_CASE("Maths / Vector / Select by bool value")
{
}

#if false
TEST_CASE("Vec4 Operations")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::UnitX<M::Vec4>();
    M::Vec4 const v2 = M::UnitY<M::Vec4>();
    M::Vec4 const v3 = M::Add(v1, v2);

    CHECK(M::GetX(v3) == Approx{ 1.0F });
    CHECK(M::GetY(v3) == Approx{ 1.0F });
    CHECK(M::GetZ(v3) == Approx{ 0.0F });
    CHECK(M::GetW(v3) == Approx{ 0.0F });

    M::Vec4 const v4 = M::Make<M::Vec4>(2.0F, 3.0F);

    CHECK(M::GetX(v4) == Approx{ 2.0F });
    CHECK(M::GetY(v4) == Approx{ 3.0F });
    CHECK(M::GetZ(v4) == Approx{ 0.0F });
    CHECK(M::GetW(v4) == Approx{ 0.0F });

    M::Vec4 const v5 = M::SplatX(v4);

    CHECK(M::GetX(v5) == Approx{ 2.0F });
    CHECK(M::GetY(v5) == Approx{ 2.0F });
    CHECK(M::GetZ(v5) == Approx{ 2.0F });
    CHECK(M::GetW(v5) == Approx{ 2.0F });

    M::Vec4 const v6 = M::Mul(M::Add(v1, v2), M::Sub(v3, v4));

    CHECK(M::GetX(v6) == Approx{ -1.0F });
    CHECK(M::GetY(v6) == Approx{ -2.0F });
    CHECK(M::GetZ(v6) == Approx{ 0.0F });
    CHECK(M::GetW(v6) == Approx{ 0.0F });
}

TEST_CASE("Fused Multiply Add / Sub operations")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::Make<M::Vec4>(1.0F, 2.0F, 3.0F, 4.0F);
    M::Vec4 const v2 = M::Make<M::Vec4>(4.0F, 5.0F, 6.0F, 7.0F);
    M::Vec4 const v3 = M::Make<M::Vec4>(3.0F, 5.0F, 7.0F, 9.0F);

    SECTION("mul-add")
    {
        M::Vec4 const r = M::MulAdd(v1, v2, v3);

        CHECK(M::GetX(r) == Approx{ 7.0F });
        CHECK(M::GetY(r) == Approx{ 15.0F });
        CHECK(M::GetZ(r) == Approx{ 25.0F });
        CHECK(M::GetW(r) == Approx{ 37.0F });
    }

    SECTION("mul-sub")
    {
        M::Vec4 const r = M::MulSub(v1, v2, v3);

        CHECK(M::GetX(r) == Approx{ 1.0F });
        CHECK(M::GetY(r) == Approx{ 5.0F });
        CHECK(M::GetZ(r) == Approx{ 11.0F });
        CHECK(M::GetW(r) == Approx{ 19.0F });
    }

    SECTION("neg-mul-add")
    {
        M::Vec4 const r = M::NegMulAdd(v1, v2, v3);

        CHECK(M::GetX(r) == Approx{ -1.0F });
        CHECK(M::GetY(r) == Approx{ -5.0F });
        CHECK(M::GetZ(r) == Approx{ -11.0F });
        CHECK(M::GetW(r) == Approx{ -19.0F });
    }

    SECTION("neg-mul-sub")
    {
        M::Vec4 const r = M::NegMulSub(v1, v2, v3);

        CHECK(M::GetX(r) == Approx{ -7.0F });
        CHECK(M::GetY(r) == Approx{ -15.0F });
        CHECK(M::GetZ(r) == Approx{ -25.0F });
        CHECK(M::GetW(r) == Approx{ -37.0F });
    }
}

TEST_CASE("Vec / rounding")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::Make<M::Vec4>(0.25F, 0.5F, 0.75F, 1.0F);
    M::Vec4 const v2 = M::Make<M::Vec4>(0.15F, 0.55F, 0.65F, 1.1F);

    SECTION("min(v1,v2)")
    {
        M::Vec4 const r = M::Min(v1, v2);

        CHECK(M::GetX(r) == Approx{ 0.15F });
        CHECK(M::GetY(r) == Approx{ 0.5F });
        CHECK(M::GetZ(r) == Approx{ 0.65F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("max(v1,v2)")
    {
        M::Vec4 const r = M::Max(v1, v2);

        CHECK(M::GetX(r) == Approx{ 0.25F });
        CHECK(M::GetY(r) == Approx{ 0.55F });
        CHECK(M::GetZ(r) == Approx{ 0.75F });
        CHECK(M::GetW(r) == Approx{ 1.1F });
    }

    SECTION("round(v1)")
    {
        M::Vec4 const r = M::Round(v1);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 0.0F });
        CHECK(M::GetZ(r) == Approx{ 1.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("round(v2)")
    {
        M::Vec4 const r = M::Round(v2);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 1.0F });
        CHECK(M::GetZ(r) == Approx{ 1.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("truncate(v1)")
    {
        M::Vec4 const r = M::Truncate(v1);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 0.0F });
        CHECK(M::GetZ(r) == Approx{ 0.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("truncate(v2)")
    {
        M::Vec4 const r = M::Truncate(v2);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 0.0F });
        CHECK(M::GetZ(r) == Approx{ 0.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("floor(v1)")
    {
        M::Vec4 const r = M::Floor(v1);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 0.0F });
        CHECK(M::GetZ(r) == Approx{ 0.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("floor(v2)")
    {
        M::Vec4 const r = M::Floor(v2);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 0.0F });
        CHECK(M::GetZ(r) == Approx{ 0.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("ceiling(v1)")
    {
        M::Vec4 const r = M::Ceiling(v1);

        CHECK(M::GetX(r) == Approx{ 1.0F });
        CHECK(M::GetY(r) == Approx{ 1.0F });
        CHECK(M::GetZ(r) == Approx{ 1.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("ceiling(v2)")
    {
        M::Vec4 const r = M::Ceiling(v2);

        CHECK(M::GetX(r) == Approx{ 1.0F });
        CHECK(M::GetY(r) == Approx{ 1.0F });
        CHECK(M::GetZ(r) == Approx{ 1.0F });
        CHECK(M::GetW(r) == Approx{ 2.0F });
    }
}

TEST_CASE("Setting vector components")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::Zero<M::Vec4>();

    CHECK(M::GetX(v1) == Approx{ 0.0F });
    CHECK(M::GetY(v1) == Approx{ 0.0F });
    CHECK(M::GetZ(v1) == Approx{ 0.0F });
    CHECK(M::GetW(v1) == Approx{ 0.0F });

    M::Vec4 const v2 = M::SetX(v1, 1.0F);

    CHECK(M::GetX(v2) == Approx{ 1.0F });
    CHECK(M::GetY(v2) == Approx{ 0.0F });
    CHECK(M::GetZ(v2) == Approx{ 0.0F });
    CHECK(M::GetW(v2) == Approx{ 0.0F });

    M::Vec4 const v3 = M::SetY(v2, 2.0F);

    CHECK(M::GetX(v3) == Approx{ 1.0F });
    CHECK(M::GetY(v3) == Approx{ 2.0F });
    CHECK(M::GetZ(v3) == Approx{ 0.0F });
    CHECK(M::GetW(v3) == Approx{ 0.0F });

    M::Vec4 const v4 = M::SetZ(v3, 3.0F);

    CHECK(M::GetX(v4) == Approx{ 1.0F });
    CHECK(M::GetY(v4) == Approx{ 2.0F });
    CHECK(M::GetZ(v4) == Approx{ 3.0F });
    CHECK(M::GetW(v4) == Approx{ 0.0F });

    M::Vec4 const v5 = M::SetW(v4, 4.0F);

    CHECK(M::GetX(v5) == Approx{ 1.0F });
    CHECK(M::GetY(v5) == Approx{ 2.0F });
    CHECK(M::GetZ(v5) == Approx{ 3.0F });
    CHECK(M::GetW(v5) == Approx{ 4.0F });
}

TEST_CASE("Vec4 - length & normalization")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const ux = M::UnitX<M::Vec4>();
    M::Vec4 const uy = M::UnitY<M::Vec4>();
    M::Vec4 const uz = M::UnitZ<M::Vec4>();
    M::Vec4 const uw = M::UnitW<M::Vec4>();

    // double them
    M::Vec4 const uxx = M::Add(ux, ux);
    M::Vec4 const uyy = M::Add(uy, uy);
    M::Vec4 const uzz = M::Add(uz, uz);
    M::Vec4 const uww = M::Add(uw, uw);

    CHECK(M::GetX(M::Length(uxx)) == Approx{ 2.0F });
    CHECK(M::GetX(M::Length(uyy)) == Approx{ 2.0F });
    CHECK(M::GetX(M::Length(uzz)) == Approx{ 2.0F });
    CHECK(M::GetX(M::Length(uww)) == Approx{ 2.0F });

    M::Vec4 const nxx = M::Normalize(uxx);
    M::Vec4 const nyy = M::Normalize(uyy);
    M::Vec4 const nzz = M::Normalize(uzz);
    M::Vec4 const nww = M::Normalize(uww);

    CHECK(M::GetX(M::Length(nxx)) == Approx{ 1.0F });
    CHECK(M::GetX(M::Length(nyy)) == Approx{ 1.0F });
    CHECK(M::GetX(M::Length(nzz)) == Approx{ 1.0F });
    CHECK(M::GetX(M::Length(nww)) == Approx{ 1.0F });

    CHECK(M::GetX(M::Length(M::Zero<M::Vec4>())) == Approx{ 0.0F });
}


TEST_CASE("Vec3 - length & normalization")
{
    namespace M = Graphyte::Maths;

    M::Vec3 const ux = M::UnitX<M::Vec3>();
    M::Vec3 const uy = M::UnitY<M::Vec3>();
    M::Vec3 const uz = M::UnitZ<M::Vec3>();

    // double them
    M::Vec3 const uxx = M::Add(ux, ux);
    M::Vec3 const uyy = M::Add(uy, uy);
    M::Vec3 const uzz = M::Add(uz, uz);

    CHECK(M::GetX(M::Length(uxx)) == Approx{ 2.0F });
    CHECK(M::GetX(M::Length(uyy)) == Approx{ 2.0F });
    CHECK(M::GetX(M::Length(uzz)) == Approx{ 2.0F });

    M::Vec3 const nxx = M::Normalize(uxx);
    M::Vec3 const nyy = M::Normalize(uyy);
    M::Vec3 const nzz = M::Normalize(uzz);

    CHECK(M::GetX(M::Length(nxx)) == Approx{ 1.0F });
    CHECK(M::GetX(M::Length(nyy)) == Approx{ 1.0F });
    CHECK(M::GetX(M::Length(nzz)) == Approx{ 1.0F });

    CHECK(M::GetX(M::Length(M::Zero<M::Vec3>())) == Approx{ 0.0F });
}

TEST_CASE("Vec4 - order comparable")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::UnitX<M::Vec4>();
    M::Vec4 const v2 = M::UnitY<M::Vec4>();
    M::Vec4 const v3 = M::UnitZ<M::Vec4>();
    M::Vec4 const v4 = M::UnitW<M::Vec4>();

    CHECK_FALSE(M::IsEq(v1, v2));
    CHECK_FALSE(M::IsEq(v2, v3));
    CHECK_FALSE(M::IsEq(v3, v4));
    CHECK_FALSE(M::IsEq(v4, v1));

    CHECK(M::IsNeq(v1, v2));
    CHECK(M::IsNeq(v2, v3));
    CHECK(M::IsNeq(v3, v4));
    CHECK(M::IsNeq(v4, v1));

    CHECK_FALSE(M::IsLt(v1, v2));
    CHECK_FALSE(M::IsLt(v2, v3));
    CHECK_FALSE(M::IsLt(v3, v4));
    CHECK_FALSE(M::IsLt(v4, v1));

    CHECK_FALSE(M::IsLe(v1, v2));
    CHECK_FALSE(M::IsLe(v2, v3));
    CHECK_FALSE(M::IsLe(v3, v4));
    CHECK_FALSE(M::IsLe(v4, v1));

    CHECK_FALSE(M::IsGt(v1, v2));
    CHECK_FALSE(M::IsGt(v2, v3));
    CHECK_FALSE(M::IsGt(v3, v4));
    CHECK_FALSE(M::IsGt(v4, v1));

    CHECK_FALSE(M::IsGe(v1, v2));
    CHECK_FALSE(M::IsGe(v2, v3));
    CHECK_FALSE(M::IsGe(v3, v4));
    CHECK_FALSE(M::IsGe(v4, v1));

    CHECK(M::IsEq(M::Infinity<M::Vec4>(), M::Infinity<M::Vec4>()));
    CHECK_FALSE(M::IsNeq(M::Infinity<M::Vec4>(), M::Infinity<M::Vec4>()));

    REQUIRE(M::MulAdd(1.0F, 1.0F, 1.0F) == Approx{ 2.0F });
}

TEST_CASE("Vec4 - componentwise comparisons")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::UnitX<M::Vec4>();
    M::Vec4 const v2 = M::UnitY<M::Vec4>();
    M::Vec4 const v3 = M::UnitZ<M::Vec4>();
    M::Vec4 const v4 = M::UnitW<M::Vec4>();

    M::Bool4 const b11 = M::CmpEq(v1, v1);
    M::Bool4 const b12 = M::CmpEq(v1, v2);
    M::Bool4 const b13 = M::CmpEq(v1, v3);
    M::Bool4 const b14 = M::CmpEq(v1, v4);

    M::Bool4 const b21 = M::CmpEq(v2, v1);
    M::Bool4 const b22 = M::CmpEq(v2, v2);
    M::Bool4 const b23 = M::CmpEq(v2, v3);
    M::Bool4 const b24 = M::CmpEq(v2, v4);

    M::Bool4 const b31 = M::CmpEq(v3, v1);
    M::Bool4 const b32 = M::CmpEq(v3, v2);
    M::Bool4 const b33 = M::CmpEq(v3, v3);
    M::Bool4 const b34 = M::CmpEq(v3, v4);

    M::Bool4 const b41 = M::CmpEq(v4, v1);
    M::Bool4 const b42 = M::CmpEq(v4, v2);
    M::Bool4 const b43 = M::CmpEq(v4, v3);
    M::Bool4 const b44 = M::CmpEq(v4, v4);

    CHECK(M::AnyTrue( b11));
    CHECK(M::AllTrue( b11));
    CHECK_FALSE(M::AnyFalse(b11));
    CHECK_FALSE(M::AllFalse(b11));

    CHECK(M::AnyTrue( b12));
    CHECK_FALSE(M::AllTrue( b12));
    CHECK(M::AnyFalse(b12));
    CHECK_FALSE(M::AllFalse(b12));

    CHECK(M::AnyTrue( b13));
    CHECK_FALSE(M::AllTrue( b13));
    CHECK(M::AnyFalse(b13));
    CHECK_FALSE(M::AllFalse(b13));

    CHECK(M::AnyTrue( b14));
    CHECK_FALSE(M::AllTrue( b14));
    CHECK(M::AnyFalse(b14));
    CHECK_FALSE(M::AllFalse(b14));

    CHECK(M::AnyTrue( b21));
    CHECK_FALSE(M::AllTrue( b21));
    CHECK(M::AnyFalse(b21));
    CHECK_FALSE(M::AllFalse(b21));

    CHECK(M::AnyTrue( b22));
    CHECK(M::AllTrue( b22));
    CHECK_FALSE(M::AnyFalse(b22));
    CHECK_FALSE(M::AllFalse(b22));

    CHECK(M::AnyTrue( b23));
    CHECK_FALSE(M::AllTrue( b23));
    CHECK(M::AnyFalse(b23));
    CHECK_FALSE(M::AllFalse(b23));

    CHECK(M::AnyTrue( b24));
    CHECK_FALSE(M::AllTrue( b24));
    CHECK(M::AnyFalse(b24));
    CHECK_FALSE(M::AllFalse(b24));

    CHECK(M::AnyTrue( b11));
    CHECK(M::AllTrue( b11));
    CHECK_FALSE(M::AnyFalse(b11));
    CHECK_FALSE(M::AllFalse(b11));

    CHECK(M::AnyTrue( b32));
    CHECK_FALSE(M::AllTrue( b32));
    CHECK(M::AnyFalse(b32));
    CHECK_FALSE(M::AllFalse(b32));

    CHECK(M::AnyTrue( b33));
    CHECK(M::AllTrue( b33));
    CHECK_FALSE(M::AnyFalse(b33));
    CHECK_FALSE(M::AllFalse(b33));

    CHECK(M::AnyTrue( b34));
    CHECK_FALSE(M::AllTrue( b34));
    CHECK(M::AnyFalse(b34));
    CHECK_FALSE(M::AllFalse(b34));

    CHECK(M::AnyTrue( b41));
    CHECK_FALSE(M::AllTrue( b41));
    CHECK(M::AnyFalse(b41));
    CHECK_FALSE(M::AllFalse(b41));

    CHECK(M::AnyTrue( b42));
    CHECK_FALSE(M::AllTrue( b42));
    CHECK(M::AnyFalse(b42));
    CHECK_FALSE(M::AllFalse(b42));

    CHECK(M::AnyTrue( b43));
    CHECK_FALSE(M::AllTrue( b43));
    CHECK(M::AnyFalse(b43));
    CHECK_FALSE(M::AllFalse(b43));

    CHECK(M::AnyTrue( b44));
    CHECK(M::AllTrue( b44));
    CHECK_FALSE(M::AnyFalse(b44));
    CHECK_FALSE(M::AllFalse(b44));
}

//TEST_CASE("operators")
//{
//    namespace M = Graphyte::Maths;
//
//    M::Vec4 const v1 = M::Make<M::Vec4>(1.0F);
//    M::Vec4 const v2 = M::Make<M::Vec4>(2.0F);
//    M::Vec4 const v3 = M::Make<M::Vec4>(3.0F);
//
//    REQUIRE(v1 != v2);
//    REQUIRE_FALSE(v1 == v2);
//
//    REQUIRE(M::IsEqEps(v1 + v2, v3, M::Epsilon<M::Vec4>()));
//}

template <typename T>
int check() requires(Graphyte::Maths::EqualComparable<T>)
{
    return 1;
}

template <typename T>
int check() requires(!Graphyte::Maths::EqualComparable<T>)
{
    return 0;
}

TEST_CASE("xxx")
{
    CHECK(check<int>() == 0);
    CHECK(check<Graphyte::Maths::Vec4>() == 1);
}
#endif

#endif
