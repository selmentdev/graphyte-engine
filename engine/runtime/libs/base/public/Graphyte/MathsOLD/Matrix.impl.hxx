    mathinline Matrix mathcall Matrix::FromRollPitchYaw(float pitch, float yaw, float roll) noexcept
    {
        auto v_angles = Vector3::Make(pitch, yaw, roll);
        return Matrix::FromRollPitchYaw(v_angles);
    }

    mathinline Matrix mathcall Matrix::FromRollPitchYaw(Vector3 angles) noexcept
    {
        auto q_rotation = Quaternion::RotationFromRollPitchYaw(angles);
        return Matrix::FromRotationQuaternion(q_rotation);
    }
}
