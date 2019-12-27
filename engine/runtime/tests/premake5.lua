if _OPTIONS["with-tests"] == "yes" then

    group "engine/tests"

    include "base"
    include "entities"
    include "graphics"
    include 'maths'

end
