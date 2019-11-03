group 'sdks'

include 'fmt'
include 'lz4'
include 'libvulkanvma'
include 'glad'

if os.target() == "windows" then
    -- GMake will try to build them :/
    include 'catch2'
end
