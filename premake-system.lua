----------------------------------------------------------------------------------------------------
-- courtesy of Daniel Penkala
----------------------------------------------------------------------------------------------------

---
-- Required modules

require "vstudio"

    local p = premake
    local api = p.api
    --local settings = require "cunits.settings"

---
-- MSBuild specific project options enabled when support for MSBuild native Jumbo files is selected.

    api.register {
        name = "ufenabled",
        scope = "project",
        kind = "boolean"
    }

    api.register {
        name = "ufinclude",
        scope = "config",
        kind = "boolean"
    }

    api.register {
        name = "uforder",
        scope = "config",
        kind = "number"
    }

    api.register {
        name = "ufsamefolder",
        scope = "config",
        kind = "boolean"
    }

    api.register {
        name = "ufminsources",
        scope = "config",
        kind = "number",
        default = 2
    }

    api.register {
        name = "ufoutput",
        scope = "config",
        kind = "path",
        default = "$(IntDir)"
    }

    api.register {
        name = "ufcustom",
        scope = "config",
        kind = "boolean"
    }

    -- Generated file content options
    api.register {
        name = "ufbeforeinclude",
        scope = "config",
        kind = "list:string",
    }

    api.register {
        name = "ufafterinclude",
        scope = "config",
        kind = "list:string",
    }

    api.register {
        name = "ufbeforeincludefile",
        scope = "config",
        kind = "list:path",
    }

    api.register {
        name = "ufafterincludefile",
        scope = "config",
        kind = "list:path",
    }

    api.register {
        name = "jmcdisabled",
        scope = "config",
        kind = "boolean",
    }

    api.register {
        name = "enablemodules",
        scope = "project",
        kind = "boolean",
    }

    api.register {
        name = "EnableClangTidyCodeAnalysis",
        scope = "project",
        kind = "boolean",
    }
---
-- Hooks into the VisualStudio generation action to support the msbuild options

    local vstudio = p.vstudio
    local m = vstudio.vc2010

    -- Enable modules experimental support
    p.override(p.vstudio.vc2010.elements, "clCompile", function(base, cfg)
        local calls = base(cfg)
        if cfg.enablemodules then
            table.insert(calls, function(cfg)
                p.vstudio.vc2010.element("EnableModules", nil, "true")
            end)
        end
        return calls
    end)

    -- Disable support for JustMyCode for scope
    p.override(p.vstudio.vc2010.elements, "clCompile", function(base, cfg)
        local calls = base(cfg)
        if cfg.jmcdisabled then
            table.insert(calls, function(cfg)
                p.vstudio.vc2010.element("SupportJustMyCode", nil, "false")
            end)
        end
        return calls
    end)

    -- Set the required global property value to true
    p.override(p.vstudio.vc2010.elements, "globals", function(base, proj)
        local calls = base(proj)
        if proj.ufenabled then
            table.insertafter(calls, m.projectName, function()
                m.element("EnableUnitySupport", nil, "true")
            end)
        end

        if proj.EnableClangTidyCodeAnalysis then
            table.insertafter(calls, m.projectName, function()
                m.element("EnableClangTidyCodeAnalysis", nil, "true")
            end)
        end

        return calls
    end)

    -- Set unity file options in project properties
    p.override(p.vstudio.vc2010.elements, "clCompile", function(base, cfg)
        local calls = base(cfg)
        if cfg.ufenabled then
            table.insertafter(calls, m.includePath, m.ufinclude)
            table.insertafter(calls, m.includePath, m.ufafterinclude)
            table.insertafter(calls, m.includePath, m.ufbeforeinclude)
        end
        return calls
    end)


-- Implementation of unity files options to be generated

    function m.ufinclude(cfg, condition)
        if cfg.ufinclude ~= nil then
            m.element("IncludeInUnityFile", condition, tostring(cfg.ufinclude))
        end
    end

    function m.ufbeforeinclude(cfg)
        if cfg.ufbeforeinclude and #cfg.ufbeforeinclude > 0 then
            m.element("AddCodeBeforeSourceInclude", nil, table.concat(cfg.ufbeforeinclude, "\n"))
        end
    end

    function m.ufafterinclude(cfg)
        if cfg.ufafterinclude and #cfg.ufafterinclude > 0 then
            m.element("AddCodeAfterSourceInclude", nil, table.concat(cfg.ufafterinclude, "\n"))
        end
    end

    local unity_file_index = { }
    local unity_file_indexed = { }
