#pragma once

namespace Graphyte
{
    template <typename T>
    struct AccessKey final
    {
        friend T;
    private:
        AccessKey() = default;
    };
}
