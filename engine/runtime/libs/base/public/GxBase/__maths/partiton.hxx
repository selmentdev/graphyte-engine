namespace Graphyte::Maths::Impl
{
    mathinline NativeFloat32x4 mathcall ConvertIntToFloat(NativeFloat32x4 vint, uint32_t exponent) noexcept
    mathinline NativeFloat32x4 mathcall ConvertFloatToInt(NativeFloat32x4 vfloat, uint32_t exponent) noexcept
    mathinline NativeFloat32x4 mathcall ConvertUIntToFloat(NativeFloat32x4 vuint, uint32_t exponent) noexcept
    mathinline NativeFloat32x4 mathcall ConvertFloatToUInt(NativeFloat32x4 vfloat, uint32_t exponent)
    mathinline NativeFloat32x4 mathcall SplatConstant(int32_t c, uint32_t exponent) noexcept
    mathinline NativeFloat32x4 mathcall SplatConstant(int32_t c) noexcept
}

// Select control mask
namespace Graphyte::Maths
{
    mathinline Bool4 mathcall SelectControl(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    mathinline Vector4 mathcall Select(Vector4 a, Vector4 b, Bool4 control) noexcept
    mathinline float mathcall Select(float a, float b, float control) noexcept
}

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Permute(Vector4 a, Vector4 b, uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline Vector4 mathcall Permute(Vector4 a, Vector4 b) noexcept
}

// Swizzling
namespace Graphyte::Maths
{
    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline Vector4 mathcall Swizzle(Vector4 v) noexcept
    template <size_t X, size_t Y, size_t Z>
    mathinline Vector3 mathcall Swizzle(Vector3 v) noexcept
    template <size_t X, size_t Y>
    mathinline Vector2 mathcall Swizzle(Vector2 v) noexcept
    template <SwizzleMask M>
    mathinline Vector4 mathcall Swizzle(Vector4 v) noexcept
    mathinline Vector4 mathcall Swizzle(Vector4 v, uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    mathinline Vector4 mathcall MergeXY(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall MergeZW(Vector4 a, Vector4 b) noexcept
    template <uint32_t Count>
    mathinline Vector4 mathcall ShiftLeft(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall ShiftLeft(Vector4 a, Vector4 b, uint32_t count) noexcept
    template <uint32_t Count>
    mathinline Vector4 mathcall RotateLeft(Vector4 v) noexcept
    mathinline Vector4 mathcall RotateLeft(Vector4 v, uint32_t count) noexcept
    template <uint32_t Count>
    mathinline Vector4 mathcall RotateRight(Vector4 v) noexcept
    mathinline Vector4 mathcall RotateRight(Vector4 v, uint32_t count) noexcept
    mathinline Vector4 mathcall SumComponents(Vector4 v) noexcept
}

// Vector insertion
namespace Graphyte::Maths
{
    template <bool X, bool Y, bool Z, bool W>
    mathinline Vector4 mathcall Insert(Vector4 a, Vector4 b) noexcept
    template <InsertMask Mask>
    mathinline Vector4 mathcall Insert(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall Insert(Vector4 a, Vector4 b, bool x, bool y, bool z, bool w) noexcept
    mathinline Vector4 mathcall Insert(Vector4 a, Vector4 b, uint32_t rotate_left_count, bool x, bool y, bool z, bool w) noexcept
}

// Type conversion operations
namespace Graphyte::Maths
{
    mathinline Vector4 mathcall To(float x, Vector3 yzw) noexcept
    mathinline Vector4 mathcall To(Vector3 xyz, float w) noexcept
    mathinline Vector4 mathcall To(float x, float y, Vector2 zw) noexcept
    mathinline Vector4 mathcall To(float x, Vector2 yz, float w) noexcept
    mathinline Vector4 mathcall To(Vector2 xy, float z, float w) noexcept
    mathinline Vector4 mathcall To(Vector2 xy, Vector2 zw) noexcept
    mathinline Vector3 mathcall To(float x, Vector2 yz) noexcept
    mathinline Vector3 mathcall To(Vector2 xy, float z) noexcept
}

// =================================================================================================
//
// Load / store operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Load<Vector4, Float4A>(Float4A const* source) noexcept
    mathinline void mathcall Store<Float4A, Vector4>(Float4A* destination, Vector4 v) noexcept
    mathinline Vector4 mathcall Load<Vector4, Float4>(Float4 const* source) noexcept
    mathinline void mathcall Store<Float4, Vector4>(Float4* destination, Vector4 v) noexcept
    mathinline Vector4 mathcall Load<Vector4, Float3A>(Float3A const* source) noexcept
    mathinline void mathcall Store<Float3A, Vector4>(Float3A* destination, Vector4 v) noexcept
    mathinline Vector4 mathcall Load<Vector4, Float3>(Float3 const* source) noexcept
    mathinline void mathcall Store<Float3, Vector4>(Float3* destination, Vector4 v) noexcept
    mathinline Vector4 mathcall Load<Vector4, Float2A>(Float2A const* source) noexcept
    mathinline void mathcall Store<Float2A, Vector4>(Float2A* destination, Vector4 v) noexcept
    mathinline Vector4 mathcall Load<Vector4, Float2>(Float2 const* source) noexcept
    mathinline void mathcall Store<Float2, Vector4>(Float2* destination, Vector4 v) noexcept
    mathinline Vector4 mathcall Load<Vector4, float>(float const* source) noexcept
    mathinline void mathcall Store<float, Vector4>(float* destination, Vector4 v) noexcept
}

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Load<Vector4, Half4>(Half4 const* source) noexcept
    mathinline void mathcall Store<Half4, Vector4>(Half4* destination, Vector4 v) noexcept
    mathinline Vector4 mathcall Load<Vector4, Half2>(Half2 const* source) noexcept
    mathinline void mathcall Store<Half2, Vector4>(Half2* destination, Vector4 v) noexcept
}

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall SplatX<Vector4>(Vector4 v) noexcept
    mathinline Vector4 mathcall SplatY<Vector4>(Vector4 v) noexcept
    mathinline Vector4 mathcall SplatZ<Vector4>(Vector4 v) noexcept
    mathinline Vector4 mathcall SplatW<Vector4>(Vector4 v) noexcept
    mathinline float mathcall GetByIndex(Vector4 v, size_t index) noexcept
    mathinline Vector4 mathcall SetByIndex(Vector4 v, float value, size_t index) noexcept
    mathinline void mathcall GetByIndex(float* result, Vector4 v, size_t index) noexcept
    mathinline Vector4 mathcall SetByIndex(Vector4 v, float const* value, size_t index)
    mathinline float mathcall GetX(Vector4 v) noexcept
    mathinline float mathcall GetY(Vector4 v) noexcept
    mathinline float mathcall GetZ(Vector4 v) noexcept
    mathinline float mathcall GetW(Vector4 v) noexcept
    mathinline void mathcall GetX(float* result, Vector4 v) noexcept
    mathinline void mathcall GetY(float* result, Vector4 v) noexcept
    mathinline void mathcall GetZ(float* result, Vector4 v) noexcept
    mathinline void mathcall GetW(float* result, Vector4 v) noexcept
    mathinline Vector4 mathcall SetX(Vector4 v, float value) noexcept
    mathinline Vector4 mathcall SetY(Vector4 v, float value) noexcept
    mathinline Vector4 mathcall SetZ(Vector4 v, float value) noexcept
    mathinline Vector4 mathcall SetW(Vector4 v, float value) noexcept
    mathinline Vector4 mathcall SetX(Vector4 v, float const* value) noexcept
    mathinline Vector4 mathcall SetY(Vector4 v, float const* value) noexcept
    mathinline Vector4 mathcall SetZ(Vector4 v, float const* value) noexcept
    mathinline Vector4 mathcall SetW(Vector4 v, float const* value) noexcept
}

// Getters and setters for bitwisable vectors
namespace Graphyte::Maths
{
    mathinline uint32_t mathcall GetByIndex(Bool4 v, size_t index) noexcept
    mathinline Bool4 mathcall SetUIntByIndex(Bool4 v, uint32_t value, size_t index) noexcept
    mathinline void mathcall GetUIntByIndex(uint32_t* result, Bool4 v, size_t index) noexcept
    mathinline Bool4 mathcall SetUIntByIndex(Bool4 v, uint32_t const* value, size_t index) noexcept
    mathinline uint32_t mathcall GetX(Bool4 v) noexcept
    mathinline uint32_t mathcall GetY(Bool4 v) noexcept
    mathinline uint32_t mathcall GetZ(Bool4 v) noexcept
    mathinline uint32_t mathcall GetW(Bool4 v) noexcept
    mathinline void mathcall GetX(uint32_t* result, Bool4 v) noexcept
    mathinline void mathcall GetY(uint32_t* result, Bool4 v) noexcept
    mathinline void mathcall GetZ(uint32_t* result, Bool4 v) noexcept
    mathinline void mathcall GetW(uint32_t* result, Bool4 v) noexcept
    mathinline Bool4 mathcall SetX(Bool4 v, uint32_t value) noexcept
    mathinline Bool4 mathcall SetY(Bool4 v, uint32_t value) noexcept
    mathinline Bool4 mathcall SetZ(Bool4 v, uint32_t value) noexcept
    mathinline Bool4 mathcall SetW(Bool4 v, uint32_t value) noexcept
    mathinline Bool4 mathcall SetX(Bool4 v, uint32_t const* value) noexcept
    mathinline Bool4 mathcall SetY(Bool4 v, uint32_t const* value) noexcept
    mathinline Bool4 mathcall SetZ(Bool4 v, uint32_t const* value) noexcept
    mathinline Bool4 mathcall SetW(Bool4 v, uint32_t const* value) noexcept
}

// =================================================================================================
//
// Constants
//

namespace Graphyte::Maths
{
    T UnitX() noexcept = delete;
    T UnitY() noexcept = delete;
    T UnitZ() noexcept = delete;
    T UnitW() noexcept = delete;
    T NegativeUnitX() noexcept = delete;
    T NegativeUnitY() noexcept = delete;
    T NegativeUnitZ() noexcept = delete;
    T NegativeUnitW() noexcept = delete;
    T Zero() noexcept = delete;
    T Identity() noexcept = delete;
    T One() noexcept = delete;
    T Infinity() noexcept = delete;
    T Nan() noexcept = delete;
    T Epsilon() noexcept = delete;
    T SignMask() noexcept = delete;
}

// Constructors
namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Make<Vector4, float>(float x, float y, float z, float w) noexcept
    mathinline Vector3 mathcall Make<Vector3, float>(float x, float y, float z) noexcept
    mathinline Vector2 mathcall Make<Vector2, float>(float x, float y) noexcept
    mathinline Vector1 mathcall Make<Vector1, float>(float x) noexcept
    mathinline Vector4 mathcall Replicate<Vector4, float>(float value) noexcept
    mathinline Vector4 mathcall Replicate<Vector4, float const*>(float const* source) noexcept
    mathinline Bool4 mathcall Make<Bool4, uint32_t>(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    mathinline Bool4 mathcall Replicate<Bool4, uint32_t>(uint32_t value) noexcept
    mathinline Bool4 mathcall Replicate<Bool4, uint32_t const*>(uint32_t const* source) noexcept
}

// Boolean operations
namespace Graphyte::Maths
{
    T True() noexcept = delete;
    T False() noexcept = delete;
    mathinline Bool4 mathcall And(Bool4 a, Bool4 b) noexcept
    mathinline Bool4 mathcall AndNot(Bool4 a, Bool4 b) noexcept
    mathinline Bool4 mathcall Or(Bool4 a, Bool4 b) noexcept
    mathinline Bool4 mathcall Xor(Bool4 a, Bool4 b) noexcept
    mathinline Bool4 mathcall Nor(Bool4 a, Bool4 b) noexcept
    mathinline Bool4 mathcall Not(Bool4 v) noexcept
}

// Boolean type comparison
namespace Graphyte::Maths
{
    mathinline Bool4 mathcall CompareEqual(Bool4 a, Bool4 b) noexcept
    mathinline Bool4 mathcall CompareNotEqual(Bool4 a, Bool4 b) noexcept
    mathinline bool mathcall IsEqual(Bool4 a, Bool4 b) noexcept
    mathinline bool mathcall IsEqual(Bool3 a, Bool3 b) noexcept
    mathinline bool mathcall IsEqual(Bool2 a, Bool2 b) noexcept
    mathinline bool mathcall IsEqual(Bool1 a, Bool1 b) noexcept
    mathinline bool mathcall IsNotEqual(Bool4 a, Bool4 b) noexcept
    mathinline bool mathcall IsNotEqual(Bool3 a, Bool3 b) noexcept
    mathinline bool mathcall IsNotEqual(Bool2 a, Bool2 b) noexcept
    mathinline bool mathcall IsNotEqual(Bool1 a, Bool1 b) noexcept
}

// Boolean mask qualification
namespace Graphyte::Maths
{
    mathinline bool mathcall AllTrue(Bool4 v) noexcept
    mathinline bool mathcall AllTrue(Bool3 v) noexcept
    mathinline bool mathcall AllTrue(Bool2 v) noexcept
    mathinline bool mathcall AllTrue(Bool1 v) noexcept
    mathinline bool mathcall AllFalse(Bool4 v) noexcept
    mathinline bool mathcall AllFalse(Bool3 v) noexcept
    mathinline bool mathcall AllFalse(Bool2 v) noexcept
    mathinline bool mathcall AllFalse(Bool1 v) noexcept
    mathinline bool mathcall AnyTrue(Bool4 v) noexcept
    mathinline bool mathcall AnyTrue(Bool3 v) noexcept
    mathinline bool mathcall AnyTrue(Bool2 v) noexcept
    mathinline bool mathcall AnyTrue(Bool1 v) noexcept
    mathinline bool mathcall AnyFalse(Bool4 v) noexcept
    mathinline bool mathcall AnyFalse(Bool3 v) noexcept
    mathinline bool mathcall AnyFalse(Bool2 v) noexcept
    mathinline bool mathcall AnyFalse(Bool1 v) noexcept
}


// =================================================================================================
//
// Componentwise functions
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Cos(Vector4 v) noexcept
    mathinline float mathcall Cos(float v) noexcept
    mathinline Vector4 mathcall Sin(Vector4 v) noexcept
    mathinline float mathcall Sin(float v) noexcept
    mathinline void mathcall SinCos(Vector4& result_sin, Vector4& result_cos, Vector4 v) noexcept
    mathinline void mathcall SinCos(float& result_sin, float& result_cos, float v) noexcept
    mathinline Vector4 mathcall Tan(Vector4 v) noexcept
    mathinline float mathcall Tan(float v) noexcept
    mathinline Vector4 mathcall Asin(Vector4 v) noexcept
    mathinline float mathcall Asin(float v) noexcept
    mathinline Vector4 mathcall Acos(Vector4 v) noexcept
    mathinline float mathcall Acos(float v) noexcept
    mathinline Vector4 mathcall Atan(Vector4 v) noexcept
    mathinline float mathcall Atan(float v) noexcept
    mathinline Vector4 mathcall Atan2(Vector4 y, Vector4 x) noexcept
    mathinline float mathcall Atan2(float y, float x) noexcept
    mathinline Vector4 mathcall Sinh(Vector4 v) noexcept
    mathinline float mathcall Sinh(float v) noexcept
    mathinline Vector4 mathcall Cosh(Vector4 v) noexcept
    mathinline Vector3 mathcall Cosh(Vector3 v) noexcept
    mathinline float mathcall Cosh(float v) noexcept
    mathinline Vector4 mathcall Tanh(Vector4 v) noexcept
    mathinline float mathcall Tanh(float v) noexcept
    mathinline Vector4 mathcall Asinh(Vector4 v) noexcept
    mathinline float mathcall Asinh(float v) noexcept
    mathinline Vector4 mathcall Acosh(Vector4 v) noexcept
    mathinline float mathcall Acosh(float v) noexcept
    mathinline Vector4 mathcall Atanh(Vector4 v) noexcept
    mathinline float mathcall Atanh(float v) noexcept
    mathinline Vector4 mathcall Log(Vector4 v) noexcept
    mathinline float mathcall Log(float v) noexcept
    mathinline Vector4 mathcall Log(Vector4 base, Vector4 value) noexcept
    mathinline float mathcall Log(float base, float value) noexcept
    mathinline Vector4 mathcall Log10(Vector4 v) noexcept
    mathinline float mathcall Log10(float v) noexcept
    mathinline Vector4 mathcall Log2(Vector4 v) noexcept
    mathinline float mathcall Log2(float v) noexcept
    mathinline Vector4 mathcall Exp(Vector4 v) noexcept
    mathinline float mathcall Exp(float v) noexcept
    mathinline Vector4 mathcall Exp10(Vector4 v) noexcept
    mathinline float mathcall Exp10(float v) noexcept
    mathinline Vector4 mathcall Exp2(Vector4 v) noexcept
    mathinline float mathcall Exp2(float v) noexcept
    mathinline Vector4 mathcall Power(Vector4 x, Vector4 y) noexcept
    mathinline float mathcall Power(float x, float y) noexcept
    mathinline Vector4 mathcall Hypot(Vector4 x, Vector4 y) noexcept
    mathinline float mathcall Hypot(float x, float y) noexcept
    mathinline Vector4 mathcall Sqrt(Vector4 v) noexcept
    mathinline float mathcall Sqrt(float v) noexcept
    mathinline Vector4 mathcall SqrtEst(Vector4 v) noexcept
    mathinline float mathcall SqrtEst(float v) noexcept
    mathinline Vector4 mathcall InvSqrt(Vector4 v) noexcept
    mathinline float mathcall InvSqrt(float v) noexcept
    mathinline Vector4 mathcall InvSqrtEst(Vector4 v) noexcept
    mathinline float mathcall InvSqrtEst(float v) noexcept
    mathinline Vector4 mathcall Cbrt(Vector4 v) noexcept
    mathinline float mathcall Cbrt(float v) noexcept
    mathinline Vector4 mathcall InvCbrt(Vector4 v) noexcept
    mathinline float mathcall InvCbrt(float v) noexcept
    mathinline Vector4 mathcall Abs(Vector4 v) noexcept
    mathinline float mathcall Abs(float v) noexcept
    mathinline Vector4 mathcall Negate(Vector4 v) noexcept
    mathinline float mathcall Negate(float v) noexcept
    mathinline Vector4 mathcall Add(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall Subtract(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall Multiply(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall Multiply(Vector4 a, float b) noexcept
    mathinline Vector4 mathcall Reciprocal(Vector4 v) noexcept
    mathinline float mathcall Reciprocal(float v) noexcept
    mathinline Vector4 mathcall Divide(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall Divide(Vector4 a, float b) noexcept
    mathinline Vector4 mathcall MultiplyAdd(Vector4 a, Vector4 b, Vector4 c) noexcept
    mathinline float mathcall MultiplyAdd(float a, float b, float c) noexcept
    mathinline Vector4 mathcall MultiplySubtract(Vector4 a, Vector4 b, Vector4 c) noexcept
    mathinline float mathcall MultiplySubtract(float a, float b, float c) noexcept
    mathinline Vector4 mathcall NegateMultiplyAdd(Vector4 a, Vector4 b, Vector4 c) noexcept
    mathinline float mathcall NegateMultiplyAdd(float a, float b, float c) noexcept
    mathinline Vector4 mathcall NegateMultiplySubtract(Vector4 a, Vector4 b, Vector4 c) noexcept
    mathinline float mathcall NegateMultiplySubtract(float a, float b, float c) noexcept
    mathinline Vector4 mathcall Square(Vector4 v) noexcept
    mathinline float mathcall Square(float v) noexcept
    mathinline Vector4 mathcall SignedSquare(Vector4 v) noexcept
    mathinline float mathcall SignedSquare(float v) noexcept
    mathinline Vector4 mathcall Cube(Vector4 v) noexcept
    mathinline float mathcall Cube(float v) noexcept
}

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Lerp(Vector4 a, Vector4 b, float t) noexcept
    mathinline Vector4 mathcall Lerp(Vector4 a, Vector4 b, Vector4 t) noexcept
    mathinline float mathcall Lerp(float a, float b, float t) noexcept
    mathinline float mathcall LerpPrecise(float a, float b, float t) noexcept
    mathinline Vector4 mathcall Hermite(Vector4 position0, Vector4 tangent0, Vector4 position1, Vector4 tangent1, float t) noexcept
    mathinline Vector4 mathcall Hermite(Vector4 position0, Vector4 tangent0, Vector4 position1, Vector4 tangent1, Vector4 t) noexcept
    mathinline float mathcall Hermite(float position0, float tangent0, float position1, float tangent1, float t) noexcept
    mathinline Vector4 mathcall Barycentric(Vector4 a, Vector4 b, Vector4 c, float f, float g) noexcept
    mathinline float mathcall Barycentric(float a, float b, float c, float f, float g) noexcept
    mathinline Vector4 mathcall Barycentric(Vector4 a, Vector4 b, Vector4 c, Vector4 f, Vector4 g) noexcept
    mathinline Vector4 mathcall CatmullRom(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3, float t) noexcept
    mathinline Vector4 mathcall CatmullRom(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3, Vector4 t) noexcept
    mathinline float mathcall CatmullRom(float p0, float p1, float p2, float p3, float t) noexcept
    mathinline Vector4 mathcall Remap(Vector4 value, Vector4 from_min, Vector4 from_max, Vector4 to_min, Vector4 to_max) noexcept
    mathinline float mathcall Remap(float value, float from_min, float from_max, float to_min, float to_max) noexcept
    mathinline Vector4 mathcall Unlerp(Vector4 value, Vector4 min, Vector4 max) noexcept
    mathinline float mathcall Unlerp(float value, float min, float max) noexcept
    mathinline float mathcall Bezier(float a, float b, float c, float t) noexcept
    mathinline float mathcall Bezier(float a, float b, float c, float d, float t) noexcept
    
    mathinline Vector4 mathcall MoveTowards(Vector4 current, Vector4 target, float max_distance) noexcept
    mathinline Vector3 mathcall MoveTowards(Vector3 current, Vector3 target, float max_distance) noexcept
    mathinline Vector2 mathcall MoveTowards(Vector2 current, Vector2 target, float max_distance) noexcept
    mathinline float mathcall MoveTowards(float current, float target, float max_distance) noexcept
    
    mathinline Vector4 mathcall Smoothstep(Vector4 a, Vector4 b, Vector4 x) noexcept
    mathinline Vector4 mathcall Smoothstep(Vector4 a, Vector4 b, float x) noexcept
    mathinline float mathcall Smoothstep(float a, float b, float x) noexcept
    mathinline float mathcall Cosine(float a, float b, float t) noexcept
    mathinline float mathcall EaseSmoothC2(float x) noexcept
    mathinline float mathcall Smooth(float min, float max, float x) noexcept
    mathinline float mathcall SmoothSquared(float min, float max, float x) noexcept
    mathinline float mathcall SmoothInvSquared(float min, float max, float x) noexcept
    mathinline float mathcall SmoothCubed(float min, float max, float x) noexcept
    mathinline float mathcall SmoothInvCubed(float min, float max, float x) noexcept
    mathinline float mathcall Trapezoid(float a, float b, float c, float d, float t) noexcept
    mathinline float mathcall Trapezoid(float a, float b, float c, float d, float t, float min, float max) noexcept
}


// =================================================================================================
// Common functions?

namespace Graphyte::Maths::Impl
{
    mathinline float RoundToNearest(float value) noexcept
}

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall CopySign(Vector4 number, Vector4 sign) noexcept
    mathinline float mathcall CopySign(float number, float sign) noexcept
    mathinline Vector4 mathcall Sign(Vector4 x) noexcept
    mathinline float mathcall Sign(float val)
    mathinline Vector4 mathcall Ceiling(Vector4 v) noexcept
    mathinline float mathcall Ceiling(float value) noexcept
    mathinline Vector4 mathcall Floor(Vector4 v) noexcept
    mathinline float mathcall Floor(float value) noexcept
    mathinline Vector4 mathcall Truncate(Vector4 v) noexcept
    mathinline float mathcall Truncate(float value) noexcept
    mathinline Vector4 mathcall Round(Vector4 v) noexcept
    mathinline float mathcall Round(float value) noexcept
    mathinline Vector4 mathcall Remainder(Vector4 x, Vector4 y) noexcept
    mathinline float mathcall Remainder(float x, float y) noexcept
    mathinline Vector4 mathcall Fraction(Vector4 x) noexcept
    mathinline float mathcall Fraction(float x) noexcept

    mathinline float mathcall Gain(float value, float gain) noexcept
    mathinline float mathcall Bias(float value, float base) noexcept
    mathinline float mathcall Step(float value1, float value2) noexcept
    mathinline int mathcall QuadricEquation(float a, float b, float c, float& out_x1, float& out_x2) noexcept
    mathinline float mathcall SnapToGrid(float value, float grid_size) noexcept
    mathinline float mathcall WangHashNoise(uint32_t u, uint32_t v, uint32_t s) noexcept
    mathinline float mathcall WrapAngle(float value) noexcept
    mathinline float mathcall DiffAngle(float angle1, float angle2) noexcept
    
    mathinline Vector4 mathcall FresnelTerm(Vector4 cos_incident_angle, Vector4 refraction_index) noexcept

    mathinline uint32_t mathcall FixedToFixed(uint32_t value, uint32_t n, uint32_t p) noexcept
    mathinline uint32_t mathcall FloatToFixed(float value, uint32_t bits) noexcept
    mathinline float mathcall FixedToFloat(uint32_t value, uint32_t bits) noexcept
}


// =================================================================================================
// Component-wise comparisons

namespace Graphyte::Maths
{
    mathinline Bool4 mathcall BitCompareEqual(Vector4 a, Vector4 b) noexcept
    mathinline Bool4 mathcall BitCompareNotEqual(Vector4 a, Vector4 b) noexcept
    mathinline Bool4 mathcall CompareEqual(Vector4 a, Vector4 b) noexcept
    mathinline Bool4 mathcall CompareEqual(Vector4 a, Vector4 b, Vector4 epsilon) noexcept
    mathinline Bool4 mathcall CompareNotEqual(Vector4 a, Vector4 b) noexcept
    mathinline Bool4 mathcall CompareGreater(Vector4 a, Vector4 b) noexcept
    mathinline Bool4 mathcall CompareGreaterEqual(Vector4 a, Vector4 b) noexcept
    mathinline Bool4 mathcall CompareLess(Vector4 a, Vector4 b) noexcept
    mathinline Bool4 mathcall CompareLessEqual(Vector4 a, Vector4 b) noexcept
    mathinline Bool4 mathcall CompareNan(Vector4 v) noexcept
    mathinline Bool4 mathcall CompareInfinite(Vector4 v) noexcept
    mathinline Bool4 mathcall CompareInBounds(Vector4 v, Vector4 bounds) noexcept
    mathinline bool mathcall IsZero(Vector4 v) noexcept
    mathinline bool mathcall IsZero(float v) noexcept
    mathinline bool mathcall IsZero(Vector4 v, Vector4 epsilon) noexcept
    mathinline bool mathcall IsZero(float v, float epsilon) noexcept
    mathinline bool mathcall IsEqual(Vector4 a, Vector4 b) noexcept
    mathinline bool mathcall IsEqual(float a, float b) noexcept
    mathinline bool mathcall IsEqual(Vector4 a, Vector4 b, Vector4 epsilon) noexcept
    mathinline bool mathcall IsEqual(float a, float b, float epsilon) noexcept
    mathinline bool mathcall IsNotEqual(Vector4 a, Vector4 b) noexcept
    mathinline bool mathcall IsNotEqual(float a, float b) noexcept
    mathinline bool mathcall IsGreater(Vector4 a, Vector4 b) noexcept
    mathinline bool mathcall IsGreater(float a, float b) noexcept
    mathinline bool mathcall IsGreaterEqual(Vector4 a, Vector4 b) noexcept
    mathinline bool mathcall IsGreaterEqual(float a, float b) noexcept
    mathinline bool mathcall IsLess(Vector4 a, Vector4 b) noexcept
    mathinline bool mathcall IsLess(float a, float b) noexcept
    mathinline bool mathcall IsLessEqual(Vector4 a, Vector4 b) noexcept
    mathinline bool mathcall IsLessEqual(float a, float b) noexcept
    mathinline bool InBounds(Vector4 v, Vector4 bounds) noexcept
    mathinline bool IsNan(Vector4 v) noexcept
    mathinline bool IsInfinity(Vector4 v) noexcept
    mathinline bool mathcall IsNearEqual(float a, float b, int32_t tolerance) noexcept
    mathinline bool mathcall IsNearEqual(float value1, float value2) noexcept
}

// =================================================================================================
// Component-wise operations

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Min(Vector4 a, Vector4 b) noexcept
    mathinline float mathcall Min(float a, float b) noexcept
    mathinline Vector4 mathcall Max(Vector4 a, Vector4 b) noexcept
    mathinline float mathcall Max(float a, float b) noexcept
    mathinline Vector4 mathcall Clamp(Vector4 v, Vector4 min, Vector4 max) noexcept
    mathinline float mathcall Clamp(float v, float min, float max) noexcept
    mathinline Vector4 mathcall Saturate(Vector4 v) noexcept
    mathinline float mathcall Saturate(float v) noexcept
    mathinline Vector4 mathcall Wrap(Vector4 v, Vector4 min, Vector4 max) noexcept
    mathinline float mathcall Wrap(float v, float min, float max) noexcept
    
    mathinline Vector4 mathcall Hmin(Vector4 v) noexcept
    mathinline Vector4 mathcall Hmax(Vector4 v) noexcept
    mathinline Vector4 mathcall Hsum(Vector4 v) noexcept
}

// Vector space operations
namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Dot(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall Dot(Vector3 a, Vector3 b) noexcept
    mathinline Vector4 mathcall Dot(Vector2 a, Vector2 b) noexcept
    mathinline float mathcall Dot(float a, float b) noexcept
    mathinline Vector4 mathcall LengthSquared(Vector4 v) noexcept
    mathinline Vector4 mathcall LengthSquared(Vector3 v) noexcept
    mathinline Vector4 mathcall LengthSquared(Vector2 v) noexcept
    mathinline float mathcall LengthSquared(float v) noexcept
    mathinline Vector4 mathcall Length(Vector4 v) noexcept
    mathinline Vector4 mathcall Length(Vector3 v) noexcept
    mathinline Vector4 mathcall Length(Vector2 v) noexcept
    mathinline Vector4 mathcall Length(Quaternion q) noexcept
    mathinline Vector4 mathcall LengthEst(Vector4 v) noexcept
    mathinline Vector4 mathcall LengthEst(Vector3 v) noexcept
    mathinline Vector4 mathcall LengthEst(Vector2 v) noexcept
    mathinline Vector4 mathcall ReciprocalLength(Vector4 v) noexcept
    mathinline Vector4 mathcall ReciprocalLength(Vector3 v) noexcept
    mathinline Vector4 mathcall ReciprocalLength(Vector2 v) noexcept
    mathinline Vector4 mathcall ReciprocalLengthEst(Vector4 v) noexcept
    mathinline Vector4 mathcall ReciprocalLengthEst(Vector3 v) noexcept
    mathinline Vector4 mathcall ReciprocalLengthEst(Vector2 v) noexcept
    mathinline Vector4 mathcall Distance(Vector4 a, Vector4 b) noexcept
    mathinline Vector3 mathcall Distance(Vector3 a, Vector3 b) noexcept
    mathinline Vector2 mathcall Distance(Vector2 a, Vector2 b) noexcept
    mathinline float mathcall Distance(float a, float b) noexcept
    mathinline Vector4 mathcall DistanceSquared(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall DistanceSquared(Vector3 a, Vector3 b) noexcept
    mathinline Vector4 mathcall DistanceSquared(Vector2 a, Vector2 b) noexcept
    mathinline float mathcall DistanceSquared(float a, float b) noexcept
    mathinline bool mathcall IsUnit(Vector4 v) noexcept
    mathinline bool mathcall IsUnit(Vector3 v) noexcept
    mathinline bool mathcall IsUnit(Vector2 v) noexcept
    mathinline Vector4 mathcall Normalize(Vector4 v) noexcept
    mathinline Vector3 mathcall Normalize(Vector3 v) noexcept
    mathinline Vector2 mathcall Normalize(Vector2 v) noexcept
    mathinline Vector4 mathcall NormalizeEst(Vector4 v) noexcept
    mathinline Vector3 mathcall NormalizeEst(Vector3 v) noexcept
    mathinline Vector2 mathcall NormalizeEst(Vector2 v) noexcept
    mathinline Vector4 mathcall ClampLength(Vector4 v, Vector4 min, Vector4 max) noexcept
    mathinline Vector3 mathcall ClampLength(Vector3 v, Vector4 min, Vector4 max) noexcept
    mathinline Vector2 mathcall ClampLength(Vector2 v, Vector4 min, Vector4 max) noexcept
    mathinline Vector4 mathcall ClampLength(Vector4 v, float min, float max) noexcept
    mathinline Vector3 mathcall ClampLength(Vector3 v, float min, float max) noexcept
    mathinline Vector2 mathcall ClampLength(Vector2 v, float min, float max) noexcept
    mathinline Vector4 mathcall Reflect(Vector4 incident, Vector4 normal) noexcept
    mathinline Vector3 mathcall Reflect(Vector3 incident, Vector3 normal) noexcept
    mathinline Vector2 mathcall Reflect(Vector2 incident, Vector2 normal) noexcept
    mathinline Vector4 mathcall Refract(Vector4 incident, Vector4 normal, Vector4 index) noexcept
    mathinline Vector3 mathcall Refract(Vector3 incident, Vector3 normal, Vector4 index) noexcept
    mathinline Vector2 mathcall Refract(Vector2 incident, Vector2 normal, Vector4 index) noexcept
    mathinline Vector4 mathcall Refract(Vector4 incident, Vector4 normal, float index) noexcept
    mathinline Vector3 mathcall Refract(Vector3 incident, Vector3 normal, float index) noexcept
    mathinline Vector2 mathcall Refract(Vector2 incident, Vector2 normal, float index) noexcept
    mathinline Vector3 mathcall FaceForward(Vector3 normal, Vector3 incident, Vector3 reference) noexcept
    mathinline Vector2 mathcall FaceForward(Vector2 normal, Vector2 incident, Vector2 reference) noexcept
    mathinline Vector4 mathcall AngleBetweenNormals(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall AngleBetweenNormals(Vector3 a, Vector3 b) noexcept
    mathinline Vector4 mathcall AngleBetweenNormals(Vector2 a, Vector2 b) noexcept
    mathinline Vector4 mathcall AngleBetweenVectors(Vector4 a, Vector4 b) noexcept
    mathinline Vector4 mathcall AngleBetweenVectors(Vector3 a, Vector3 b) noexcept
    mathinline Vector4 mathcall AngleBetweenVectors(Vector2 a, Vector2 b) noexcept
}

// Vector4 operations
namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Cross(Vector4 a, Vector4 b, Vector4 c) noexcept
    mathinline Vector4 mathcall Orthogonal(Vector4 v) noexcept
    mathinline Vector4 mathcall Transform(Vector4 v, Matrix m) noexcept
}

// Vector3 operations
namespace Graphyte::Maths
{
    mathinline Vector3 mathcall Cross(Vector3 a, Vector3 b) noexcept
    mathinline Vector3 mathcall Orthogonal(Vector3 v) noexcept
    mathinline void mathcall ComponentsFromNormal(Vector3& out_parallel, Vector3& out_perpendicular, Vector3 v, Vector3 n) noexcept
    mathinline Vector3 mathcall Transform(Vector3 v, Matrix m) noexcept
    mathinline Vector3 mathcall TransformCoord(Vector3 v, Matrix m) noexcept
    mathinline Vector3 mathcall TransformNormal(Vector3 v, Matrix m) noexcept
}

// Vector2 operations
namespace Graphyte::Maths
{
    mathinline Vector2 mathcall Cross(Vector2 a, Vector2 b) noexcept
    mathinline Vector2 mathcall Orthogonal(Vector2 v) noexcept
    mathinline Vector2 mathcall Transform(Vector2 v, Matrix m) noexcept
    mathinline Vector2 mathcall TransformCoord(Vector2 v, Matrix m) noexcept
    mathinline Vector2 mathcall TransformNormal(Vector2 v, Matrix m) noexcept
}

// Create rotation from axis/angle or normal/angle / euler angles
namespace Graphyte::Maths
{
    template <typename T> T CreateFromAxisAngle(Vector3 axis, float angle) noexcept = delete;
    template <typename T> T CreateFromNormalAngle(Vector3 normal, float angle) noexcept = delete;
    template <typename T> T CreateFromEuler(Vector3 angles) noexcept = delete;
    template <typename T> T CreateFromEuler(float x, float y, float z) noexcept = delete;
}

// Quaternion operations
namespace Graphyte::Maths
{
    template <> mathinline Quaternion mathcall Identity<Quaternion>() noexcept
    mathinline bool mathcall IsIdentity(Quaternion v) noexcept
    mathinline bool mathcall IsIdentity(Quaternion v, Vector4 epsilon) noexcept
    mathinline Quaternion mathcall Conjugate(Quaternion q) noexcept
    mathinline Quaternion Inverse(Quaternion q) noexcept
    mathinline Quaternion mathcall Multiply(Quaternion q1, Quaternion q2) noexcept
    mathinline Quaternion mathcall Multiply(Quaternion q, Vector4 v) noexcept
    mathinline Quaternion mathcall Divide(Quaternion q, Vector4 v) noexcept
    mathinline Quaternion mathcall Exp(Quaternion q) noexcept
    mathinline Quaternion mathcall Log(Quaternion q) noexcept
    template <> mathinline Quaternion mathcall CreateFromEuler<Quaternion>(Vector3 angles) noexcept
    template <> mathinline Quaternion mathcall CreateFromEuler<Quaternion>(float x, float y, float z) noexcept
    template <> mathinline Quaternion mathcall CreateFromNormalAngle<Quaternion>(Vector3 normal, float angle) noexcept
    mathinline Quaternion mathcall CreateFromMatrix(Matrix m) noexcept
    template <> mathinline Quaternion mathcall CreateFromAxisAngle<Quaternion>(Vector3 axis, float angle) noexcept
    mathinline void mathcall ToAxisAngle(Vector3& axis, float& angle, Quaternion q) noexcept
    mathinline Vector3 Rotate(Vector3 v, Quaternion q) noexcept
    mathinline Vector3 InverseRotate(Vector3 v, Quaternion q) noexcept
}
// Matrix operations
namespace Graphyte::Maths
{
    mathinline Matrix mathcall Make(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33) noexcept
    template <> mathinline Matrix mathcall Load<Matrix, Float4x4A>(Float4x4A const* source) noexcept
    template <> mathinline void mathcall Store<Float4x4A, Matrix>(Float4x4A* destination, Matrix m) noexcept
    template <> mathinline Matrix mathcall Load<Matrix, Float4x3A>(Float4x3A const* source) noexcept
    template <> mathinline void mathcall Store<Float4x3A, Matrix>(Float4x3A* destination, Matrix m) noexcept
    template <> mathinline Matrix mathcall Load<Matrix, Float3x4A>(Float3x4A const* source) noexcept
    template <> mathinline void mathcall Store<Float3x4A, Matrix>(Float3x4A* destination, Matrix m) noexcept
    template <> mathinline Matrix mathcall Load<Matrix, Float4x4>(Float4x4 const* source) noexcept
    template <> mathinline void mathcall Store<Float4x4, Matrix>(Float4x4* destination, Matrix m) noexcept
    template <> mathinline Matrix mathcall Load<Matrix, Float4x3>(Float4x3 const* source) noexcept
    template <> mathinline void mathcall Store<Float4x3, Matrix>(Float4x3* destination, Matrix m) noexcept
    template <> mathinline Matrix mathcall Load<Matrix, Float3x4>(Float3x4 const* source) noexcept
    template <> mathinline void mathcall Store<Float3x4, Matrix>(Float3x4* destination, Matrix m) noexcept
    template <> mathinline Matrix mathcall Load<Matrix, Float3x3>(Float3x3 const* source) noexcept
    template <> mathinline void mathcall Store<Float3x3, Matrix>(Float3x3* destination, Matrix m) noexcept
    mathinline Matrix mathcall OuterProduct(Vector4 c, Vector4 r) noexcept
    mathinline Vector4 mathcall Diagonal(Matrix m) noexcept
    mathinline Vector4 mathcall Trace(Matrix m) noexcept
    mathinline Matrix mathcall Add(Matrix m1, Matrix m2) noexcept
    mathinline Matrix mathcall Subtract(Matrix m1, Matrix m2) noexcept
    mathinline Matrix mathcall Negate(Matrix m) noexcept
    mathinline Matrix mathcall Multiply(float s, Matrix m) noexcept
    mathinline Matrix mathcall Multiply(Matrix m, float s) noexcept
    mathinline Matrix mathcall Divide(Matrix m, float s) noexcept
    mathinline Matrix mathcall ComponentMultiply(Matrix a, Matrix b) noexcept
    mathinline Matrix mathcall Multiply(Matrix a, Matrix b) noexcept
    mathinline Matrix mathcall MultiplyTranspose(Matrix a, Matrix b) noexcept
    mathinline Matrix mathcall Transpose(Matrix m) noexcept
    mathinline Matrix mathcall Inverse(Matrix m, Vector4* determinant = nullptr) noexcept
    mathinline Vector4 mathcall Determinant(Matrix m) noexcept
    mathinline bool mathcall Decompose(
        Vector4& out_scale,
        Quaternion& out_rotation,
        Vector4& out_translation,
        Matrix m) noexcept
    template <> mathinline Matrix mathcall Nan<Matrix>() noexcept
    mathinline bool mathcall IsNan(Matrix m) noexcept
    mathinline Matrix mathcall Infinity<Matrix>() noexcept
    mathinline bool mathcall IsInfinity(Matrix m) noexcept
    template <> mathinline Matrix mathcall Identity<Matrix>() noexcept
    mathinline bool mathcall IsIdentity(Matrix m) noexcept
    mathinline Vector4 mathcall GetBaseX(Matrix m) noexcept
    mathinline Vector4 mathcall GetBaseY(Matrix m) noexcept
    mathinline Vector4 mathcall GetBaseZ(Matrix m) noexcept
    mathinline Vector4 mathcall GetBaseW(Matrix m) noexcept
    template <> mathinline Matrix mathcall CreateFromNormalAngle<Matrix>(Vector3 normal, float angle) noexcept
    template <> mathinline Matrix mathcall CreateFromAxisAngle<Matrix>(Vector3 axis, float angle) noexcept
    mathinline Matrix mathcall CreateFromQuaternion(Quaternion q) noexcept
    template <> mathinline Matrix mathcall CreateFromEuler<Matrix>(Vector3 angles) noexcept
    template <> mathinline Matrix mathcall CreateFromEuler<Matrix>(float x, float y, float z) noexcept

    mathinline Matrix mathcall CreateTranslation(float x, float y, float z) noexcept
    mathinline Matrix mathcall CreateTranslation(Vector3 translation) noexcept
    mathinline Matrix mathcall CreateScaling(float x, float y, float z) noexcept
    mathinline Matrix mathcall CreateScaling(Vector3 scale) noexcept
    mathinline Matrix mathcall CreateRotationX(float angle) noexcept
    mathinline Matrix mathcall CreateRotationY(float angle) noexcept
    mathinline Matrix mathcall CreateRotationZ(float angle) noexcept
    mathinline Matrix mathcall CreateTransform2D(
        Vector2 scaling_origin,
        float scaling_orientation,
        Vector2 scaling,
        Vector2 rotation_origin,
        float rotation,
        Vector2 translation) noexcept
    mathinline Matrix mathcall CreateAffineTransform2D(
        Vector2 scaling,
        Vector2 rotation_origin,
        float rotation,
        Vector2 translation) noexcept
    mathinline Matrix mathcall CreateTransform(
        Vector3 scaling_origin,
        Quaternion scaling_orientation,
        Vector3 scaling,
        Vector3 rotation_origin,
        Quaternion rotation,
        Vector3 translation) noexcept
    mathinline Matrix mathcall CreateAffineTransform(
        Vector3 scaling,
        Vector3 rotation_origin,
        Quaternion rotation,
        Vector3 translation) noexcept
    mathinline Matrix mathcall LookToLH(Vector3 eye_position, Vector3 eye_direction, Vector3 up_direction) noexcept
    mathinline Matrix mathcall LookToRH(Vector3 eye_position, Vector3 eye_direction, Vector3 up_direction) noexcept
    mathinline Matrix mathcall LookAtLH(Vector3 eye_position, Vector3 focus_position, Vector3 up_direction) noexcept
    mathinline Matrix mathcall LookAtRH(Vector3 eye_position, Vector3 focus_position, Vector3 up_direction) noexcept
    mathinline Matrix mathcall PerspectiveLH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
    mathinline Matrix mathcall PerspectiveRH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
    mathinline Matrix mathcall PerspectiveFovLH(
        float fov_angle_y,
        float aspect_ratio,
        float z_near,
        float z_far) noexcept
    mathinline Matrix mathcall PerspectiveFovRH(
        float fov_angle_y,
        float aspect_ratio,
        float z_near,
        float z_far) noexcept
    mathinline Matrix mathcall PerspectiveOffsetLH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far)
    mathinline Matrix mathcall PerspectiveOffsetRH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far)
    mathinline Matrix mathcall OrthographicLH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
    mathinline Matrix mathcall OrthographicRH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
    mathinline Matrix mathcall OrthographicOffsetLH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far) noexcept
    mathinline Matrix mathcall OrthographicOffsetRH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far) noexcept
