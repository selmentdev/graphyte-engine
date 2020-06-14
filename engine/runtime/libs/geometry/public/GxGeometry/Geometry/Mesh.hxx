#pragma once
#include <GxGeometry/Geometry.module.hxx>
#include <GxBase/Storage/Archive.hxx>

namespace Graphyte::Geometry
{
    /**
     * @brief   This struct contains mesh data in separate streams.
     *
     * @note    Assumptions
     *
     *          - all faces are triangles
     *          - mesh face has N corners (N=3 for triangles).
     *          - wedge all attributes of each corner of face
     *              - wedge_id = face_id * corners + corner_id
     *          - vertex - vertex position shared by wedges
     */
    class GEOMETRY_API Mesh final
    {
    public:
        /**
         * @brief   Number of supported texture coords.
         */
        static const size_t MaxTextureCoords = 8;

        /**
         * @brief   Number of corners in primitive.
         */
        static const uint32_t FacePrimitiveCornersCount = 3;

    public:
        /**
         * @brief   Stores mapping between faces and materials.
         *
         * @note    FaceMaterialIndex[face_index] = material_index.
         */
        std::vector<int32_t> FaceMaterialIndices;

        /**
         * @brief   Stores information about face smoothing.
         *
         * @note    FaceSmoothingMasks[face_index] = smooth_mask.
         */
        std::vector<uint32_t> FaceSmoothingMasks;

        /**
         * @brief   Stores vertex position.
         *
         * @note    VertexPositions[vertex_index] = Float3(position)
         */
        std::vector<Float3> VertexPositions;

        /**
         * @brief   Stores mapping between wedge_index to vertex_index.
         *
         * @note    WedgeIndices[wedge_index] = vertex_index.
         */
        std::vector<uint32_t> WedgeIndices;

        /**
         * @brief   Stores information of tangent in U direction at specified wedge_index.
         *
         * @note    WedgeTangentX[wedge_index] = tangent_x.
         */
        std::vector<Float3> WedgeTangentX;

        /**
         * @brief   Stores information of tangent in V direction at specified wedge_index.
         *
         * @note    WedgeTangentY[wedge_index] = tangent_y.
         */
        std::vector<Float3> WedgeTangentY;

        /**
         * @brief   Stores normal vector at specified wedge_index.
         *
         * @note    WedgeTangentZ[wedge_index] = normal.
         */
        std::vector<Float3> WedgeTangentZ;

        /**
         * @brief   Stores texture coords at specified wedge_index.
         *
         * @note    WedgeTextureCoords[uv_layer][wedge_index] = texcoords.
         */
        std::vector<Float2> WedgeTextureCoords[MaxTextureCoords];

        /**
         * @brief   Stores color information at specified wedge_index.
         *
         * @note    WedgeColors[wedge_index] = color.
         */
        std::vector<ColorBGRA> WedgeColors;

    public:
        /**
         * @brief   Clears mesh data.
         */
        void Clear() noexcept;

        /**
         * @brief   Checks whether mesh is valid.
         */
        bool IsValid() const noexcept;

    public:
        /**
         * @brief   Gets number of vertices in mesh.
         */
        __forceinline uint32_t GetVerticesCount() const noexcept
        {
            return static_cast<uint32_t>(this->VertexPositions.size());
        }

        /**
         * @brief   Gets number of wedges.
         */
        __forceinline uint32_t GetWedgesCount() const noexcept
        {
            return static_cast<uint32_t>(this->WedgeIndices.size());
        }

        /**
         * @brief   Gets number of faces.
         */
        __forceinline uint32_t GetFacesCount() const noexcept
        {
            return static_cast<uint32_t>(this->WedgeIndices.size()) / FacePrimitiveCornersCount;
        }

        /**
         * @brief   Computes wedge index from face and corner index.
         *
         * @param   face_index      Provides a face index.
         * @param   corner_index    Provides a corner index.
         *
         * @return  The wedge index.
         */
        __forceinline uint32_t ComputeWedgeIndex(uint32_t face_index, uint32_t corner_index) const noexcept
        {
            return (face_index * FacePrimitiveCornersCount) + corner_index;
        }

        /**
         * @brief   Computes face index from wedge index.
         *
         * @param   wedge_index     Provides a wedge index.
         *
         * @return  The face index.
         */
        __forceinline uint32_t ComputeFaceIndex(uint32_t wedge_index) const noexcept
        {
            return (wedge_index / FacePrimitiveCornersCount);
        }
    };

    GEOMETRY_API Storage::Archive& operator<<(Storage::Archive& archive, Mesh& mesh) noexcept;
}
