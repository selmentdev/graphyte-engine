#pragma once
#include <Graphyte/Geometry.module.hxx>
#include <Graphyte/Types.hxx>
#include <Graphyte/Maths.hxx>
#include <Graphyte/Geometry/Mesh.hxx>

namespace Graphyte::Geometry
{
    /**
     * @brief   This enum represents possible model part types.
     */
    enum class ModelPartType : uint32_t
    {
        None,       //!< Works as non-bone xform for other model parts.
        Mesh,       //!< Renderable mesh geometry.
        Hull,       //!< Physics hull / occlusion query proxy mesh.
        Bone,       //!< Bone xform.
        Helper,     //!< Helper mesh - for editor purposes only.
    };

    /**
     * @brief   This enum represents possible helper types.
     */
    enum class ModelHelperType : uint32_t
    {
        None,       //!< Model is not a helper.
        Point,      //!< Point rendered in editor.
        Mesh,       //!< Helper mesh geometry
    };

    /**
     * @brief   This enum represents possible model part flags.
     */
    enum class ModelPartFlags : uint32_t
    {
        None = 0,
    };
    GX_ENUM_CLASS_FLAGS(ModelPartFlags);

    /**
     * @brief   This struct represents part of loaded model.
     *
     * @note    Skeletal animation is provided in separate structure.
     *          Model part specifies just initial state of whole model (for humanoids, T-pose).
     */
    class GEOMETRY_API ModelPart final
    {
    public:
        ModelPart*      Parent;             //!< Pointer to parent model part.
        ModelPartType   Type;               //!< Model part type.
        ModelPartFlags  Flags;              //!< Additional flags.
        uint32_t        LodCount;           //!< Number of LOD levels. Serialized sequentially.
        uint32_t        ChildrenCount;      //!< Number of children model parts.
        Mesh*           MeshData;           //!< Pointer to actual mesh data.
        ModelHelperType HelperType;         //!< Model helper type.
        Float3   HelperSize;                //!< Model helper size.
        std::string     Name;               //!< Name of model part.
        Float4x3 LocalTransform;            //!< Local transform matrix.
        Float4x3 BoneTransform;             //!< Bone transform matrix.
    };

    /**
     * @brief   Represents 3D model.
     *
     *          Data loaded from model are used to create static / dynamic renderable meshes.
     *          Some of this data may be not available or generated on loading time.
     */
    class GEOMETRY_API Model final
    {
    public:
        std::vector<ModelPart*> Parts;

        std::vector<ModelPart*> FindChildren(ModelPart* parentPart) const noexcept;

        Matrix ComputeWorldMatrix(ModelPart* part) const noexcept;

        Model() noexcept;
        ~Model() noexcept;
    };

    GEOMETRY_API Storage::Archive& operator<< (Storage::Archive& archive, Model& model) noexcept;
}