// Color operations
namespace Graphyte::Maths
{
    mathinline Color mathcall Negative(Color v) noexcept
    mathinline Color mathcall Modulate(Color a, Color b) noexcept
    mathinline Color mathcall AdjustSaturation(Color v, float saturation) noexcept
    mathinline Color mathcall AdjustContrast(Color v, float contrast) noexcept
}

// Plane operations
namespace Graphyte::Maths
{
    mathinline Vector4 mathcall DotCoord(Plane p, Vector3 v) noexcept
    mathinline Vector4 mathcall DotNormal(Plane p, Vector3 n) noexcept
    mathinline Plane mathcall Normalize(Plane p) noexcept
    mathinline Plane mathcall NormalizeEst(Plane p) noexcept
    mathinline bool mathcall IsEqual(Plane p1, Plane p2, Vector4 epsilon) noexcept
    mathinline Plane mathcall Transform(Plane p, Matrix m) noexcept
    mathinline Plane mathcall CreateFromPointNormal(Vector3 point, Vector3 normal) noexcept
    mathinline Plane mathcall CreateFromPoints(Vector3 p1, Vector3 p2, Vector3 p3) noexcept
    mathinline Matrix mathcall Reflect(Plane reflection) noexcept
    mathinline Matrix mathcall Shadow(Plane shadow, Vector4 light) noexcept
}

