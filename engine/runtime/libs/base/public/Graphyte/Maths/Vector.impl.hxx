#if 0
    struct noise final
    {
        mathinline static float mathcall mod289(float x) noexcept
        {
            return x - Floor(x * (1.0F / 289.0F)) * 289.0F;
        }
        mathinline static Vector2 mathcall mod289(Vector2 x) noexcept
        {
            return Vector2::Subtract(
                x,
                Vector2::Scale(
                    Vector2::Floor(
                        Vector2::Multiply(x, Vector2::Make(1.0F / 289.0F))
                    ),
                    289.0F
                )
            );
        }
        mathinline static Vector3 mathcall mod289(Vector3 x) noexcept
        {
            return Vector3::Subtract(Vector3::Make(x), Vector3::Scale(Vector3::Floor(x * Vector3::Make(1.0F / 289.0F)), 289.0F);
        }
        mathinline static Vector4 mathcall mod289(Vector4 x) noexcept
        {
            return Vector4::Scale(Vector4::Floor(x * Vector4::Make(1.0F / 289.0F)), 289.0F);
        }

        mathinline static Vector3 mathcall mod7(Vector3 x) noexcept
        {
            return x 
        }

            // Modulo 7 without a division
            static Float3A mod7(Float3A x)
            {
                return x - math.floor(x * (1.0f / 7.0f)) * 7.0f;
            }
            static Float4A mod7(Float4A x)
            {
                return x - math.floor(x * (1.0f / 7.0f)) * 7.0f;
            }

            // Permutation polynomial: (34x^2 + x) math.mod 289
            static float  permute(float x)
            {
                return mod289((34.0f * x + 1.0f) * x);
            }
            static Float3A permute(Float3A x)
            {
                return mod289((34.0f * x + 1.0f) * x);
            }
            static Float4A permute(Float4A x)
            {
                return mod289((34.0f * x + 1.0f) * x);
            }

            static float  taylorInvSqrt(float r)
            {
                return 1.79284291400159f - 0.85373472095314f * r;
            }
            static Float4A taylorInvSqrt(Float4A r)
            {
                return 1.79284291400159f - 0.85373472095314f * r;
            }

            static Float2A fade(Float2A t)
            {
                return t * t*t*(t*(t*6.0f - 15.0f) + 10.0f);
            }
            static Float3A fade(Float3A t)
            {
                return t * t*t*(t*(t*6.0f - 15.0f) + 10.0f);
            }
            static Float4A fade(Float4A t)
            {
                return t * t*t*(t*(t*6.0f - 15.0f) + 10.0f);
            }

            static Float4A grad4(float j, Float4A ip)
            {
                Float4A ones = new Float4A(1.0f, 1.0f, 1.0f, -1.0f);
                Float3A pxyz = math.floor(math.fract(new Float3A(j) * ip.xyz) * 7.0f) * ip.z - 1.0f;
                float  pw = 1.5f - math.dot(math.abs(pxyz), ones.xyz);
                Float4A p = new Float4A(pxyz, pw);
                Float4A s = new Float4A(math.lessThan(p, new Float4A(0.0f)));
                p.xyz = p.xyz + (s.xyz*2.0f - 1.0f) * s.www;
                return p;
            }

            // Hashed 2-D gradients with an extra rotation.
            // (The constant 0.0243902439 is 1/41)
            static Float2A rgrad2(Float2A p, float rot)
            {
                // For more isotropic gradients, math.sin/math.cos can be used instead.
                float u = permute(permute(p.x) + p.y) * 0.0243902439f + rot; // Rotate by shift
                u = math.fract(u) * 6.28318530718f; // 2*pi
                return new Float2A(math.cos(u), math.sin(u));
            }
        }
    };
#endif
