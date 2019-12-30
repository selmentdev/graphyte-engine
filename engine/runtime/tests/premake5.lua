if _OPTIONS["with-tests"] == "yes" then

    group "runtime/tests"

    include "base"
    include "entities"
    include "graphics"
    include 'maths'

end