// Intersections
namespace Graphyte::Maths
{
    mathinline Vector3 mathcall LinePlaneIntersection(Plane plane, Vector3 start, Vector3 end) noexcept
    mathinline void PlanePlaneIntersection(
        Vector3& out_line1,
        Vector3& out_line2,
        Plane plane1,
        Plane plane2) noexcept
    mathinline Vector2 mathcall LineLineIntersection(
        Vector2 line1_start,
        Vector2 line1_end,
        Vector2 line2_start,
        Vector2 line2_end) noexcept
    template <typename T>
    mathinline Vector4 mathcall LinePointDistance(T line1, T line2, T point) noexcept
}

// Degrees / Radians conversion
namespace Graphyte::Maths
{
    mathinline Vector4 mathcall RevolutionsToDegrees(Vector4 value) noexcept
    mathinline float mathcall RevolutionsToDegrees(float value) noexcept
    mathinline Vector4 mathcall RevolutionsToRadians(Vector4 value) noexcept
    mathinline float mathcall RevolutionsToRadians(float value) noexcept
    mathinline Vector4 mathcall RevolutionsToGradians(Vector4 value) noexcept
    mathinline float mathcall RevolutionsToGradians(float value) noexcept
    mathinline Vector4 mathcall DegreesToRevolutions(Vector4 value) noexcept
    mathinline float mathcall DegreesToRevolutions(float value) noexcept
    mathinline Vector4 mathcall RadiansToRevolutions(Vector4 value) noexcept
    mathinline float mathcall RadiansToRevolutions(float value) noexcept
    mathinline Vector4 mathcall GradiansToRevolutions(Vector4 value) noexcept
    mathinline float mathcall GradiansToRevolutions(float value) noexcept
    mathinline Vector4 mathcall RadiansToGradians(Vector4 value) noexcept
    mathinline float mathcall RadiansToGradians(float value) noexcept
    mathinline Vector4 mathcall GradiansToRadians(Vector4 value) noexcept
    mathinline float mathcall GradiansToRadians(float value) noexcept
    mathinline Vector4 mathcall RadiansToDegrees(Vector4 value) noexcept
    mathinline float mathcall RadiansToDegrees(float value) noexcept
    mathinline Vector4 mathcall DegreesToRadians(Vector4 value) noexcept
    mathinline float mathcall DegreesToRadians(float value) noexcept
    mathinline Vector4 mathcall GradiansToDegrees(Vector4 value) noexcept
    mathinline float mathcall GradiansToDegrees(float value) noexcept
    mathinline Vector4 mathcall DegreesToGradians(Vector4 value) noexcept
    mathinline float mathcall DegreesToGradians(float value) noexcept
}

// Coordinate systems
namespace Graphyte::Maths
{
    mathinline Float3A mathcall CartesianToSpherical(const Float3A& value) noexcept
    mathinline Float3A mathcall SphericalToCartesian(const Float3A& value) noexcept
    mathinline Float3A mathcall CartesianToCylindrical(const Float3A& value) noexcept
    mathinline Float3A mathcall CylindricalToCartesian(const Float3A& value) noexcept
    mathinline Float2A mathcall PolarToCartesian(const Float2A& value) noexcept
    mathinline Float2A mathcall CartesianToPolar(const Float2A& value) noexcept
}


// =================================================================================================
//
// Vector projection on viewport
//

namespace Graphyte::Maths
{
    // TODO: make Viewport struct instead of this
    mathinline Vector3 mathcall Project(
        Vector3 v,
        float viewport_x,
        float viewport_y,
        float viewport_width,
        float viewport_height,
        float viewport_min_z,
        float viewport_max_z,
        Matrix projection,
        Matrix view,
        Matrix world) noexcept
    mathinline Vector3 mathcall Unproject(
        Vector3 v,
        float viewport_x,
        float viewport_y,
        float viewport_width,
        float viewport_height,
        float viewport_min_z,
        float viewport_max_z,
        Matrix projection,
        Matrix view,
        Matrix world) noexcept
}


// =================================================================================================
//
// Load / Store for packed types
//

namespace Graphyte::Maths
{
    template <>
    mathinline Color mathcall Load<Color, ColorBGRA>(ColorBGRA const* source) noexcept
    template <>
    mathinline void mathcall Store<ColorBGRA, Color>(ColorBGRA* destination, Color color) noexcept
}


//==================================================================================================
//
// Unsequential algorithms
//

namespace Graphyte::Maths::Unsequential
{
    mathinline Vector4 mathcall Dot(
        Vector4 x1,
        Vector4 y1,
        Vector4 z1,
        Vector4 w1,
        Vector4 x2,
        Vector4 y2,
        Vector4 z2,
        Vector4 w2) noexcept
    {
        Vector4 const r0 = Multiply(x1, x2);
        Vector4 const r1 = MultiplyAdd(y1, y2, r0);
        Vector4 const r2 = MultiplyAdd(z1, z2, r1);
        Vector4 const r3 = MultiplyAdd(w1, w2, r2);
        return r3;
    }

    mathinline Vector4 mathcall Dot(
        Vector4 x1,
        Vector4 y1,
        Vector4 z1,
        Vector4 x2,
        Vector4 y2,
        Vector4 z2) noexcept
    {
        Vector4 const r0 = Multiply(x1, x2);
        Vector4 const r1 = MultiplyAdd(y1, y2, r0);
        Vector4 const r2 = MultiplyAdd(z1, z2, r1);
        return r2;
    }

    mathinline Vector4 mathcall Dot(
        Vector4 x1,
        Vector4 y1,
        Vector4 x2,
        Vector4 y2) noexcept
    {
        Vector4 const r0 = Multiply(x1, x2);
        Vector4 const r1 = MultiplyAdd(y1, y2, r0);
        return r1;
    }
}
